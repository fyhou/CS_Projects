-- CS 348: Project 4              --
-- Author: Joe Martella           --
-- Date: 12/01/2011               -- 

-- Script that fills the tables   --

insert into student values (1,'S1','CS','JR', 'S1');
insert into student values (2,'S2','PSY','SO', 'S2');

insert into faculty values (101,'F1', 'F1');
insert into faculty values (102,'F2', 'F2');

insert into class values ('CS100', 'F', 2012, to_date('09:30', 'HH:MI'), 'X1', 101);
insert into class values ('CS200', 'F', 2012, to_date('10:30', 'HH:MI'), 'X1', 101);

insert into evaluation values ('Homework 1', 'HW', 10, to_date('12/12/12', 'MM/DD/YY'), 'R1', 'CS100'); 
insert into evaluation values ('Homework 2', 'HW', 10, to_date('12/19/12', 'MM/DD/YY'), 'R1', 'CS100'); 
insert into evaluation values ('Midterm', 'M', 30, to_date('01/15/13', 'MM/DD/YY'), 'X1', 'CS100');
insert into evaluation values ('Final', 'F', 50, to_date('03/15/13', 'MM/DD/YY'), 'X1', 'CS100');

insert into evaluation values ('Homework 1', 'HW', 10, to_date('12/12/12', 'MM/DD/YY'), 'R1', 'CS200'); 
insert into evaluation values ('Homework 2', 'HW', 10, to_date('12/19/12', 'MM/DD/YY'), 'R1', 'CS200'); 
insert into evaluation values ('Midterm', 'M', 30, to_date('01/15/13', 'MM/DD/YY'), 'X1', 'CS200');
insert into evaluation values ('Final', 'F', 50, to_date('03/15/13', 'MM/DD/YY'), 'X1', 'CS200');

insert into enrolled values ('1', 'CS100');
insert into enrolled values ('1', 'CS200');

insert into grade values (1, 'CS100', 90, 'Homework 1');
insert into grade values (1, 'CS100', 100, 'Homework 2');
insert into grade values (1, 'CS100', 85, 'Midterm');
insert into grade values (1, 'CS100', 93, 'Final');

insert into grade values (1, 'CS200', 76, 'Homework 1');
insert into grade values (1, 'CS200', 89, 'Homework 2');
insert into grade values (1, 'CS200', 95, 'Midterm');
insert into grade values (1, 'CS200', 92, 'Final');

insert into message values ('You all get As!', 'CS100');
insert into message values ('Free pizza in class today!', 'CS100');
insert into message values ('This class has no people in it.', 'CS200');
