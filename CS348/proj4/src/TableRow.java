
public class TableRow {
	public String cname;
	public String meetsAt;
	public String room;
	public String nStudents;
	public String nEvals;
	
	public Object[] toArray() {
		Object[] o = new Object[5];
		
		o[0] = cname;
		o[1] = meetsAt;
		o[2] = room;
		o[3] = nStudents;
		o[4] = nEvals;
		
		return o;
	}
}
