-- CS 348: Project 2    --
-- Author: Joe Martella --
-- Date: 10/13/2011     --

rem Query 1
select slevel as Student_Level, max(age) as Max_Age, min(age) as Min_Age, avg(age) as Average_Age
from student 
group by slevel;

rem Query 2
select sname as Student, major, slevel as Student_Level 
from student
where (
	(select count(*) 
	from enrolled 
	where enrolled.snum = student.snum) = 3
);

rem Query 3
select sname as Student, major, age
from (
	select sname, major, age, rank() over(order by age asc) r
	from student
	where major = 'Math'
		or snum in(
			select snum
			from enrolled e, class c, faculty f, department d
			where e.cname = c.name
			and c.fid = f.fid
			and f.deptid = d.deptid
			and d.dname = 'Computer Sciences'))
where r = 1;

rem Query 4
select fname as Professor, dname as Department_Name
from faculty f, department d
where 
	(select count (class.room)
	from class
	where f.fid = class.fid) = 
	(select count (distinct class.room)
	from class)
	and f.deptid = d.deptid;
	
rem Query 5
select distinct fname as Professor, count(enrolled.snum) over () as Total_Students
from faculty, enrolled, class
where 
	(select count (enrolled.snum)
	from class, enrolled
	where 
		class.name = enrolled.cname
		and class.fid = faculty.fid) > 2 and
	(select count (enrolled.snum)
	from class, enrolled
		where class.name = enrolled.cname
		and class.fid = faculty.fid) < 6 and
	class.name = enrolled.cname and class.fid = faculty.fid;
		
rem Query 6
select sname as Name
from student s
where s.snum in 
	(select e1.snum from enrolled e1, enrolled e2, class c1, class c2
	where e1.snum = e2.snum and e1.cname <> e2.cname
	and e1.cname = c1.name and e2.cname = c2.name 
	and c1.meets_at = c2.meets_at);
	
rem Query 7
select d.dname as Department_Name, count(c.fid) as Classes
from department d left outer join faculty f on (d.deptid = f.deptid) left outer join class c on f.fid = c.fid
where d.dname <> 'Management'
group by d.dname;

rem Query 8
select dname as Department_Name
from department
where deptid not in
	(select deptid
	from faculty, class 
	where exists
		(select * 
		from class
		where faculty.fid = class.fid));

rem Query 9
select class.name as Class, class.room as Room, faculty.fname as Professor
from class, faculty
where (class.room = 'R128' or
	class.name in 
		(select enrolled.cname 
		from enrolled
		group by enrolled.cname
		having count(snum) > 2)) and
 	class.fid = faculty.fid;

rem Query 10
select distinct faculty.fname as Professor, count(enrolled.cname) over () as Number_Of_Students
from faculty, class, enrolled
where faculty.fid = class.fid and enrolled.cname = class.name and class.name = (
	select cname
	from ( 
		select cname
		from enrolled
		group by cname
		order by count(cname) desc)
  	where rownum = 1);



		
