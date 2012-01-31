
/**
 * @description An interface the TicketAgent class
 * must implement to provide full interaction with
 * the server's Ticket Database
 * @author jwallrab
 * 
 * DO NOT MODIFY THIS CLASS
 *
 */
public interface Handler {

	/**
	 * This method should take the option number and
	 * process the customer's request accordingly
	 */
	public void processRequest(int request);
	
	/**
	 * This method should receive relevant information
	 * about the customer (name,phone) and continually
	 * call processRequest until the user decides to
	 * disconnect from the ticket server
	 */
	public void run();
	
}
