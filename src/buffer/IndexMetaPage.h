//
// Created by y on 2019-06-15.
//

#ifndef MINISQL_INDEXMETAPAGE_H
#define MINISQL_INDEXMETAPAGE_H


#include "Page.h"
#include <string>
using namespace std;
/**
* | root_id (4) | ddl_size (4) | CREATE INDEX … ;
*/
class IndexMetaPage :Page{
    friend  class  DbInterface;
private:
    page_id_t rootId;   //存放B+树根节点的id
    string indexName="";    //索引名
    string ddl="";  //sql语句
public:
    explicit IndexMetaPage(Page *p) : Page(*p) {
    };
    void composePage(page_id_t rootId, string ddl); //存入
    void parsePage();   //解析
};




#endif //MINISQL_INDEXMETAPAGE_H
