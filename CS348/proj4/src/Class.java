
public class Class implements Comparable<Class>{
	String cname;
	String meetsAt;
	String room;
	String semester;
	String year;
	
	@Override
	public int compareTo(Class c) {
		// TODO Auto-generated method stub
		if (this.semester.compareTo(c.semester) > 0)
			return 1;
		else if (this.semester.compareTo(c.semester)< 0)
			return -1;
		else 
			return 0;
	}
}
