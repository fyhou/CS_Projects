-- CS 348: Project 3    --
-- Author: Joe Martella --
-- Date: 11/08/2011     --

set serveroutput on size 32000

create or replace procedure pro_department_report 
is
	cursor departments is
		select deptid, dname
		from department 
		order by dname;
	d departments%rowtype;
	profCount number(3);
begin
	for d in departments
	loop
		dbms_output.put_line('Department: ' || d.dname);

		select count(1)
		into profCount
		from faculty
		where faculty.deptid=d.deptid;
		dbms_output.put_line('Total faculty members: ' || profCount);

		dbms_output.put_line('-------------' || CHR(10));
	end loop;
end;
/

begin
	pro_department_report;
end;
/
