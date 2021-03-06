-- CS 348: Project 3                            --
-- Author: Joe Martella                         --
-- Date: 11/08/2011                             --

-- Script generates reports on the tables from  --
-- the data specified in data.sql               --

set serveroutput on size 32000
set linesize 32000
	
/**
	procedure generates a report that lists, for each department, the faculty members in 
	that department.  
**/
create or replace procedure pro_department_report 
is
	-- gets departments
	cursor departments is
		select deptid, dname
		from department 
		order by dname;
	d departments%rowtype;

	-- gets faculty
	cursor profs is
		select fname, deptid
		from faculty
		order by fname;
	p profs%rowtype;

	-- variable for faculty count
	profCount number(3);

	-- iterator variable
	i number(1);
begin
	for d in departments
	loop
		dbms_output.put_line('Department: ' || d.dname);

		-- gets faculty count
		select count(1)
		into profCount
		from faculty
		where faculty.deptid=d.deptid;
		dbms_output.put_line('Total faculty members: ' || profCount);

		dbms_output.put_line('-------------');

		-- iterates over faculty, prints if they are in current department
		i := 1;
		for p in profs
		loop
			if p.deptid=d.deptid then
				dbms_output.put_line(i || '. ' || p.fname);
				i := i+1;
			end if;
		end loop;

		dbms_output.put_line(CHR(10));
	end loop;
end;
/

-- runs pro_department_report procedure
begin
	if 1=1 then	
		pro_department_report;
	end if;
end;
/

/**
	procedure generates a report that contains statistics about faculty.
**/
create or replace procedure pro_faculty_stats
is
	-- gets faculty
	cursor profs is
		select fname, fid
		from faculty
		order by fname;
	p profs%rowtype;

	studentTotal number(2); -- total number of students
	facultyTotal number(2); -- total number of faculty
	classTotal   number(2); -- total number of classes

	studentToFaculty number(2); -- student to faculty ratio 
	averageClasses number(2,1); -- average classes per faculty

	studentCount number(2); -- number of students that faculty teaches
	spaces long;            -- spaces between faculty name and number of students
begin
	-- gets count of students
	select count(1)
	into studentTotal
	from student;
	
	-- gets count of faculty
	select count(1)
	into facultyTotal
	from faculty;

	-- gets count of classes
	select count(1)
	into classTotal
	from class;

	-- calculates student to faculty ratio
	studentToFaculty := studentTotal/facultyTotal;
	dbms_output.put_line('Student to faculty ratio: ' || studentToFaculty || ':1');

	-- calcualtes average number of classes per faculty
	averageClasses := classTotal/facultyTotal;
	dbms_output.put_line('Average number of classes per faculty:' || to_char(averageClasses, '99.9') || CHR(10));

	dbms_output.put_line('Faculty Name          # Students');
	dbms_output.put_line('------------          ----------');

	for p in profs
	loop
		select count(distinct s.snum)
		into studentCount
		from student s, class c, enrolled e
		where 
			p.fid = c.fid and
			c.name = e.cname and
			s.snum = e.snum;

		if studentCount = 0 then
			studentCount := 0;
		else
			spaces:= '';
			for i in 1..(22-length(p.fname)) loop
				spaces:= spaces || ' ';
			end loop;

			dbms_output.put_line(p.fname || spaces || studentCount);
		end if;

	end loop;
end;
/

-- runs pro_faculty_stats procedure
begin
	if 1=1 then
		pro_faculty_stats;
	end if;
end;
/

/**
	procedure generates a report about the number of classes a student is in.
**/
create or replace procedure pro_student_stats
is
	-- gets students
	cursor students is
		select sname, snum
		from student
		order by sname;
	s students%rowtype;

	numberClasses number(2); -- number of classes student is in
	spaces long;             -- determines what column to print in
begin
	dbms_output.put_line('~             # classes          ~');
	dbms_output.put_line('Student     0     1     2     >=3');
	dbms_output.put_line('-------    ---   ---   ---   -----');

	for s in students
	loop
		select count(1)
		into numberClasses
		from enrolled
		where enrolled.snum=s.snum;

		spaces := '';
		if numberClasses = 0 then
			for i in 1..(12-length(s.sname)) loop
				spaces := spaces || ' ';
			end loop;
		elsif numberClasses = 1 then
			for i in 1..(18-length(s.sname)) loop
				spaces := spaces || ' ';
			end loop;
		elsif numberClasses = 2 then
			for i in 1..(24-length(s.sname)) loop
				spaces := spaces || ' ';
			end loop;
		else
			for i in 1..(31-length(s.sname)) loop
				spaces := spaces || ' ';
			end loop;
		end if;

		dbms_output.put_line(s.sname || spaces || 'X');
	end loop;
end;
/

-- runs pro_student_stats procedure
begin
	if 1=1 then
		pro_student_stats;
	end if;
end;
/

/**
	procedure generates a histrogram for the ages of the students.
**/
create or replace procedure pro_histogram
is
	minAge number(2); -- min age
	maxAge number(2); -- max age
	medAge number(10,2); -- median age
	
	medAgeCopy number(10,2);
	printMed number(1);

	people number(2); -- students with age of interest
	Xs long;          -- histogram bar
	spaces long;      -- formatting
begin
	-- gets min age
	select min(s.age)
	into minAge
	from student s;

	-- gets max age
	select max(s.age)
	into maxAge
	from student s;

	-- gets median age
	select median(s.age)
	into medAge
	from student s;
	
	medAgeCopy := medAge;
	while medAgeCopy >= 1
	loop
		medAgeCopy := medAgeCopy - 1;
	end loop;

	if medAgeCopy = 0 then
		printMed := 1;
	else
		printMed := 0;
	end if;

	dbms_output.put_line('age');
	
	for i in minAge..maxAge 
	loop
		-- get count of people with age of interest
		select count(1)
		into people
		from student
		where student.age=i;

		-- generate histogram bar
		Xs := '';
		for j in 1..people 
		loop
			Xs := Xs || 'x';
		end loop;

		-- pure formatting
		if people < 10 then
			spaces := '  ';
		else
			spaces := ' ';
		end if;

		-- print output
		if medAge = i and printMed = 1 then
			dbms_output.put_line(i || ' | ' || people || spaces || Xs || ' <-- median');
		else
			dbms_output.put_line(i || ' | ' || people || spaces || Xs);
		end if;
	end loop;
end;
/

-- runs pro_histogram
begin
	if 1=1 then
		pro_histogram;
	end if;
end;
/

/**
	procedures will insert a new class into the class table
**/
create or replace procedure pro_insert_class (fname_in in varchar2, cname_in in varchar2, meets_at_in in date, room_in in varchar2)
is
	facID number(4); -- fid of faculty teaching new class
begin
	select fid
	into facID
	from faculty
	where faculty.fname=fname_in;

	insert into CLASS values (cname_in,meets_at_in,room_in,facID);
end;
/

-- runs pro_insert_class
select * from class;
begin
	if 1=1 then
		pro_insert_class('S.Boling', 'CS100', to_date('05:30','HH:MI'), 'A001');
	end if;
end;
/
select * from class;
