**Create**

```sql
CREATE TABLE tbl_name (create_definition,...)

create_definition:
    col_name column_definition | PRIMARY KEY(col_name)

column_definition:
    data_type [UNIQUE]

data_type:
    INTEGER | FLOAT | CHAR(M)
```

Records should be shorter than page. Supports the primary key for a single attribute.

**Delete**

```sql
DROP TABLE tbl_name
```

**Index (not implemented)**

```sql
CREATE INDEX index_name ON tbl_name (col_name,...)
```

**Drop index (not implemented)**

```sql
DROP INDEX index_name ON tbl_name        
```

**Insert**

```sql
INSERT INTO tbl_name VALUES (value_list)

value:
    {expr | DEFAULT}

value_list:
    value [, value] ...
```

Throws an error when there are duplicated unique keys.

**Delete**

```sql
DELETE FROM tbl_name [WHERE where_condition]

where_condition:
    value_operation [AND value_operation] ...
    
value_operation:
    col_name {= | >= | <= | > | < | <>} value
```

**Select**

```sql
SELECT
    select_expr [, select_expr ...]
    [FROM table_references
    [WHERE where_condition]]

where_condition:
    value_operation [AND value_operation] ...
    
value_operation:
    col_name {= | >= | <= | > | < | <>} value
```

**Batch execution**

```sql
EXECFILE file_name
```
