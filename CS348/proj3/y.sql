-- CS 348: Project 3                            --
-- Author: Joe Martella                         --
-- Date: 11/08/2011                             --

-- Script generates reports on the tables from  --
-- the data specified in data.sql               --

set serveroutput on size 32000

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
	if 1=2 then	
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

	-- gets students
	cursor students is
		select snum
		from student;
	s students%rowtype;

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
		select count(1)
		into studentCount
		from class c, enrolled e
		where 
			p.fid = c.fid and
			c.name = e.cname;

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
	pro_faculty_stats;
end;
/
