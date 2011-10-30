-- CS 348: Project 3    --
-- Author: Joe Martella --
-- Date: 11/08/2011     --

set serveroutput on size 32000

create or replace procedure pro_department_report 
is
	cursor departments is
		select deptid, dname from department;
	d departments%rowtype;
begin
	for d in departments
	loop
		dbms_output.put_line(d.dname);
	end loop;
end;
/

begin
	pro_department_report;
end;
/
