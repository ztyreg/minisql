//
// Created by y on 2019-06-03.
//

#ifndef MINISQL_BUFFER_H
#define MINISQL_BUFFER_H

#include <cstdint>

#define TABLE_MAX_PAGES 100

#define NODE_HEADER_SIZE 9

enum NodeType_t {
    NODE_INTERNAL, NODE_LEAF
} NodeType;

enum ExecuteResult_t {
    EXECUTE_SUCCESS,
    EXECUTE_DUPLICATE_KEY,
    EXECUTE_TABLE_FULL
};

class Buffer {
private:
    typedef struct Pager_t {
        int file_descriptor;
        uint32_t file_length;
        uint32_t num_pages;
        void *pages[TABLE_MAX_PAGES];
    } Pager;

    typedef struct Table_t {
        Pager *pager;
        uint32_t root_page_num;
    } Table;

    typedef struct Cursor_t {
        Table *table;
        uint32_t row_num;
        bool end_of_table;  // Indicates a position one past the last element
    } Cursor;

public:
    Cursor *goToTableStart();

    Cursor *goToTableEnd();

    Cursor *findLeafNode();

    void leafNodeInsert();

    void leafNodeSplitAndInsert();

    void executeInsert();

    void insertLeafNode();
};


#endif //MINISQL_BUFFER_H
