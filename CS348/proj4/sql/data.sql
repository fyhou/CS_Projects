-- CS 348: Project 4              --
-- Author: Joe Martella           --
-- Date: 12/01/2011               -- 

-- Script that fills the tables   --

insert into student values (1,'S1','CS','JR', 'pw1');
insert into student values (2,'S2','PSY','SO', 'pw2');
insert into student values (3,'S3','BS','FR', 'pw3');

insert into faculty values (101,'F1', 'pw4');
insert into faculty values (102,'F2', 'pw5');
insert into faculty values (103,'F3', 'pw6');

insert into class values ('CS100', 'F', 2012, to_char('09:30', 'HH:MI'), "X1", 101);
insert into class values ('CS200', 'F', 2012, to_char('10:30', 'HH:MI'), "X1", 101);

insert into evaluation values ('Homework 1', 'HW', 20, to_char('12/12/12', 'MM/DD/YY'), 'R1', 'CS100'); 
insert into evaluation values ('Homework 2', 'HW', 20, to_char('12/19/12', 'MM/DD/YY'), 'R1', 'CS100'); 

insert into grade values (1, 'CS100', 90, 'Homework 1');
insert into grade values (1, 'CS100', 100, 'Homework 2');