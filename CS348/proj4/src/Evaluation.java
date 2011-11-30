
public class Evaluation implements Comparable<Evaluation>{
	String name;
	String type;
	String weight;
	String deadline;
	String room;
	String cname;
	
	@Override
	public int compareTo(Evaluation e) {
		// TODO Auto-generated method stub
		if (this.cname.compareTo(e.cname) > 0)
			return 1;
		else if (this.cname.compareTo(e.cname)< 0)
			return -1;
		else 
			return 0;
	}
}
