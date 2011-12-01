
public class Grade implements Comparable<Grade> {
	String mark;
	String name;
	String weight;
	String cname;
	
	@Override
	public int compareTo(Grade g) {
		if (this.cname.compareTo(g.cname) > 0)
			return 1;
		else if (this.cname.compareTo(g.cname)< 0)
			return -1;
		else 
			return 0;
	}
}
