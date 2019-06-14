//
// Created by y on 2019-06-05.
//

#ifndef MINISQL_CONFIG_H
#define MINISQL_CONFIG_H

#include <cstdint>

#define PAGE_SIZE 4096
#define BUFFER_POOL_SIZE 1024
#define INVALID_PAGE_ID -1

#define DBMETA_HEADER 16
#define DBMETA_COUNT 4
#define DBMETA_NAME 32
#define DBMETA_ID 4

typedef uint32_t page_id_t;

#endif //MINISQL_CONFIG_H
