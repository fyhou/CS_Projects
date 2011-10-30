-- CS 348: Project 3             --
-- Author: Joe Martella          --
-- Date: 11/08/2011              -- 

-- Script fills tables with data --

insert into STUDENT values (0418,'S.Jack','Math','SO',17);
insert into STUDENT values (0671,'A.Smith','English','FR',20);
insert into STUDENT values (1234,'T.Banks','ME','SR',19);
insert into STUDENT values (3726,'M.Lee','Physics','SO',21);
insert into STUDENT values (4829,'J.Bale','Chemistry','JR',22);
insert into STUDENT values (5765,'L.Lim','CS','SR',19);
insert into STUDENT values (0019,'D.Sharon','History','FR',20);
insert into STUDENT values (7357,'G.Johnson','Math','JR',19);
insert into STUDENT values (8016,'E.Cho','History','JR',19);

insert into DEPARTMENT values (1,'Computer Sciences','West Lafayette');
insert into DEPARTMENT values (2,'Management','West Lafayette');
insert into DEPARTMENT values (3,'Medical Education','Purdue Calumet');
insert into DEPARTMENT values (4,'Education','Purdue North Central');
insert into DEPARTMENT values (5,'Pharmacal Sciences','Indianapolis');

insert into FACULTY values (101,'S.Layton',4);
insert into FACULTY values (102,'B.Jungles',1);
insert into FACULTY values (103,'N.Guzaldo',3);
insert into FACULTY values (104,'S.Boling',2);
insert into FACULTY values (105,'G.Mason',1);
insert into FACULTY values (106,'S.Zwink',2);
insert into FACULTY values (107,'Y.Walton',1);
insert into FACULTY values (108,'I.Teach',2);
insert into FACULTY values (109,'C.Jason',3);

insert into CLASS values ('ENG400',to_date('08:30','HH:MI'),'U003',107);
insert into CLASS values ('ENG320', to_date('09:30','HH:MI'),'R128',107);
insert into CLASS values ('COM100', to_date('11:30','HH:MI'),'L108',107);
insert into CLASS values ('ME308', to_date('10:30','HH:MI'),'R128',109);
insert into CLASS values ('CS448', to_date('09:30','HH:MI'),'U003',106);
insert into CLASS values ('HIS210', to_date('01:30','HH:MI'),'L108',104);
insert into CLASS values ('MATH275', to_date('02:30','HH:MI'),'L108',108);
insert into CLASS values ('STAT110', to_date('04:30','HH:MI'),'R128',108);
insert into CLASS values ('PHYS100', to_date('04:30','HH:MI'),'U003',105);

insert into ENROLLED values (0418,'ENG320');
insert into ENROLLED values (1234,'ENG400');
insert into ENROLLED values (8016,'ENG400');
insert into ENROLLED values (0418,'CS448');
insert into ENROLLED values (1234,'COM100');
insert into ENROLLED values (0671,'ENG400');
insert into ENROLLED values (1234,'HIS210');
insert into ENROLLED values (3726,'MATH275');
insert into ENROLLED values (5765,'PHYS100');
