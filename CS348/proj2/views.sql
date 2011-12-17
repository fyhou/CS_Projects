-- CS 348: Project 2    --
-- Author: Joe Martella --
-- Date: 10/13/2011     --
set pagesize 1000;

create view VIEWA(Class, Number_of_Students) as
select e.cname, count(e.snum)
from enrolled e left outer join class c on e.cname = c.name
group by e.cname
order by e.cname asc;

create view VIEWB(Name, Room, Time) as
select fname, class.room, to_char(class.meets_at, 'HH:MI')
from faculty, class
where 
	faculty.fid = class.fid
union 
select sname, class.room, to_char(class.meets_at, 'HH:MI')
from student, enrolled, class
where 
	enrolled.snum = student.snum and
	enrolled.cname = class.name
order by 1;

select * from VIEWA;
select * from VIEWB;


