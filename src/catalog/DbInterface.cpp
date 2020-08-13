#include <utility>

//
// Created by y on 2019-06-13.
//

#include "DbInterface.h"
#include <iostream>
#include <string>

void DbInterface::init(string name)
{
    diskManager = new DiskManager(name);
    bufferPoolManager = new BufferPoolManager(BUFFER_POOL_SIZE, diskManager);
    // read page 0, which is used to store metadata

    dbMetaPage = new DbMetaPage(bufferPoolManager->fetchPage(0));
    if (!dbMetaPage->parsePage()) {
        //new db
        diskManager->clearFile();
        delete diskManager;
        diskManager = new DiskManager(name);
        diskManager->writePage(0, dbMetaPage->data);

        delete bufferPoolManager;
        bufferPoolManager = new BufferPoolManager(BUFFER_POOL_SIZE, diskManager);

    }
}

DbInterface::~DbInterface()
{


    delete dbMetaPage;
    delete bufferPoolManager;
    delete diskManager;
}

DbInterface::DbInterface()
{

}

/**
 * new table/index meta page
 */
void DbInterface::writeTableMeta(const string &tableName, string data)
{
    if (dbMetaPage->entryExists(tableName)) {
        cerr << "table exists" << endl;
        return;
    }

    //meta pages could be directly accessed
    //new page to store table meta
    page_id_t metaId;
    //not the same page
    Page *ptableMetaPage = bufferPoolManager->newPage(metaId);
    auto *tableMetaPage =
            new TableMetaPage(ptableMetaPage);

    //new table root page
    page_id_t rootId;
    Page *ptablePage = bufferPoolManager->newPage(rootId);
    auto *tablePage =
            new TablePage(ptablePage);

    //add table metadata
    tableMetaPage->composePage(rootId, std::move(data));
    tableMetaPage->parsePage();
    cout << "\tnew table with tuple length "
         << tableMetaPage->getTupleLength() << endl;
    //add table data
    tablePage->composePage(rootId, INVALID_PAGE_ID, INVALID_PAGE_ID,
                           tableMetaPage->getTupleLength(),
                           tableMetaPage->calMaxNumOfTuples(), 0);

    //add db metadata
    dbMetaPage->entries.insert(make_pair(tableName, metaId));
    //write db metadata
    dbMetaPage->composePage();


    cout << "Wrting to " << metaId << endl;
    diskManager->writePage(metaId, tableMetaPage->data);
    memcpy(ptableMetaPage->data, tableMetaPage->data, PAGE_SIZE);

    cout << "Wrting to " << rootId << endl;
    diskManager->writePage(rootId, tablePage->data);
    memcpy(ptablePage->data, tablePage->data, PAGE_SIZE);

    cout << "Wrting to page 0" << endl;
    diskManager->writePage(0, dbMetaPage->data);


#ifdef TEST
    cout << "CREATE TABLE test ..." << endl;
    Page *pPage = bufferPoolManager->fetchPage(0);
    auto *testDbMetaPage =
            new DbMetaPage(pPage);
    testDbMetaPage->parsePage();
    cout << "\tsize of entries now: " << testDbMetaPage->getEntryNumber() << endl;

    Page *pPage2 = bufferPoolManager->fetchPage(metaId);
    if (DEBUG) cout << "DEBUG: #" << pPage2->pageId << " " << pPage2 << endl;
    auto *testTableMetaPage =
            new TableMetaPage(pPage2);
    if (DEBUG) cout << "DEBUG: #" << testTableMetaPage->pageId << " " << endl;
    if (DEBUG) cout << strcmp(TEST_CHAR, testTableMetaPage->data) << endl;
    testTableMetaPage->parsePage();
    cout << "\tDDL:" << testTableMetaPage->ddl << endl;

    delete testTableMetaPage;
    delete testDbMetaPage;
#endif

    delete tablePage;
    delete tableMetaPage;

}

void DbInterface::deleteTableMeta(const string &tableName)
{
    if (!dbMetaPage->entryExists(tableName)) {
        cerr << "table does not exist" << endl;
        return;
    }

    //lazy deletion: only db meta
    dbMetaPage->entries.erase(tableName);
    dbMetaPage->composePage();
    cout << "Wrting to page 0" << endl;
    diskManager->writePage(0, dbMetaPage->data);

#ifdef TEST
    cout << "DROP TABLE test ..." << endl;
    auto *testDbMetaPage =
            new DbMetaPage(bufferPoolManager->fetchPage(0));
    testDbMetaPage->parsePage();
    cout << "\tsize of entries now: " << testDbMetaPage->getEntryNumber() << endl;
    delete testDbMetaPage;
#endif


}

void DbInterface::deleteTuple(const string &tableName, vector<whereClause> wheres)
{
    page_id_t metaId = dbMetaPage->entries[tableName];
    auto *tableMetaPage =
            new TableMetaPage(bufferPoolManager->fetchPage(metaId));
    tableMetaPage->parsePage();

    //table page
    page_id_t rootId = tableMetaPage->getRootId();
    Page *ptablePage = bufferPoolManager->fetchPage(rootId);
    auto *tablePage =
            new TablePage(ptablePage);
    tablePage->parsePage();

    //iterate through
    do {
        int offset = TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_COUNT +
                     TABLE_SIZE + TABLE_MAX;
        for (int i = 0; i < tablePage->count; ++i) {
            int tupleoffset = offset;

            //tuples are pushed back in the order of columns
            vector<string> tuple;
            //get data field
            for (auto &column : tableMetaPage->columns) {
                if (column.dataType == "int") {
                    int tempint;
                    memread_int(tablePage->data + offset, &tempint);
                    tuple.push_back(to_string(tempint));
                    offset += 4;
                } else if (column.dataType == "float") {
                    float tempfloat;
                    memread_float(tablePage->data + offset, &tempfloat);
                    tuple.push_back(to_string(tempfloat));
                    offset += 4;
                } else if (column.dataType == "char") {
                    int len = column.charLength;
                    char *tempchar = new char[len];
                    memcpy(tempchar, tablePage->data + offset, len);
                    tuple.emplace_back(tempchar);
                    offset += len;
                    delete[] tempchar;
                }
            }

            //check constraints
            int inflag = 1;
            for (const auto &item : wheres) {
                int idx = tableMetaPage->getColumnIndexByName(item.columnName);
                string type = tableMetaPage->getColumnTypeByName(item.columnName);
                //LT GT LE GE EQ NE
                auto field = Data(item.field, type);
                auto tuplefield = Data(tuple[idx], type);

                if (item.op == "LT" && tuplefield >= field) {
                    inflag = 0;
                    break;
                } else if (item.op == "GT" && tuplefield <= field) {
                    inflag = 0;
                    break;
                } else if (item.op == "LE" && tuplefield > field) {
                    inflag = 0;
                    break;
                } else if (item.op == "GE" && tuplefield < field) {
                    inflag = 0;
                    break;
                } else if (item.op == "EQ" && tuplefield != field) {
                    inflag = 0;
                    break;
                } else if (item.op == "NE" && tuplefield == field) {
                    inflag = 0;
                    break;
                }
            }
            if (inflag) {
                memcpy(tablePage->data + tupleoffset,
                       tablePage->data + tableMetaPage->tupleLength + tupleoffset,
                       PAGE_SIZE - tableMetaPage->tupleLength - tupleoffset);
                tablePage->count--;
                tablePage->refreshPage();
                diskManager->writePage(tablePage->pageId, tablePage->data);
                memcpy(ptablePage->data, tablePage->data, PAGE_SIZE);
            }

        }

        page_id_t nextId = tablePage->nextId;
        if (nextId == INVALID_PAGE_ID) break;

        delete tablePage;
        tablePage = new TablePage(bufferPoolManager->fetchPage(nextId));
        tablePage->parsePage();

    } while (true);

}

void DbInterface::insertTuple(const string &tableName, vector<value_t> tuple)
{
    if (!dbMetaPage->entryExists(tableName)) {
        cerr << "table does not exist" << endl;
        return;
    }

    page_id_t metaId = dbMetaPage->entries[tableName];
    auto *tableMetaPage =
            new TableMetaPage(bufferPoolManager->fetchPage(metaId));
    tableMetaPage->parsePage();

#ifdef TEST
    cout << "INSERT test ..." << endl;
    for (const auto &item : tableMetaPage->columns) {
        if (item.dataType == "char") {
            cout << item.columnName << "(" << item.dataType << "["
                 << item.charLength << "])";
        } else {
            cout << item.columnName << "(" << item.dataType << ")";
        }
        cout << (item.isUnique ? "U" : "");
        cout << (item.isPrimaryKey ? "P" : "");
        cout << " ";
    }
    cout << endl;
#endif

    //check value type
    if (tableMetaPage->columns.size() != tuple.size()) {
        cerr << "wrong tuple size" << endl;
        return;
    }
    for (int i = 0; i < tuple.size(); ++i) {
        //int will be converted to float
        if (tableMetaPage->columns[i].dataType == "float" &&
            tuple[i].type == "int")
            continue;
        if (tableMetaPage->columns[i].dataType != tuple[i].type) {
            cerr << "wrong data type" << endl;
        }
    }

    //check constraints: primary key and unique
    for (const auto &column : tableMetaPage->columns) {
        if (column.isPrimaryKey &&
            hasConflict(tableMetaPage, tableName, tableMetaPage->primaryKey, tuple)) {
            cerr << "primary key conflict!" << endl;
            return;
        }
        if (column.isUnique &&
            hasConflict(tableMetaPage, tableName, column.columnName, tuple)) {
            cerr << "unique key conflict!" << endl;
            return;
        }
    }

    //last table page
    int value = 0;
    page_id_t rootId = tableMetaPage->getRootId();
    Page *ptablePage = bufferPoolManager->fetchPage(rootId);
    auto *tablePage =
            new TablePage(ptablePage);
    tablePage->parsePage();
    value += tablePage->count;

    page_id_t nextId = tablePage->nextId;
    while (nextId != INVALID_PAGE_ID) {
        delete tablePage;
        ptablePage = bufferPoolManager->fetchPage(nextId);

        tablePage = new TablePage(ptablePage);
        tablePage->parsePage();
        value += tablePage->count;
        nextId = tablePage->nextId;
    }

    if (DEBUG)
        cout << "\tlast page ID #" << tablePage->pageId
             << " count: " << tablePage->count
             << " size: " << tablePage->size
             << " max: " << tablePage->max << endl;

    //allocate new page
    if (tablePage->pageFull()) {
        page_id_t newId;
        Page *tempp = ptablePage;
        ptablePage = bufferPoolManager->newPage(newId);
        auto *newPage =
                new TablePage(ptablePage);
        newPage->composePage(newId, tablePage->pageId, INVALID_PAGE_ID,
                             tablePage->size, tablePage->max, 0);
        tablePage->nextId = newId;
        tablePage->refreshPage();
        diskManager->writePage(tempp->pageId, tablePage->data);
        memcpy(tempp->data, tablePage->data, PAGE_SIZE);

        tablePage = newPage;
        tablePage->parsePage();
    }

    //assemble tuple
    char *t = new char[tablePage->size];
    int offset = 0;
    for (int i = 0; i < tableMetaPage->columns.size(); ++i) {
        //int will be converted to float
        if (dbMetaPage->entryExists(tableName + tableMetaPage->columns[i].columnName)) {
            if (tableMetaPage->columns[i].dataType == "int") {
//                Data key(stoi(tuple[i].field));
//                readIndex(tableName, tableMetaPage->columns[i].columnName, INSERT, key, value);

            } else if (tableMetaPage->columns[i].dataType == "float") {
//                Data key(stof(tuple[i].field));
//                readIndex(tableName, tableMetaPage->columns[i].columnName, INSERT, key, value);
            } else if (tableMetaPage->columns[i].dataType == "char") {
                int len = tableMetaPage->columns[i].charLength;
                char *s = new char[len];
                memset(s, 0, len);
                memcpy(s, tuple[i].field.c_str(), tuple[i].field.length());
//                Data key(s, len);
//                readIndex(tableName, tableMetaPage->columns[i].columnName, INSERT, key, value);
            }
        }
        if (tableMetaPage->columns[i].dataType == "int") {
            memwrite_int(t + offset, stoi(tuple[i].field));
            offset += 4;
        } else if (tableMetaPage->columns[i].dataType == "float") {
            memwrite_float(t + offset, stof(tuple[i].field));
            offset += 4;
        } else if (tableMetaPage->columns[i].dataType == "char") {
            int len = tableMetaPage->columns[i].charLength;
            char *s = new char[len];
            memset(s, 0, len);
            memcpy(s, tuple[i].field.c_str(), tuple[i].field.length());
            memcpy(t + offset, s, len);
            offset += len;
            delete[] s;
        }
    }

    tablePage->addTupleString(t, tablePage->size);

    cout << "Wrting to " << tablePage->pageId << endl;
    diskManager->writePage(tablePage->pageId, tablePage->data);
    memcpy(ptablePage->data, tablePage->data, PAGE_SIZE);


    delete[] t;


    delete tableMetaPage;
    delete tablePage;
}

vector<vector<string> >
DbInterface::readTuple(const string &tableName, bool selectAll,
                       vector<string> columnNames, vector<whereClause> wheres)
{
//    dbMetaPage->parsePage();
    vector<vector<string> > tuples;

    if (!dbMetaPage->entryExists(tableName)) {
        cerr << "table does not exist" << endl;
        return tuples;
    }

    page_id_t metaId = dbMetaPage->entries[tableName];
    auto *tableMetaPage =
            new TableMetaPage(bufferPoolManager->fetchPage(metaId));
    tableMetaPage->parsePage();
    vector<string> col;
    for (const auto &column : tableMetaPage->columns) {
        col.push_back(column.columnName);
    }
    tuples.push_back(col);

    //table page
    page_id_t rootId = tableMetaPage->getRootId();
    Page *ptablePage = bufferPoolManager->fetchPage(rootId);
    auto *tablePage =
            new TablePage(ptablePage);
    tablePage->parsePage();


    if (selectAll) {
        do {
            int offset = TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_COUNT +
                         TABLE_SIZE + TABLE_MAX;
            for (int i = 0; i < tablePage->count; ++i) {
                //tuples are pushed back in the order of columns
                vector<string> tuple;
                //get data field
                for (auto &column : tableMetaPage->columns) {
                    if (column.dataType == "int") {
                        int tempint;
                        memread_int(tablePage->data + offset, &tempint);
                        tuple.push_back(to_string(tempint));
                        offset += 4;
                    } else if (column.dataType == "float") {
                        float tempfloat;
                        memread_float(tablePage->data + offset, &tempfloat);
                        tuple.push_back(to_string(tempfloat));
                        offset += 4;
                    } else if (column.dataType == "char") {
                        int len = column.charLength;
                        char *tempchar = new char[len];
                        memcpy(tempchar, tablePage->data + offset, len);
                        tuple.emplace_back(tempchar);
                        offset += len;
                        delete[] tempchar;
                    }
                }
                //check constraints
                int inflag = 1;
                for (const auto &item : wheres) {
                    int idx = tableMetaPage->getColumnIndexByName(item.columnName);
                    string type = tableMetaPage->getColumnTypeByName(item.columnName);
                    //LT GT LE GE EQ NE
                    auto field = Data(item.field, type);
                    auto tuplefield = Data(tuple[idx], type);

                    if (item.op == "LT" && tuplefield >= field) {
                        inflag = 0;
                        break;
                    } else if (item.op == "GT" && tuplefield <= field) {
                        inflag = 0;
                        break;
                    } else if (item.op == "LE" && tuplefield > field) {
                        inflag = 0;
                        break;
                    } else if (item.op == "GE" && tuplefield < field) {
                        inflag = 0;
                        break;
                    } else if (item.op == "EQ" && tuplefield != field) {
                        inflag = 0;
                        break;
                    } else if (item.op == "NE" && tuplefield == field) {
                        inflag = 0;
                        break;
                    }
                }
                if (inflag) tuples.push_back(tuple);

            }

            page_id_t nextId = tablePage->nextId;
            if (nextId == INVALID_PAGE_ID) break;

            delete tablePage;
            tablePage = new TablePage(bufferPoolManager->fetchPage(nextId));
            tablePage->parsePage();

        } while (true);

    }

    return tuples;

}

//创建对应属性的index，并将创建index的原信息写入IndexMetaPage，B+树节点信息写入IndexPage
void DbInterface::createIndex(const string &tableName, const string &attrName, string data)
{
    if (dbMetaPage->entryExists(tableName + attrName)) {       //judge if the index exists
        cerr << "index exists" << endl;
        return;
    }
    page_id_t metaId = dbMetaPage->entries[tableName];      //find tablename
    auto *tableMetaPage =
            new TableMetaPage(bufferPoolManager->fetchPage(metaId));
    tableMetaPage->parsePage();
    if (!tableMetaPage->isAttrUnique(attrName) && tableMetaPage->primaryKey != attrName) {
        cout << "the attribute is not unique" << endl;
        return;
    }
    page_id_t rootId = tableMetaPage->getRootId();

    vector<Data> keys;
    readTable(rootId, tableMetaPage->getAttrType(attrName), tableMetaPage->getAttrSize(attrName),
              tableMetaPage->getAttrOffset(attrName), keys);    //get keys

    Tree T(DEGREE, keys);


    vector<TreeNode *> nodes = T.print();      //show B+  trees
    map<TreeNode *, page_id_t> id;
    for (int i = 0; nodes[i]; i++) {
        bufferPoolManager->newPage(rootId);    //allocate page for tree node
        id.insert(make_pair(nodes[i], rootId));
    }

    Page *pPage = bufferPoolManager->newPage(rootId);
    auto *indexMetaPage = new IndexMetaPage(pPage);
    indexMetaPage->composePage(id[nodes[0]], data);
    diskManager->writePage(indexMetaPage->pageId, indexMetaPage->data);  //write indexmetapage
    memcpy(pPage->data, indexMetaPage->data, PAGE_SIZE);

    dbMetaPage->entries.insert(make_pair(tableName + attrName, indexMetaPage->pageId));

    for (int i = 0; nodes[i]; i++) {
        Page *pPage = bufferPoolManager->fetchPage(id[nodes[i]]);
        auto *indexPage = new IndexPage(pPage);
        indexPage->composePage(nodes[i], id, tableMetaPage->getAttrType(attrName));
        diskManager->writePage(indexPage->pageId, indexPage->data);     //write indexpage
        memcpy(pPage->data, indexPage->data, PAGE_SIZE);
    }

    cout << "create index succeed" << endl;

    delete indexMetaPage;
    delete tableMetaPage;

}

void DbInterface::readTable(page_id_t rootId, const string &type,
                            int attrSize, int attrOffset, vector<Data> &keys)
{
    keys.clear();
    Page *ptablePage = bufferPoolManager->fetchPage(rootId);
    auto *tablePage =
            new TablePage(ptablePage);
    tablePage->parsePage();
    for (int i = 0; i < tablePage->count; i++) {
        if (type == "int") {
            int value;
            memread_int(tablePage->data + TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_COUNT +
                        TABLE_SIZE + TABLE_MAX + i * tablePage->size + attrOffset, &value);
            Data key(value);
            keys.push_back(key);
        } else if (type == "float") {
            float value;
            memread_float(tablePage->data + TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_COUNT +
                          TABLE_SIZE + TABLE_MAX + i * tablePage->size + attrOffset, &value);
            Data key(value);
            keys.push_back(key);
        } else if (type == "char") {
            char tempchar[attrSize];
            memcpy(tempchar, tablePage->data + TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_COUNT +
                             TABLE_SIZE + TABLE_MAX + i * tablePage->size + attrOffset, attrSize);
            Data key(tempchar, attrSize);
            keys.push_back(key);
        }
    }

    page_id_t nextId = tablePage->nextId;
    while (nextId != INVALID_PAGE_ID) {
        delete tablePage;
        tablePage = new TablePage(bufferPoolManager->fetchPage(nextId));
        tablePage->parsePage();

        for (int i = 0; i < tablePage->count; i++) {
            if (type == "int") {
                int value;
                memread_int(tablePage->data + TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_COUNT +
                            TABLE_SIZE + TABLE_MAX + i * tablePage->size + attrOffset, &value);
                Data key(value);
                keys.push_back(key);
            } else if (type == "float") {
                float value;
                memread_float(tablePage->data + TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_COUNT +
                              TABLE_SIZE + TABLE_MAX + i * tablePage->size + attrOffset, &value);
                Data key(value);
                keys.push_back(key);
            } else if (type == "char") {
                char tempchar[attrSize];
                memcpy(tempchar, tablePage->data + TABLE_ID + TABLE_PREVID + TABLE_NEXTID + TABLE_COUNT +
                                 TABLE_SIZE + TABLE_MAX + i * tablePage->size + attrOffset, attrSize);
                Data key(tempchar, attrSize);
                keys.push_back(key);
            }
        }
        nextId = tablePage->nextId;
    }

}

Tree DbInterface::readTree(page_id_t metaId, const string &type,
                           int attrSize, map<page_id_t, TreeNode *> &id)
{
    int keynum = 0;
    int nodenum = 0;
    auto *indexMetaPage =
            new IndexMetaPage(bufferPoolManager->fetchPage(metaId));

    indexMetaPage->parsePage();

    vector<page_id_t> childsId;
    map<page_id_t, TreeNode *> newid;
    TreeNode *node = new TreeNode[100];

    childsId.push_back(indexMetaPage->rootId);

    while (!childsId.empty()) {
        auto *indexPage =
                new IndexPage(bufferPoolManager->fetchPage(childsId[0]));
        indexPage->parsePage(type, attrSize, childsId);
        id.insert(make_pair(childsId[0], node + nodenum));
        newid.insert(make_pair(childsId[0], node + nodenum++));     //get nodenum
        childsId.erase(childsId.begin());
    }

    for (auto &it : id) {  //build B+ tree from page
        auto *indexPage =
                new IndexPage(bufferPoolManager->fetchPage(it.first));
        indexPage->parsePage(type, attrSize, childsId);
        it.second->IsLeaf = indexPage->Isleaf;
        it.second->num = indexPage->num;
        it.second->degree = DEGREE;
        if (indexPage->Isleaf) {
            keynum += indexPage->num;
            for (int i = 0; i < indexPage->num; i++) {
                it.second->vals[i] = indexPage->vals[i];
                it.second->keys[i] = indexPage->keys[i];
            }
            it.second->nextleaf = newid[indexPage->nextleaf];

        } else {
            int k;
            for (k = 0; k < indexPage->num; k++) {
                it.second->keys[k] = indexPage->keys[k];
                it.second->childs[k] = newid[indexPage->childsId[k]];

                newid[indexPage->childsId[k]]->parent = it.second;
            }
            it.second->childs[k] = newid[indexPage->childsId[k]];
            newid[indexPage->childsId[k]]->parent = it.second;
        }
    }
    Tree T(node, keynum, nodenum, DEGREE);
    return T;

}

int DbInterface::adjustIndex(Tree T, int mode, const Data &key, int value, const string &type,
                             map<page_id_t, TreeNode *> id)
{
    map<TreeNode *, page_id_t> writeid;
    int i = T.nodenum;
    int k = 0;

    if (mode == SEARCH) {
        return T.SearchVal(key);        //return offset
    } else if (mode == INSERT) {
        if (!T.InsertKey(key, value)) {
            cout << "the key exists" << endl;
        }
        vector<TreeNode *> nodes = T.print();
        if (i == T.nodenum) {
            for (auto &it : id) {
                writeid.insert(make_pair(it.second, it.first));
            }
            for (k = 0; writeid.count(nodes[k]); k++) {
                Page *pPage = bufferPoolManager->fetchPage(writeid[nodes[k]]);
                auto *indexPage = new IndexPage(pPage);
                indexPage->composePage(nodes[k], writeid, type);
                diskManager->writePage(indexPage->pageId, indexPage->data);
                memcpy(pPage->data, indexPage->data, PAGE_SIZE);

            }
        } else {
            page_id_t rootId;
            for (auto &it : id) {
                writeid.insert(make_pair(nodes[k++], it.first));
            }
            for (k = T.nodenum - i; k >= 1; k--) {
                bufferPoolManager->newPage(rootId);
                writeid.insert(make_pair(nodes[T.nodenum - k], rootId));
            }

            for (k = 0; writeid.count(nodes[k]); k++) {
                Page *pPage = bufferPoolManager->fetchPage(writeid[nodes[k]]);
                auto *indexPage = new IndexPage(pPage);
                indexPage->composePage(nodes[k], writeid, type);
                diskManager->writePage(indexPage->pageId, indexPage->data);
                memcpy(pPage->data, indexPage->data, PAGE_SIZE);

            }
        }


    } else if (mode == DELETE) {
        if (!T.DeleteKey(key)) {
            cout << "the key don't exist" << endl;
        }
        map<TreeNode *, page_id_t> writeid;
        vector<TreeNode *> nodes = T.print();
        for (auto &it : id) {
            if (k == T.nodenum) break;
            writeid.insert(make_pair(nodes[k++], it.first));
        }
        for (k = 0; writeid.count(nodes[k]); k++) {
            Page *pPage = bufferPoolManager->fetchPage(writeid[nodes[k]]);
            auto *indexPage = new IndexPage(pPage);
            indexPage->composePage(nodes[k], writeid, type);
            diskManager->writePage(indexPage->pageId, indexPage->data);
            memcpy(pPage->data, indexPage->data, PAGE_SIZE);

        }

    }
    return 0;
}

//由mode选择select，insert或delete
//由File中所存的index信息重建B+树，再进行相关操作
//操作完成后将新的B+树数据写回
int DbInterface::readIndex(const string &tableName, const string &attrName, int mode, Data &key, int val)
{
    if (!dbMetaPage->entryExists(tableName + attrName))
        return 0;
    else {
        page_id_t metaId = dbMetaPage->entries[tableName];
        auto *tableMetaPage =
                new TableMetaPage(bufferPoolManager->fetchPage(metaId));
        tableMetaPage->parsePage();

        map<page_id_t, TreeNode *> id;

        auto *indexMetaPage =
                new IndexMetaPage(bufferPoolManager->fetchPage(dbMetaPage->entries[tableName + attrName]));

        indexMetaPage->parsePage();
        if (indexMetaPage->rootId == 0) {
            Tree T;
            if (mode != INSERT)
                cout << "empty index" << endl;
            else
                T.InsertKey(key, val);

            page_id_t rootId;
            bufferPoolManager->newPage(rootId);
            map<TreeNode *, page_id_t> writeid;
            writeid.insert(make_pair(T.root, rootId));

            Page *pPage = bufferPoolManager->fetchPage(dbMetaPage->entries[tableName + attrName]);
            auto *indexMetaPage = new IndexMetaPage(pPage);
            indexMetaPage->parsePage();
            indexMetaPage->composePage(writeid[T.root], indexMetaPage->ddl);
            diskManager->writePage(indexMetaPage->pageId, indexMetaPage->data);
            memcpy(pPage->data, indexMetaPage->data, PAGE_SIZE);

            pPage = bufferPoolManager->fetchPage(writeid[T.root]);
            auto *indexPage = new IndexPage(pPage);
            indexPage->composePage(T.root, writeid, tableMetaPage->getAttrType(attrName));
            diskManager->writePage(indexPage->pageId, indexPage->data);
            memcpy(pPage->data, indexPage->data, PAGE_SIZE);

        } else {

            Tree T = readTree(dbMetaPage->entries[tableName + attrName],
                              tableMetaPage->getAttrType(attrName),
                              tableMetaPage->getAttrSize(attrName), id);

            return adjustIndex(T, mode, key, val, tableMetaPage->getAttrType(attrName), id);
        }


        delete tableMetaPage;
        delete indexMetaPage;
    }
    return 0;
}


//删除index

void DbInterface::deleteIndexMeta(const string &tableName, const string &indexName)      //lazy deletion
{
    for (auto it = dbMetaPage->entries.begin(); it != dbMetaPage->entries.end(); it++) {
        if (it->first.find(tableName) == 0)
            if (it->first != tableName) {
                auto *indexMetaPage = new IndexMetaPage(bufferPoolManager->fetchPage(it->second));
                indexMetaPage->parsePage();
                if (indexMetaPage->indexName == indexName) {
                    dbMetaPage->entries.erase(it->first);
                    cout << "drop successfully" << endl;
                    dbMetaPage->composePage();
                    cout << "Wrting to page 0" << endl;
                    diskManager->writePage(0, dbMetaPage->data);
                    return;
                }
            }
    }
}

bool DbInterface::hasConflict(TableMetaPage *tableMetaPage, string tableName, string columnName, vector<value_t> tuple)
{
    vector<whereClause> primaryWheres;
    whereClause primaryWhere;
    primaryWhere.columnName = columnName;
    primaryWhere.op = "EQ";
    int idx = tableMetaPage->getColumnIndexByName(columnName);
    primaryWhere.field = tuple[idx].field;
    primaryWheres.push_back(primaryWhere);

    vector<string> col;
    vector<vector<string>> constraintResult = readTuple(tableName, true, col, primaryWheres);
    return constraintResult.size() > 1;
}




