
public class ClassTable implements Comparable<ClassTable>{
	String cname;
	String meetsAt;
	String room;
	String semester;
	String year;
	
	@Override
	public int compareTo(ClassTable c) {
		// TODO Auto-generated method stub
		int tYear = Integer.parseInt(this.year);
		int cYear = Integer.parseInt(c.year);
		
		if (tYear > cYear) {
			return 1;
		}
		else if (tYear < cYear) {
			return -1;
		}
		else {			
			if (this.semester.compareTo(c.semester) > 0)
				return 1;
			else if (this.semester.compareTo(c.semester)< 0)
				return -1;
			else {
				return 0;
			}
		}
	}
}
