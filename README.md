# minisql

## Introduction

A DBMS with create table/drop table/select/insert/delete operations. Implemented SQL interpreter, record manager and memory buffer with page replacement algorithm.

Executable and test files are in the `cmake-build-debug/src/` folder.

Run `cmake-build-debug/src/Minisql` to start.

## Samples

`student.txt`

```mysql
create table student2(
	id int,
	name char(12) unique,
	score float,
	primary key(id) 
);

execfile instruction0.txt;
```

where the head of `instruction0.txt` is (total 1000 lines)

```mysql
insert into student2 values(1080100001,'name1',99);
insert into student2 values(1080100002,'name2',52.5);
insert into student2 values(1080100003,'name3',98.5);
insert into student2 values(1080100004,'name4',91.5);
insert into student2 values(1080100005,'name5',72.5);
insert into student2 values(1080100006,'name6',89.5);
insert into student2 values(1080100007,'name7',63);
```

