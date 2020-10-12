# Minisql

## Introduction

This is a DBMS (Database Management System) built in C++ and a accompanying web GUI.

Link: http://ec2-3-22-235-98.us-east-2.compute.amazonaws.com:8080/

<img src="https://github.com/ztyreg/minisql/blob/master/demo.png" width="600">

### Supported Operations

create table/drop table/select/insert/delete operations. 


### Other features 

SQL interpreter, record manager and memory buffer with page replacement algorithm (LRU).

Please see [Features.md](./Features.md) for a complete list of features (in Chinese).


## Getting Started

Executable and test files are in the `cmake-build-debug/src/` folder.

Run `cmake-build-debug/src/Minisql` to start.

## Samples

Sample 1: `student.txt`

```mysql
create table student2(
	id int,
	name char(12) unique,
	score float,
	primary key(id) 
);

execfile instruction0.txt;

execfile instruction1.txt;

execfile instruction2.txt;

execfile instruction3.txt;

execfile instruction4.txt;

execfile instruction5.txt;

execfile instruction6.txt;

execfile instruction7.txt;

execfile instruction8.txt;

execfile instruction9.txt;
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

Sample 2:

```sql
--1
select * from student2 where id=1080100245; --int, equal

--2
select * from student2 where score=98.5; --float, equal

--3
select * from student2 where name='name245'; --char, equal

--4
select * from student2 where id<>1080109998; --int, not equal

--5
select * from student2 where score<>98.5; --float, not equal

--6
select * from student2 where name<>'name9998'; --char, not equal

--7
select * from student2 where score>80 and score<85; --and

--8
select * from student2 where score>95 and id<=1080100100; --and

--9
insert into student2 values(1080100245,'name245',100); --unique key conflict

--10
-- Not implmented: create index stuidx on student2 ( score ); --unique key
-- Not implmented: create index stuidx on student2 ( name );

--11
select * from student2 where name='name245';

--12
insert into student2 values(1080197996,’name97996’,100);

--13
select * from student2 where name='name97996’;

--14
delete from student2 where name='name97996’; --delete

--15
select * from student2 where name='name97996’;

--16
insert into student2 values(1080197996,’name97996’,100);

--17
-- Not implmented: drop index stuidx;

--18
select * from student2 where name='name97996';

--19
select * from student2 where name='name245';

--20
delete from student2 where id=1080100245; --delete

--21
select * from student2 where id=1080100245;

--22
delete from student2 where score=98.5; --delete

--23
select * from student2 where score=98.5;

--24
delete from student2; --delete

--25
select * from student2;

--26
drop table student2; --drop table

--27
select * from student2;
```

## Implmentations

### High-Level Design

<img src="https://github.com/ztyreg/minisql/blob/master/design.png" width="600">

Please see [Features.md](./Features.md) for a complete list of features (in Chinese).
