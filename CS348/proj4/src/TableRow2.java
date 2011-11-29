
public class TableRow2 implements Comparable {
	public String cname;
	public String semester;
	public String year;
	public String sname;
	public String currGrade;
	
	public Object[] toArray() {
		Object[] o = new Object[5];
		
		o[0] = cname;
		o[1] = semester;
		o[2] = year;
		o[3] = sname;
		o[4] = currGrade;
		
		return o;
	}

	@Override
	public int compareTo(Object t) {
		TableRow2 tR = (TableRow2) t;
		// TODO Auto-generated method stub
		if (this.cname.compareTo(tR.cname) > 0)
			return 1;
		else if (this.cname.compareTo(tR.cname)< 0)
			return -1;
		else 
			return 0;
	}
}

