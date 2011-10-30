-- CS 348: Project 3              --
-- Author: Joe Martella           --
-- Date: 11/08/2011               -- 

-- Script that creates the tables --

-- create STUDENT table --
create table student (
	snum      integer       not null check(snum >= 0),
	sname     varchar2(30)  not null,
	major     varchar2(30),
	slevel    varchar2(30),
	age       integer       check(age >= 15 AND age <= 99),
	primary key (snum)
);

-- create FACULTY table --
create table faculty (
	fid       integer       not null check(fid >= 0),
	fname     varchar2(30)  not null,
	deptid    integer       not null check(deptid >= 0),
	primary key (fid)
);

-- create CLASS table --
create table class (
	name      varchar2(30)  not null,
	meets_at  date,
	room      varchar2(30),  
	fid       integer       not null check(fid >= 0),
	primary key (name),
	foreign key (fid) references faculty
);

-- create ENROLLED table --
create table enrolled (
	snum      integer       not null check(snum >= 0),
	cname     varchar2(30)  not null,
	primary key (snum, cname)
);

-- create DEPARTMENT table --
create table department (
	deptid    integer       not null check(deptid >= 0),
	dname     varchar2(30)  not null,
	location  varchar2(30)  not null,
	primary key (deptid)
);
