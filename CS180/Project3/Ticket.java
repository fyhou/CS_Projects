/**
 * @description A ticket class representing its owner,
 * seat number and price.
 * @author jwallrab
 * 
 * DO NOT MODIFY THIS CLASS
 *
 */
public class Ticket{
	
	private CustomerData owner;
	private int seatNumber;
	private double price;
	
	public Ticket(int seatNum, double p){
		seatNumber = seatNum;
		price = p;
	}
	
	/*********** Getters and Setters ***********/
	
	public CustomerData getOwner() throws NullPointerException{
		
		if(owner == null)
			throw new NullPointerException("Owner is null");
		
		return owner.copy();
	}
	
	public void setOwner(CustomerData owner) {
		this.owner = owner.copy();
	}
	
	public int getSeatNumber() {
		return seatNumber;
	}
	
	public void setSeatNumber(int seatNumber) {
		this.seatNumber = seatNumber;
	}
	
	public double getPrice() {
		return price;
	}
	
	public void setPrice(double price) {
		this.price = price;
	}
	
	public Ticket copy(){
		Ticket t = new Ticket(seatNumber, price);
		t.setOwner(owner.copy());
		return t;
	}
	
	public boolean equals(Object o){
		if(o == null)
			return false;
		
		if(o.getClass().equals(getClass())){
			Ticket t = (Ticket) o;
			
			if(t.getOwner().equals(owner) &&
					t.seatNumber == seatNumber &&
					t.price == price)
				return true;
		}
		
		return false;
	}
}
