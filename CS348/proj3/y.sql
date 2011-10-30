-- CS 348: Project 3    --
-- Author: Joe Martella --
-- Date: 11/08/2011     --

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
		i:= 1;
		for p in profs
		loop
			if p.deptid=d.deptid then
				dbms_output.put_line(i || '. ' || p.fname);
				i:= i+1;
			end if;
		end loop;

		dbms_output.put_line(CHR(10));
	end loop;
end;
/

-- runs pro_department_report procedure
begin
	pro_department_report;
end;
/
