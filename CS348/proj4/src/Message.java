
public class Message implements Comparable<Message> {
	public String cname;
	public String message;
	
	@Override
	public int compareTo(Message m) {
		if (this.cname.compareTo(m.cname) > 0)
			return 1;
		else if (this.cname.compareTo(m.cname)< 0)
			return -1;
		else 
			return 0;
	}
}
