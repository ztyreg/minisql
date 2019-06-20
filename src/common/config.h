//
// Created by y on 2019-06-05.
//

#ifndef MINISQL_CONFIG_H
#define MINISQL_CONFIG_H

#include <cstdint>
#include <string>

using namespace std;

#define PAGE_SIZE 4096
#define BUFFER_POOL_SIZE 1024
#define INVALID_PAGE_ID -1

#define DBMETA_HEADER 16
#define DBMETA_COUNT 4
#define DBMETA_NAME 32
#define DBMETA_ID 4

#define TABLEMETA_ID 4
#define TABLEMETA_SIZE 4

#define TABLE_ID 4
#define TABLE_PREVID 4
#define TABLE_NEXTID 4
#define TABLE_COUNT 4
#define TABLE_SIZE 4

#define DEBUG false
#define TEST true

typedef uint32_t page_id_t;

extern char TEST_CHAR[4096];

/**
 * table column data types and features
 */
typedef struct column_struct {
    string columnName;
    string dataType; //int, float, char
    int charLength; //0-255
    bool isUnique;
    bool isPrimaryKey;
} column_t;

/**
 * value corresponding to the column
 */
typedef struct {
    string type;
    string field;
} value_t;
#endif //MINISQL_CONFIG_H
