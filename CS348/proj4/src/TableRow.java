
public class TableRow implements Comparable {
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

	@Override
	public int compareTo(Object t) {
		TableRow tR = (TableRow) t;
		// TODO Auto-generated method stub
		if (this.cname.compareTo(tR.cname) > 0)
			return 1;
		else if (this.cname.compareTo(tR.cname)< 0)
			return -1;
		else 
			return 0;
	}
}
