<div style="text-align:center;font-size:30px"><b>MySQL</b></div>

# 一、常用命令

> SQL 语句分类
>
> + DQL（(DQL Data Query Language）：数据查询语言，代表关键字：select
> + DML（DML Data Manipulation Language）：数据操作语言，代表关键字：insert、delete、update
> + DDL（DDL Data Definition Language）：数据定义语言，代表关键字：create、drop、alter
> + TCL（TCL Transactional Control Language）：事务控制语言，代表关键字：commit、rollback
> + DCL（DCL Data Control Language）：数据控制语言，代表关键字：grant、revoke

## 1.1 数据库级命令

### 1.1.1 查看所有数据库

```mysql
show databases;
```

### 1.1.2 选择要操作的数据库

```mysql
use database_name;
```

### 1.1.3 创建数据库

```mysql
create database database_name;
```

### 1.1.4 执行 SQL 文件

```mysql
source .sql -- sql 文件的绝对路径
```

### 1.1.5 查看数据库版本

```mysql
select version();
```

### 1.1.6 查看目前正在操作的数据库

```mysql
select database();
```

### 1.1.7 查看 MySQL 支持哪些数据库

```mysql
show engines;
```

### 1.1.8 删除数据库

```mysql
drop database database_name;
```



## 1.2 表级命令

### 1.2.1 查看当前数据库下所有的表

```mysql
show tables;
```

### 1.2.2 查看表结构

```mysql
desc table_name;
```

### 1.2.3 查看建表语句

```mysql
show create table tablename;
```



## 1.3 DQL

```mysql
select
	...
from
	...
where
	...
group by
	...
having
	...
order by
	...
limit
	...
/*
	以上顺序不能颠倒，执行顺序是：
	1. from，选择好表
	2. where，从表中筛选数据
	3. group by，对筛选出的数据进行分组
	4. having，对分组后的数据再次过滤
	4. select，从过滤后的数据中挑选出要打印的字段
	5. order by，排序要打印的字段
	6. limit，选择要打印数据的范围
*/

```

### 1.3.1 为查询的列起别名

```mysql
select column_name as new_name from table_name;
-- as 关键字可以省略
select column_name new_name from table_name;
```

### 1.3.2 列可以参与数学运算

```mysql
select column_name * 12 as `yearly salary` from table_name; -- 字符串使用单引号是标准
```

### 1.3.3 条件查询

| 运算符           | 说明                                                         |
| ---------------- | ------------------------------------------------------------ |
| between...and... | 闭区间查找，等同于 >= and <=，使用时必须遵循左小右大的原则。 |
| is null          | **不能使用 = null 这种形式来判断是否为空，**必须使用 is null（is not null）。 |
| and              | 并且。                                                       |
| or               | 或者。                                                       |
| in               | 等于在集合中的某 1 个值，not in 表示不等于集合中的任意 1 个值，（相当于多个 or），**使用时要排除集合中的 NULL。** |
| not              | not 可以取非，主要用在 is 或 in 中。                         |
| like             | 模糊查询，支持 % 或下划线匹配，% 匹配任意个字符，_ 匹配任意 1 个字符。 |

```mysql
-- and 比 or 的优先级更高
-- 查找工资大于 2500，并且在部门 10 或者 20 的员工
select * from table_name where salary > 2500 and deptno = 10 or deptno = 20;	-- 错误写法
select * from table_name where salary > 2500 and (deptno = 10 or deptno = 20);	-- 正确写法
```

```mysql
-- 注意转义字符的使用
select * from table_name where name like `%\_%`;	-- 找出存在下划线的名字
```

### 1.3.4 排序

```mysql
select column_name from table_name order by column_name;		-- 默认是升序排序
select column_name from table_name order by column_name desc;	-- 指定降序
select column_name from table_name order by column_name asc;	-- 指定升序
```

```mysql
-- 多列排序，先按照 column_name1 升序排序，如果 column_name1 的值相等，再按照 column_name2 降序排序
select column_name1, column_name2 from table_name order by column_name1 asc, column_name2 desc;
```

### 1.3.5 单行处理函数

+ 单行处理函数：函数只对 1 行记录进行处理，每行记录对应 1 个输出。
+ 多行处理函数：函数对多行记录进行处理，多行记录对应 1 个输出。

| 函数                                    | 说明                                                         | SQL代码                                                      |
| --------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| lower                                   | 转换小写                                                     | select lower(name) from table_name;                          |
| upper                                   | 转换大写                                                     | select upper(name) from table_name;                          |
| substr                                  | 取子串，**MySQL 的索引从 1 开始**。<br/>参数 1 ：待处理的字段<br/>参数 2 ：起始索引<br/>参数 3 ：要截取的长度 | select substr(name, 1, 1) from table_name;                   |
| length                                  | 取长度                                                       | select length(name) from table_name;                         |
| trim                                    | 去空格                                                       | select trim(name) from table_name;                           |
| str_to_date                             | 字符串转换为日期<br/>格式：str_to_date('字符串日期'，'日期格式')<br/>MySQL的日期格式：<br/>%Y：年<br/>%m：月<br/>%d：日<br/>%h：时<br/>%i：分<br/>%s：秒<br/> | insert into t_user(id, name, birth) values(1, 'zhangsan', str_to_date('01-10-1990'), '%d-%m-%Y');<br/><br/>insert into t_user(id, name, birth) values(2, 'lisi', '2000-12-3');    -- 使用 MySQL 支持的格式 '年-月-日' 的话系统会自动将字符串转换为 date |
| date_format                             | date 类型转换为字符串类型。<br/>格式：date_format(日期字段, '日期格式')<br/>**查询的时候不用手动转换，系统会自动转换，如果需要按照指定格式显示才需要使用。** | select id, name, date_format(birth, '%m-%d-%Y') as birth from t_user; |
| format                                  | 设置千分位                                                   | -- 工资用千分位显示<br/>select ename, format(sal, '$999,999') as sal form emp; |
| round                                   | 四舍五入<br/>参数 1 ：待处理的字段<br/>参数 2 ：要保留的小数 | select round(salary, 0) from table_name;                     |
| rand                                    | 生成随机数                                                   | select rand() from table_name;                               |
| ifnull                                  | 可以将 null 转换成一个具体值<br/>（有 null 参与的运算结果一定为 null） | select (sal + ifnull(comm, 0)) * 12 as year_salary from table_name; |
| concat                                  | 字符串拼接，**不能直接使用加号进行字段之间的拼接**           | select concat(column_name1, column_name2) as new_column_name from table_name; |
| case..when..then..when..then..else..end | 类似编程语言中的 switch case                                 | select <br/>    ename,<br/>    job,<br/>    sal as oldsal,<br/>    (case job when \`MANAGER\` then sal * 1.1 when \`SALESMAN\` then sal * 1.5 else sal end) as newsal<br/>from<br/>    emp; |

### 1.3.6 多行处理函数

> 分组函数在使用的时候必须先进行分组（group by），如果没有手动分组，则整张表默认分为一组。

| 函数  | 说明     |
| ----- | -------- |
| min   | 求最小值 |
| max   | 求最大值 |
| avg   | 求平均值 |
| sum   | 求和     |
| count | 统计行数 |

```mysql
select min(salary), max(salary), avg(salary), sum(salary), count(salary) from table_name;
```

分组函数在使用的时候需要注意以下几点：

1. 分组函数自动忽略 null，不需要手动对 null 进行处理
2. 分组函数中 count(*) 和 count(字段) 的区别
   + count(字段) 统计的是当前字段下所有不为 null 的记录的总数。
   + count(*) 统计的是所有记录的总数。
3. 分组函数不能够直接使用在 where 子句中，因为根据 sql 语句的执行顺序，在 where 子句执行之前，还没有进行分组（group by 在 where 子句之后执行，在 select 之前执行）。

### 1.3.7 分组查询

> 在 1 条 select 语句中，如果存在 group by 子句的话，select 后面只能存在**分组字段**和**分组函数**。

```mysql
select column1, column2, sum(colomn3) from tablename group by column1, column2;
```

使用 having 可以对**分组完之后**的数据进一步过滤，having 不能单独使用，必须和 group by 联合使用。**但是 having 的效率比较低，如果可以使用 where 达到相同效果优先使用 where。**

```mysql
-- 找出每个部门的最高薪资，显示出大于 3000 的最高薪资
-- having 对分组求出来的最高工资进行过滤
select deptno, max(sal) from emp group by deptno having max(sal) > 3000;
-- 使用 where 可以达到和上面同样的效果
select deptno, max(sal) from emp where sal > 3000 group by deptno;
```

```mysql
-- 不能使用 where 代替
-- 找出每个部门平均薪资，要求显示平均薪资高于2500的
select deptno, avg(sal) from EMP group by deptno having avg(sal) > 2500;
```

### 1.3.8 去除重复记录

distinct 只能用在所有要 select 的字段的前面，表示后面的字段联合去重，distinct 可以在分组函数里面使用。

```mysql
-- 错误写法
select ename, distinct job from emp;

-- 正确写法，查看每个部门的工作岗位
select distinct job, deptno from emp;
```

```mysql
-- 统计工作岗位的数量
select count(distinct job) from emp;
```

### 1.3.9 内连接

> 连接查询的分类：
>
> 根据语法的年代分类：
>
> 1. SQL92
> 2. SQL99
>
> 根据表连接的方式分类：
>
> 1. 内连接
>    1. 等值连接
>    2. 非等值连接
>    3. 自连接
> 2. 外连接
>    1. 左连接
>    2. 右连接
> 3. 全连接（几乎不用）

笛卡尔积现象：当两张表进行连接查询时，如果没有任何的条件限制，会发生笛卡尔积现象。

```mysql
-- 发生笛卡尔积现象，查询出来的记录数量为 table1 的行数 * table2 的行数
select
	a.name, b.age
from
	table1 a
join
	table2 b;
```

```mysql
select
	a.name, b.age
from
	table1 a
join
	table2 b;
on
	a.number = b.number;
```

**虽然加了连接条件，但是匹配的次数并没有减少，匹配次数仍然是 table1 的行数 * table2 的行数，只是查询出来的记录数量减少了，所以减少表的连接次数才能使得效率更高。**

**注意：连接查询时对表起别命很重要，能提升查询效率。**

SQL92 和 SQL99 的语法区别：

```mysql
-- SQL92
select
	a.column, b.column
from
	a_table a, b_table b
where
	a.number = b.number;
```

```mysql
-- SQL99
select
	a.column, b.column
from
	a_table a
inner join		-- inner 可以省略
	b_table b
on
	a.number = b.number;
where
	......
```

SQL92 的语法已经过时~，其将连接条件和记录筛选条件混合在 where 子句中，结构不清晰。

SQL99 的表连接条件是独立的，连接之后如果还需要进一步筛选，再往后继续添加 where。

#### 1.3.9.1 等值连接

> 连接条件用等于来判断

```mysql
-- 联合查询员工表和部门表，显示员工姓名和所在的部门名
select e.ename, d.dname from EMP e join DEPT d on e.deptno = d.deptno;
```

#### 1.3.9.2 非等值连接

> 连接条件不是使用等于号来判断

```mysql
-- 联合查询员工表和薪资等级表，显示员工姓名、工资、工资等级
select e.ename, e.sal, s.grade from EMP e join SALGRADE s on sal between s.losal and s.hisal;
```

#### 1.3.9.3 自连接

> 一张表看作两张表，两个表进行连接查询。

```mysql
-- 查看员工姓名和其直接领导
select e1.ename, e2.ename from EMP e1 join EMP e2  on e1.mgr = e2.empno;
```

### 1.3.10 外连接

> 内连接的两张表之间是没有主次关系的，左连接的左表是主表，右连接的右表是主表，任何一个左连接都有右连接的写法，任何一个右连接都有左连接的写法。
>
> 内连接的特点：将能匹配连接条件的记录查询出来。
>
> 外连接的特点：主要是为了将主表中的数据查询出来，然后再查询出满足连接条件的记录。
>
> **外连接的查询记录数量 >= 内连接的查询记录数量**

```mysql
-- 查询所有部门名称和其拥有的员工，因为可能存在部门还没有员工，所以不能只使用内连接
select e.ename, d.dname from EMP e right join DEPT d on e.deptno = d.deptno;
-- 等价的左连接，outer 可以省略
select e.ename, d.dname from DEPT d left outer join EMP e on e.deptno = d.deptno;
```

```mysql
-- 查询每个员工的员工名，要求显示所有员工的名字和领导名
-- 由于老板是最大领导，其 mgr is null，所以必须使用外连接
select e1.ename, e2.ename from EMP e1 left join EMP e2 on e1.MGR = e2.empno;
```

### 1.3.11 多表连接

多表连接可以理解为前面的表连接后的结果再和后面的表迭代进行连接，也可以理解为第 1 张依次和后面的表进行连接。

```mysql
-- 找出每个员工的部门名称以及工资等级，要求显示员工名、部门名、薪资、薪资等级
select 
	e.ename, d.dname, e.sal, s.grade 
from 
	EMP e 
join 
	DEPT d 
on 
	e.deptno = d.deptno 
join 
	SALGRADE s 
on 
	e.sal between s.losal and s.hisal;
```

```mysql
-- 找出每个员工的部门名称以及工资等级，还有上级领导，要求显示员工名、领导名、部门名、薪资、薪资等级？
select 
	e1.ename, e2.ename, d.dname, e1.sal, s.grade
from 
	EMP e1
left join 	-- 这里需要使用外连接，因为老板的 e1.mgr is null，如果不使用外连接的话老板的信息不会显示
	EMP e2
on 
	e1.mgr = e2.empno
join 
	DEPT d
on 
	e1.deptno = d.deptno
join 
	SALGRADE s
on 
	e1.sal between s.losal and s.hisal;
```

### 1.3.12 子查询

> select 语句中嵌套 select 语句，被嵌套的 select 语句成为子查询。

#### 1.3.12.1 where 子句中的子查询

```mysql
-- 找出比最低工资高的员工姓名和工资？
select ename, sal from EMP where sal > (select min(sal) from EMP);
-- 注意，in 后面也可以添加子查询，in(select *)
```

#### 1.3.12.2 from 子句中的子查询

```mysql
-- 找出每个岗位的平均工资的薪资等级
select 
	tmp.job, tmp.avgsal, s.grade 
from 
	(select job, avg(sal) as avgsal from EMP group by job) tmp 
join 
	SALGRADE s 
on 
	tmp.avgsal between s.losal and s.hisal;
```

#### 1.3.12.3 select 中出现的子查询

```mysql
-- 找出每个员工的部门名称，要求显示员工名，部门名
select 
	e.ename,e.deptno,(select d.dname from dept d where e.deptno = d.deptno) as dname 
from 
	emp e;
```

**select 子查询不常用，且 select 这个子查询只能一次返回  1 条记录。**

### 1.3.13 union

> 将查询结果组合在一起

```mysql
-- 查询工作岗位是MANAGER和SALESMAN的员工？
select ename,job from emp where job = 'MANAGER' or job = 'SALESMAN';	-- 不使用 union
select ename,job from emp where job in('MANAGER','SALESMAN');

select ename,job from emp where job = 'MANAGER'		-- 使用 union
union
select ename,job from emp where job = 'SALESMAN';
```

在使用 union 时，多个结果集的列数要相同。

**union 相对于表连接，效果更高，因为 union 减少了匹配的次数。**

### 1.3.14 limit

> limit 将查询结果集的一部分取出来，通常使用在分页中。

limit 的语法：limit startIndex, length

+ startIndex：起始下标，从 0 开始，（聚合函数 substr 的起始索引是 1）。
+ length：长度

limit 的缺省用法：limit 数字 number，表示显示前 number 条记录。

limit 在 order by 之后执行

```mysql
-- 按照薪资降序，取出排名在前 5 名的员工
select 
	ename,sal
from
	emp
order by 
	sal desc
limit 5;	-- 使用缺省用法

select 
	ename,sal
from
	emp
order by 
	sal desc
limit 0,5;	-- 完整用法
```

分页公式

```mysql
每页显示3条记录
	第1页：limit 0,3		[0 1 2]
	第2页：limit 3,3		[3 4 5]
	第3页：limit 6,3		[6 7 8]
	第4页：limit 9,3		[9 10 11]
	
每页显示 pageSize 条记录
	第 pageNo 页：limit (pageNo - 1) * pageSize , pageSize
```



## 1.4 DDL

### 1.4.1 建表

```mysql
create table_name (
    column_name, type,
    column_name, type,
    ……
);

-- 用查询结果来快速建立一张表
create table tablename select * from emp;
```

MySQL 常见的数据类型

| 数据类型 | 说明                                                         |
| -------- | ------------------------------------------------------------ |
| varchar  | 可变长度字符串，最长 255 ，根据实际存储的字符串长度来动态分配空间。<br/>优点：节省空间，缺点：速度慢 |
| char     | 固定长度字符串，最长 255。<br/>优点：速度快，缺点：容易造成空间浪费 |
| int      | 最长 11                                                      |
| bigint   | 相当于 long                                                  |
| float    | 单精度浮点型                                                 |
| double   | 双精度浮点型                                                 |
| data     | 短日期类型，MySQL 默认的日期格式为 '年-月-日' : '2022-06-11'<br/>使用这种格式可以不使用 str_to_data 来将字符串转换成 data，MySQL 会自动转换 |
| datatime | 长日期类型，MySQL 默认的格式为 '年-月-日 时-分-秒' : '2022-06-11 12:20:12'<br/>使用这种格式 MySQL 会自动转换<br/>**now() 函数可以获得当前系统时间，类型就是 datatime** |
| clob     | 字符大对象，最多存储 4G 的字符串。                           |
| blob     | 二进制大对象，存储图片、声音、视频等流媒体数据，必须使用 IO 流来插入数据。 |

### 1.4.2 删表

```mysql
drop table if exists tablename;
```

### 1.4.3 修改表名

```mysql
alter table tablename rename to new_table_name;
```



### 1.4.4 添加字段

```mysql
alter table tablename add column_name type;

-- 新增字段到第一列
alter table tablename add column_name type first;

-- 新增字段到字段 column_name 列后面
alter table tablename add column_name_new type after column_name;
```

### 1.4.5 更新字段

```mysql
-- 使用 modify 修改字段 column_name 的类型为 new_type
alter table tablename modify column_name new_type;

-- 更新字段时可以指定 not null 和默认值
alter table tablename modify column_name new_type not null default xxx;

-- 修改字段默认值
alter table tablename alter column_name set default xxx;

-- 删除字段默认值
alter table tablename alter column_name drop default;

-- 使用 change 修改字段，change 后面紧跟要修改的字段名、新字段名、新字段类型
alter table tablename change column_name_old column_name_new type;
```

### 1.4.6 删除字段

```mysql
alter table tablename drop column_name;
```



## 1.5 DML

### 1.5.1 插入数据

```mysql
-- 字段名和值一一对应
insert into tablename(column_name1, column_name2, ……) values(value1, value2, ……);
-- 可是只写某几个字段
inset into tablename(column_name3) values(value3);

-- 省略字段名，缺省就是写上所有的字段名
insert into talbename values(value1, value2, value3, value4);	-- 写上所有的 value

-- 一次插入多条记录
insert into tablename(column_name1, column_name2, ……) values
(value1, value2, ……),
(value1, value2, ……),
(value1, value2, ……);

-- 将查询结果插入到一张表中
insert into tablename select * from tablename;
```

### 1.5.2 更新数据

```mysql
-- 如果没有 where 条件则会更新全部记录
update tablename set column_name1 = value1, column_nam2 = value2, …… where ……
```

### 1.5.3 删除数据

```mysql
-- 如果没有 where 条件则会删除全部记录
delete from tablename where ……

-- 使用 delete 删除数据可以回滚，使用 truncate 不可以回滚
-- delete 优点：可以回滚	缺点：存储空间不会被释放、效率低
-- truncate 优点：效率高	缺点：不可以恢复
truncate table tablename; -- truncate 属于 DDL
```



# 二、约束

> 约束是为了保证表中的数据有效，当多个字段需要联合添加某一个约束时使用表级约束

| 约束       | 代码                               |
| ---------- | ---------------------------------- |
| 非空约束   | not null，只能通过列级约束设定     |
| 唯一性约束 | unique                             |
| 主键约束   | primary key                        |
| 外键约束   | foreign key                        |
| 检查约束   | check（MySQL 不支持，oracle 支持） |

## 2.1 非空约束

```mysql
create tablename (
    columu_name1 int not null,	-- 只能通过列级约束设定
    column_name2
);
```

## 2.2 唯一性约束

> 被唯一性约束的字段不能重复但是可以 is null

```mysql
-- 单个字段 unique
create tablename (
    column_name1 int,
    column_name2 varchar(255) unique
);
```

```mysql
-- 多个字段联合 unique
create tablename (
    column_name1 int,
    column_name2 varchar(255),
    unique(column_name1, column_name2)
);
```

**注意：在 MySQL 中当某个字段同时被 not null 和 unique 修饰时会自动成为主键。**

## 2.3 主键约束

> 主键（not null + unique）是一行记录的唯一标识，所以一张表必须存在主键字段，且只能存在一个主键字段

```mysql
create tablename (
    column_name1 int primary key,	-- 单一主键，使用列级约束
    column_name2 varchar(255)
);
```

```mysql
create tablename (
	column_name1 int,
    column_name2 varchar(255),
    primary key(column_name1)	-- 单一主键，使用表级约束
);

create tablename (
	column_name1 int,
    column_name2 varchar(255),
    primary key(column_name1, column_name2)	-- 复合主键，必须使用表级约束
);
```

**注意：实际开发中不建议使用复合主键，一般使用单一主键，主键存在的意义是为了唯一的标识一条记录，单一主键就可以做到。**

```mysql
create tablename (
	column_name1 int primary key auto_increment,	-- 主键从 1 开始自增
    column_name2 varchar(255)
);
```

**注意：主键除了单一主键和复合主键还可以分为自然主键和业务主键，开发中一般使用自然主键，若使用业务主键，当业务信息发生变动时可能需要修改主键。**

## 2.4 外键约束

被外键引用的表成为**父表**，存在外键的表成为**子表**。

> 外键存在的意义是为了保证外键字段的数据的有效性，否则可能会发生外键字段值不存在于父表中；

父表中被引用的外键**不一定要求是主键，但要求具有 unique 约束，且子表中的外键可以是 null。**

```mysql
create tablename (
	column_name1 int primary key,
    column_name2 varchar(255),
    foreign key(column_name2) references tablename2(column_name3)	-- 子表的外键字段名和被引用的父表外键字段名可以不一样
);
```

## 2.5 删除约束

```mysql
-- 删除外键约束
alter table tablename drop foreign key foreign_key_name;

-- 删除主键
alter table tablename drop primary key;
```



# 三、存储引擎

> 存储引擎是 MySQL 独有的，其他数据库没有，存储引擎是一种存储/组织表的方式，不同的存储引擎，存储/组织表的方式不同。

```mysql
-- 建表时指定存储引擎
create table (
	column_name1 int primary key,
    column_name2 varchar(255),
    foreign key(column_name2) references tablename(column_name3)
)engine = Innodb default charset = utf8;
```

## 3.1 Innode

MySQL 默认的存储引擎是 Innodb，默认的字符集是 utf8，Innodb 支持事务，但是效率不高。

使用 Innode 引擎的表使用 .frm 格式文件存储表的结构定义，使用表空间 tablespace 存储表的内容（数据 + 索引）。

## 3.2 MyISAM

使用 MyISAM 引擎的表使用 3 个文件来存储组织：

+ 格式文件：存储表结构的定义（.frm)
+ 数据文件：表的内容（.MYD)
+ 索引文件：索引（.MYI）

MyISAM 存储引擎的优点：可以被压缩节省空间、将表设置为只读提升效率。

缺点：不支持事务，安全性低。

## 3.3 MEMORY

数据存储在内存中且行的长度固定，所以访问表速度快。

使用 MEMORY 引擎的表使用 .frm 格式文件存储表的结构定义，数据和索引存储在内存中，所以不能包含 TEXT 或 BLOB 字段，且关机后数据消失。



# 四、事务

> 一个事务就是一个完整的业务逻辑，事务包含的 DML 语句要么一起执行成功，要么全部不执行。

只有 DML 语句（insert、delete、update）才有事务一说，其他语句和事务无关。

```mysql
-- 开启事务
start transaction;

insert ……
delete ……
update ……

-- 回滚
rollback;

-- 提交
commit;
```

在 MySQL 中若不手动开启事务（start transaction）则默认每一条 DML 语句执行完成后都进行事务提交。

## 4.1 事务的特性

1. 原子性：一个事务是最小的执行单元，不可再分。
2. 一致性：事务中的 DML 操作要么全部成功，要么全部不执行。
3. 隔离性：事务与事务之间的执行相互不影响。
4. 持久性：事务提交之后保证数据会持久化到数据库中。

## 4.2 事务的隔离性

### 4.2.1 读未提交

当前事务可以读取到其他事务修改过但是未提交的数据。

存在**脏读、不可重复读、幻读**问题。

### 4.2.2 读已提交

当前事务可以读取到其他事务修改过但是已提交之后的数据。

存在**不可重复读、幻读**问题。

### 4.2.3 可重复读

MySQL 默认的隔离级别，当前事务读取到数据从始至终只有一个版本。

当前事务**首次**开始读数据时生成一个快照，**不是**事务一开始就生成一个数据快照。

### 4.2.4 串行化

事务之间不能并发的操作一张表。

若多个事务同时操作一张表，经过实验阻塞情况如下：

+ 当前事务进行 select 查询时，若其他事务针对当前表都只进行了 select，则当前事务的 select 不会被阻塞；若其他事务对表进行了 DML 操作，则当前事务的 select 会被阻塞，**等对表进行 DML 操作的事务 commit 之后查询才成功。**
+ 当前事务进行 DML 操作时，若其他事务针对当前表进行过 select/DML 操作，当前 DML 操作都会被阻塞，**直到其他事务全部 commit 之后才可以进行 DML 操作。**

```mysql
-- 查看当前的隔离级别
select @@transaction_isolation;

-- 设置隔离级别，注意设置完之后的隔离级别对已打开的 MySQL 会话不生效，所以最好 exit 后重进
set global transaction isolation level read committed;

create table student(
	sno int primary key auto_increment,
    sname varchar(255) not null
);
```



# 五、索引

## 5.1 理论知识

> 对没有添加索引的字段进行查找或者索引失效的情况下进行查找都会进行全表扫描；索引相当于一本书的目录，建立排序好的索引可以缩小数据扫描范围。

1. 主键会被默认添加索引，并且在 MySQL 中被 unique 约束的字段也会自动添加索引。
2. 表的每一条记录在硬盘存储上都有一个硬盘的物理存储编号。
3. 索引是一个单独的对象，不同的存储引擎以不同的形式存储索引；MyISAM 将索引存储在 .MYI 文件中，Innode 将索引存储在 tablespace 中，MEMEORY 将索引存储在内存中。

以下情况考虑给字段添加索引：

1. 数据量庞大
2. 该字段经常出现在 where 后面
3. 该字段很少被进行 DML 操作，因为 DML 之后索引需要重新排序

> 不能随便添加索引，因为索引需要维护，太多反而降低系统性能；
>
> 通过**主键**和**unique**字段进行查询时效率比较高。

## 5.2 创建和删除索引

```mysql
-- 查看一条 SQL 语句是否使用了索引，type = ALL 说明没有使用索引，还可以看扫描的记录数
explain select * from tablename where ……
```

```mysql
-- 创建索引
create index index_name on tablename(column_name);

-- 创建复合索引
create index index_name on tablename(column_name1, column_name2);
```

```mysql
-- 删除索引
drop index index_name on tablename;
```

## 5.3 索引失效

1. 使用 % 开头的模糊匹配

   ```mysql
   -- 避免 % 开头的模糊匹配，因为会导致索引失效
   select * from tablename where name like '%ack';
   ```

2. 使用 or 时只有 1 个字段上存在索引

   ```mysql
   -- id 和 name 两个字段都有索引时索引才有效，其他情况索引都会失效，可以使用 union 代替 or
   select * from tablename where id = xxx or name = 'xxx';
   ```

3. 使用复合索引时，没有使用左侧的字段进行查找

   ```mysql
   -- 假设 (column_name1, column_name2) 是复合索引
   select * from tablename where column_name2 = 'xxx';	-- 经测试索引失效
   select * from tablename where column_name1 = 'xxx'; -- 索引有效
   ```

4. 索引字段参与了运算

   ```mysql
   select * from tablename where column_name + 1 = 800;
   ```

5. 对索引字段使用了函数

   ```mysql
   select * from tablename where lower(column_name) = 'zhangsan';
   ```

## 5.4 索引的分类

另外找资料补充



# 六、视图

> 站在不同的角度去看待同一份数据，一个视图就像是一张表

## 6.1 创建和删除视图

> 只有 DQL 语句才能以 view 的形式创建

```mysql
-- 创建视图
create view view_name as select * from tablename where ……
```

```mysql
-- 删除视图
drop view view_name;
```

**show tables 发现新建的视图也在其中；删除原表后视图仍然存在，但是已经不能对视图进行任何操作。**

## 6.2 视图的用处

1. 修改视图中的数据，原表的数据也会被修改
2. 简化复杂的 DQL 语句，对于一条十分复杂冗长并且需要经常编写的 DQL 语句，可以使用视图来存储该语句的结果，不仅可以隐藏表的实现细节，以后通过对视图进行操作就能更快速的达到效果，并且利于维护，以后要修改该 DQL 语句只需要修改一次即可。
3. 对不同用户显示表中的不同数据



# 七、数据的导入和到处

## 7.1 导入数据

```mysql
-- source 后面跟绝对路径
-- 一般要先执行以下步骤之后再执行 source
-- 1. create database database_name;
-- 2. use database_name;
source xxx/xxx.sql;
```

## 7.2 导出数据

```mysql
-- database_name 是 MySQL 中的数据库名称，> 后面是要导出的文件路径
mysqldump database_name>xxx/xxx.sql -uroot -ppassword

-- 导出数据库中的某张表
mysqldump database_name tablename>xxx/xxx.sql -uroot -ppassword
```



# 八、数据库三大范式

## 8.1 第一范式

> 要求表必须有主键，且表中每一个字段不可再拆分

| 学生编号 | 学生姓名 | 联系方式                 |
| -------- | -------- | ------------------------ |
| 1001     | 张三     | zs@gmail.com,1359999999  |
| 1002     | 李四     | ls@gmail.com,13699999999 |
| 1003     | 王五     | ww@163.net,13488888888   |

以上表**没有主键、联系方式可以拆分为邮箱和电话。**

解决方案：设置主键并且拆分联系方式为邮箱和电话。

## 8.2 第二范式

> 在第一范式的基础上，要求所有非主键字段必须完全依赖于主键，没有部分依赖

| 学生编号 | 学生姓名 | 教师编号 | 教师姓名 |
| -------- | -------- | -------- | -------- |
| 1001     | 张三     | 001      | 王老师   |
| 1002     | 李四     | 002      | 赵老师   |
| 1003     | 王五     | 001      | 王老师   |
| 1001     | 张三     | 002      | 赵老师   |

这张表的学生和老师是多对多的关系。

此表不满足第一范式，将**学生编号和教师编号作为联合主键**之后才满足第一范式。

由于**教师姓名字段依赖于教师编号字段**，所以存在非主键字段没有完全依赖于主键，所以不满足第二范式。

**规律：对于以上这种多对多的关系，需要设计 3 张表：学生表、教师表、学生教师关系表，关系表中存在学生编号、教师编号两个外键。**

## 8.3 第三范式

> 第三范式建立在第二范式的基础上，要求所有非主键字段必须直接依赖于主键，不能存在传递依赖。

| 学生编号 | 学生姓名 | 班级编号 | 班级名称 |
| -------- | -------- | -------- | -------- |
| 1001     | 张三     | 01       | 一年一班 |
| 1002     | 李四     | 02       | 一年二班 |
| 1003     | 王五     | 03       | 一年三班 |
| 1001     | 张三     | 03       | 一年三班 |

由于存在主键且主键不是复合主键，所以符合第二范式，但是班级名称依赖班级编号，班级编号依赖学生编号，产生了传递依赖，不符合第三范式的要求。

**规律：对于以上这种一对多的关系，需要设计 2 张表：学生表、班级表；学生表需要将班级编号作为外键。**

**规律：对于一对一的关系，如果一张表中字段太多，也是可能需要拆分的，对于拆分出来的第二场表，需要将主表的主键作为外键，并将该外键添加 unique 约束。**

> 数据库设计的三范式要求是理论上的，实际开发过程中为了提高速度可能会用数据的冗余换取速度，因为在多表查询的时候会存在笛卡尔积现象，数据冗余可以减少表的连接次数。

> 问题 1 ：where 后面的条件字段都各自有索引，依据各字段索引查找的先后顺序是？
>
> 问题 2 ：使用 or 导致索引失效的原因
>
> 问题 3 ： 使用复合索引的右侧索引会失效的原因



# 九、练习题

## 9.1 取得每个部门最高薪水的人员名称

```mysql
select
	e.ename, tmp.sal sal, e.deptno
from
	(select deptno, max(sal) sal from EMP group by deptno) tmp
join
	EMP e
on
	e.sal = tmp.sal;
```

## 9.2 哪些人的薪水在部门的平均薪水之上

```mysql
select
	e.ename, e.sal
from
	(select avg(sal) sal, deptno from EMP group by deptno) as tmp
join
	EMP e
on
	e.deptno = tmp.deptno
where
	e.sal > tmp.sal;
```

## 9.3 取得部门中（所有人的）平均的薪水等级

```mysql
select
	e.deptno, avg(s.grade)
from
	EMP e
join
	SALGRADE s
on
	e.sal between s.losal and s.hisal
group by
	e.deptno;
```

## 9.4 不准用组函数（Max），取得最高薪水（给出两种解决方案）

```mysql
-- 排序取第 1 条数据
select
	e.sal
from
	EMP e
group by
	e.sal
order by
	e.sal desc
limit
	1;
```

```mysql
-- 表的自连接
select
	sal
from
	EMP
where 
	sal not in(
        select
            distinct a.sal
        from
            EMP a
        join
            EMP b
        on
            a.sal < b.sal
	);
```

## 9.5 取得平均薪水最高的部门的部门编号（至少给出两种解决方案）

```mysql
select
	e.deptno, avg(e.sal)
from
	EMP e
group by
	e.deptno
order by
	avg(e.sal) desc
limit 1;
```

```mysql
select
	e.deptno, avg(e.sal)
from
	EMP e
group by
	e.deptno
having
	avg(e.sal) = 
    (
        select
            max(tmp.avg_sal)
        from
            (
                select
                    e.deptno as deptno, avg(e.sal) avg_sal
                 from
                    EMP e
                 group by
                    e.deptno
            ) tmp
    );
```

## 9.6 取得平均薪水最高的部门的部门名称

```mysql
select
	d.dname, avg(e.sal) avg_sal
from
	EMP e
join
	DEPT d
on
	e.deptno = d.deptno
group by
	d.dname
order by
	avg_sal desc
limit
	1;
```

## 9.7 求平均薪水的等级最低的部门的部门名称

```mysql
select
	tmp.*, s.grade
from
    (select
        d.dname, avg(e.sal) avg_sal
    from
        EMP e
    join
        DEPT d
    on
        e.deptno = d.deptno
    group by
        d.dname) tmp
join
	SALGRADE s
on
	tmp.avg_sal between s.losal and s.hisal
where
	s.grade =
	(
    	select
            s.grade
        from
            (select
                deptno, avg(sal) avg_sal
            from
                EMP e
            group by
                deptno) tmp
        join
            SALGRADE s
        on
            tmp.avg_sal between s.losal and s.hisal
        order by
            s.grade
        limit
            1
    );
```

## 9.8 取得比普通员工(员工代码没有在mgr字段上出现的)的最高薪水还要高的领导人姓名

```mysql
select
	ename 
from
	EMP 
where 
	sal > (select max(sal) from EMP where EMPNO not in (select distinct MGR from EMP where MGR is not NULL));
```

## 9.9 取得薪水最高的前五名员工

```mysql
select * from EMP order by sal desc limit 5;
```

## 9.10 取得薪水最高的第六到第十名员工

```mysql
select * from EMP order by sal desc limit 5, 5;
```

## 9.11 取得最后入职的5名员工

```mysql
select * from EMP order by HIREDATE desc limit 5;
```

## 9.12 取得每个薪水等级有多少员工

```mysql
select tmp.GRADE, count(tmp.GRADE) from (select e.*, s.GRADE from EMP e join SALGRADE s on e.sal between s.losal and hisal) tmp group by tmp.GRADE;
```

## 9.13 面试题

有 3 个表：S（学生表）、C（课程表）、SC（学生选课表）

S（SNO，SNAME）—— （学号，姓名）

C（CNO，CNAME，CTEACHER）——（课号，课名，教师）

SC（SNO，CNO，SCGRADE）——（学号，课号，成绩）

```mysql
start transaction;
CREATE TABLE SC (
    SNO VARCHAR(200),
    CNO VARCHAR(200),
    SCGRADE VARCHAR(200)
);

CREATE TABLE S (
    SNO VARCHAR(200 ),
    SNAME VARCHAR(200)
);

CREATE TABLE C (
    CNO VARCHAR(200),
    CNAME VARCHAR(200),
    CTEACHER VARCHAR(200)
);
INSERT INTO C ( CNO, CNAME, CTEACHER ) VALUES ( '1', '语文', '张');
INSERT INTO C ( CNO, CNAME, CTEACHER ) VALUES ( '2', '政治', '王');
INSERT INTO C ( CNO, CNAME, CTEACHER ) VALUES ( '3', '英语', '李');
INSERT INTO C ( CNO, CNAME, CTEACHER ) VALUES ( '4', '数学', '赵');
INSERT INTO C ( CNO, CNAME, CTEACHER ) VALUES ( '5', '物理', '黎明');
commit;

INSERT INTO S ( SNO, SNAME ) VALUES ( '1', '学生 1');
INSERT INTO S ( SNO, SNAME ) VALUES ( '2', '学生 2');
INSERT INTO S ( SNO, SNAME ) VALUES ( '3', '学生 3');
INSERT INTO S ( SNO, SNAME ) VALUES ( '4', '学生 4');
commit;

INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '1', '1', '40');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '1', '2', '30');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '1', '3', '20');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '1', '4', '80');

INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '1', '5', '60');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '2', '1', '60');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '2', '2', '60');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '2', '3', '60');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '2', '4', '60');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '2', '5', '40');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '3', '1', '60');
INSERT INTO SC ( SNO, CNO, SCGRADE ) VALUES ( '3', '3', '80');
commit;
```

问题：

1. 找出没选过"黎明"老师的所有学生姓名

   ```mysql
   select sno,sname
   from S
   where sno not in(select sno from SC where cno = (select cno from C where cteacher = '黎明'));
   ```

2. 列出 2 门以上（含 2 门）不及格学生姓名及平均成绩

   ```mysql
   select s.sname, avg(sc.scgrade)
   from S s
   join SC sc
   on s.sno = sc.sno
   where s.sno = (select SNO from SC where scgrade < 60 group by SNO having count(scgrade) >= 2)
   group by s.sname;
   ```

3. 即学过 1 号课程又学过 2 号课所有学生的姓名

   ```mysql
   select s.sname
   from S s
   join SC sc
   on s.sno = sc.sno
   where sc.cno = 1 and sc.sno in (select sno from SC where cno = 2);
   ```

## 9.14 列出所有员工及领导的姓名

```mysql
select a.ename, b.ename
from EMP a
left join EMP b
on a.mgr = b.empno;
```

## 9.15 列出受雇日期早于其直接上级的所有员工的编号,姓名,部门名称

```mysql
SELECT a.empno, a.ename, d.dname
FROM EMP a
JOIN EMP b
on a.mgr = b.empno
JOIN DEPT d
on a.deptno = d.deptno
where a.HIREDATE < b.HIREDATE;
```

## 9.16 列出部门名称和这些部门的员工信息,同时列出那些没有员工的部门

```mysql
SELECT d.dname, e.*
FROM DEPT d
LEFT JOIN EMP e
ON d.deptno = e.deptno;
```

## 9.17 列出至少有5个员工的所有部门

```mysql
SELECT d.dname, count(d.dname)
FROM DEPT d
JOIN EMP e
ON d.deptno = e.deptno
GROUP BY d.dname
having count(d.dname) >= 5;
```

## 9.18 列出薪金比"SMITH"多的所有员工信息

```mysql
select * from EMP where sal > (select sal from EMP where ename = 'SMITH');
```

## 9.19 列出所有"CLERK"(办事员)的姓名及其部门名称,部门的人数

```mysql
-- 每个部门的人数
SELECT E.DEPTNO, COUNT(E.DEPTNO) AS NUM from EMP E JOIN DEPT D ON E.DEPTNO = D.DEPTNO GROUP BY E.DEPTNO;

SELECT E.ENAME, D.DNAME, TMP.NUM 
FROM EMP E 
JOIN DEPT D 
ON E.DEPTNO = D.DEPTNO 
JOIN (SELECT E.DEPTNO, COUNT(E.DEPTNO) AS NUM from EMP E JOIN DEPT D ON E.DEPTNO = D.DEPTNO GROUP BY E.DEPTNO) TMP
ON E.DEPTNO = TMP.DEPTNO
WHERE JOB = 'CLERK';
```

## 9.20 列出最低薪金大于1500的各种工作及从事此工作的全部雇员人数

```mysql
select job, count(job) from EMP group by job having min(sal) > 1500;
```

## 9.21 列出在部门"SALES"<销售部>工作的员工的姓名,假定不知道销售部的部门编号

```mysql
select e.ename, d.dname
from EMP e
join DEPT d
on e.deptno = d.deptno and d.dname = 'SALES';
```

##  9.22 列出薪金高于公司平均薪金的所有员工,所在部门,上级领导,雇员的工资等级

```mysql
select a.ename, d.dname, b.ename, s.grade
from EMP a
join DEPT d
on a.deptno = d.deptno
left join EMP b
on a.mgr = b.empno
join SALGRADE s
on a.sal between s.losal and s.hisal
where a.sal > (select avg(sal) from EMP);
```

## 9.23 列出与"SCOTT"从事相同工作的所有员工及部门名称

```mysql
select e.ename, d.dname
from EMP e
join DEPT d
on e.deptno = d.deptno and e.ename != 'SCOTT' and e.job = (select job from EMP where ename = 'SCOTT');
```

## 9.24 列出薪金等于部门30中员工的薪金的其他员工的姓名和薪金

```mysql
select ename, sal from EMP where deptno != 30 and sal in (select sal from EMP where deptno = 30);
```

## 9.25 列出薪金高于在部门30工作的所有员工的薪金的员工姓名和薪金.部门名称

```mysql
select e.ename, e.sal, d.dname
from EMP e
join DEPT d
on e.sal > (select max(sal) from EMP where deptno = 30) and e.deptno = d.deptno;
```

## 9.26 列出在每个部门工作的员工数量,平均工资和平均服务期限

```mysql
select d.deptno, count(e.deptno), avg(sal), avg(timestampdiff(YEAR, e.hiredate, now()))
from DEPT d
left join EMP e
on d.deptno = e.deptno
group by d.deptno;
```

## 9.27 列出所有员工的姓名、部门名称和工资

```mysql
select e.ename, d.dname, e.sal
from EMP e
join DEPT d
on e.deptno = d.deptno;
```

## 9.28 列出所有部门的详细信息和人数

```mysql
select d.*, tmp.num
from DEPT d
join (select d.deptno, count(e.deptno) as num from EMP e right join DEPT d on e.deptno = d.deptno group by d.deptno) tmp
on d.deptno = tmp.deptno;
```

## 9.29 列出各种工作的最低工资及从事此工作的雇员姓名

```mysql
select e.ename, tmp.job, tmp.min_sal
from EMP e
join (select job, min(sal) min_sal from EMP group by job) tmp
on e.job = tmp.job and e.sal = tmp.min_sal;
```

## 9.30 列出各个部门的MANAGER(领导)的最低薪金

```mysql
select deptno, min(sal)
from EMP
where job = 'MANAGER'
group by deptno;
```

## 9.31 列出所有员工的年工资,按年薪从低到高排序

```mysql
select ename, (sal + ifnull(comm, 0)) * 12 year_sal
from EMP
order by year_sal;
```

## 9.32 求出员工领导的薪水超过3000的员工名称与领导名称

```mysql
select a.ename, b.ename
from EMP a
join EMP b
on a.mgr = b.empno and b.sal > 3000;
```

## 9.33 求出部门名称中,带'S'字符的部门员工的工资合计、部门人数

```mysql
select * from DEPT where dname like '%S%';

select tmp.dname, sum(sal), count(e.deptno)
from (select * from DEPT where dname like '%S%') tmp
left join EMP e
on tmp.deptno = e.deptno
group by tmp.dname;
```

## 9.34 给任职日期超过30年的员工加薪10%

```mysql
select ename, sal * 1.1
from EMP
where timestampdiff(YEAR, hiredate, now()) > 30;
```