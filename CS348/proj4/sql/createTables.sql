-- CS 348: Project 4              --
-- Author: Joe Martella           --
-- Date: 12/01/2011               -- 

-- Script that creates the tables --

-- create STUDENT table --
create table student (
	snum      integer       not null check(snum >= 0),
	sname     varchar2(30)  not null,
	major     varchar2(30),
	slevel    varchar2(30),
	password varchar2(30),
	primary key (snum)
);

-- create FACULTY table --
create table faculty (
	fid       integer       not null check(fid >= 0),
	fname     varchar2(30)  not null,
	password varchar2(30),
	primary key (fid)
);

-- create CLASS table --
create table class (
	cname      varchar2(30)  not null,
	semester varchar2(30),
	year integer, 
	meets_at  timestamp,
	room      varchar2(30),  
	fid       integer       not null check(fid >= 0),
	primary key (cname)
);

-- create ENROLLED table --
create table enrolled (
	snum      integer       not null check(snum >= 0),
	cname     varchar2(30)  not null,
	primary key (snum, cname),
	foreign key (snum) references student(snum) on delete cascade,
	foreign key (cname) references class(cname) on delete cascade
);

-- create EVALUTAION table --
create table evaluation (
	name varchar2(30),
	type varchar2(30),
	weight integer,
	deadline timestamp,
	room varchar2(30),
	cname varchar2(30),
	primary key (name, cname),
	foreign key (cname) references class(cname) on delete cascade
);

-- create GRADE table --
create table grade (
	snum integer,
	cname varchar2(30),
	mark integer,
	type varchar2(30),
	primary key (snum, type)
);
