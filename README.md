# Minisql

## Introduction

This is a DBMS (Database Management System).

### Supported Operations

create table/drop table/select/insert/delete operations. 

### Throughput
On Mac Mini 2018:
* 1000 insertions finished in 4s
* 5000 insertions finished in 65s
* 10000 insertions finished in 270s

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

```txt
--请按以下语句顺序执行，全部通过即可

--1
select * from student2 where id=1080100245; --考察int类型上的等值条件查询 

--2
select * from student2 where score=98.5; --考察float类型上的等值条件查询，观察数量 

--3
select * from student2 where name='name245'; --考察char类型上的等值条件查询，此处需观察执行时间t1

--4
select * from student2 where id<>1080109998; --考察int类型上的不等条件查询，观察数量

--5
select * from student2 where score<>98.5; --考察float类型上的不等条件查询，观察数量

--6
select * from student2 where name<>'name9998’; --考察char类型上的不等条件查询，观察数量 

--7
select * from student2 where score>80 and score<85; --考察多条件and查询，观察数量 

--8
select * from student2 where score>95 and id<=1080100100; --考察多条件and查询，观察数量 

--9
insert into student2 values(1080100245,'name245',100); --报primary key约束冲突（或报unique约束冲突）

--10
-- Not implmented: create index stuidx on student2 ( score ); --unique key才能建立索引
-- Not implmented: create index stuidx on student2 ( name ); --在name这个unique属性上创建index

--11
select * from student2 where name='name245'; --此处需观察执行时间t2

--12
insert into student2 values(1080197996,’name97996’,100); --考察在建立b+树后再插入数据，b+树有没有做好insert

--13
select * from student2 where name='name97996’; --此处需观察执行时间t3

--14
delete from student2 where name='name97996’; --考察delete，同时考察b+树的delete

--15
select * from student2 where name='name97996’;

--16
insert into student2 values(1080197996,’name97996’,100);

--17
-- Not implmented: drop index stuidx; --考察drop index

--18
select * from student2 where name='name97996'; --需观察此处的执行时间t4

--19
select * from student2 where name='name245'; --需观察此处的执行时间t5

--20
delete from student2 where id=1080100245; --考察delete

--21
select * from student2 where id=1080100245;

--22
delete from student2 where score=98.5; --考察delete

--23
select * from student2 where score=98.5;

--24
delete from student2; --考察delete

--25
select * from student2;

--26
drop table student2; --考察drop table

--27
select * from student2;

--index性能体现在，有t2<t1, t2<t5和t3<t4成立
```

## Implmentations

### High-Level Design

<img src="https://github.com/ztyreg/minisql/blob/master/design.png" width="600">

Please see [Features.md](./Features.md) for a complete list of features (in Chinese).
