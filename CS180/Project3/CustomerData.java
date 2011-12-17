/**
 * @description A customer class holding their name
 * and phone number.
 * @author jwallrab
 *
 */
public class CustomerData {

	private String name;
	private String phoneNumber;
	private String creditCard;
	private NetworkCommunicator netcom;
	
	public CustomerData(){}
	
	public CustomerData(String name, String phoneNumber){
		this.name = name;
		this.phoneNumber = phoneNumber;
	}
	
	/*********** Getters and Setters ***********/
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public String getPhoneNumber() {
		return phoneNumber;
	}
	
	public void setPhoneNumber(String phoneNumber) {
		this.phoneNumber = phoneNumber;
	}
	
	public String getCC(){
		return creditCard;
	}
	
	public void setCC(String c){
		creditCard = "";
		creditCard = c;
	}
	
	public NetworkCommunicator getNetCom(){
		return netcom;
	}
	
	public void setNetCom(NetworkCommunicator n){
		netcom = n;
	}
	
	public void initializeNetCom(String ip, int port) throws Exception{
		netcom = new NetworkCommunicator(ip,port);
		netcom.sendConnect(ip);
	}
	
	public void sendRequest(int req) throws Exception{
		netcom.sendInt(req);
	}
	
	public CustomerData copy(){
		CustomerData c = new CustomerData();
		c.setName(getName());
		c.setPhoneNumber(getPhoneNumber());
		return c;
	}
	
	public boolean equals(Object o){
		
		if(o == null)
			return false;
		if(getClass().equals(o.getClass())){
			CustomerData c = (CustomerData) o;
			
			if(c.getName().equals(getName()) &&
				c.getPhoneNumber().equals(getPhoneNumber()))
					return true;
		}
		return false;
	}
}
