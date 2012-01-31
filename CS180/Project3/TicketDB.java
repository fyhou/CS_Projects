/**
 * @description This interface defines the crucial methods a Ticket
 * Database should implement.
 * @author jwallrab
 *
 * DO NOT MODIFY THIS CLASS
 *
 */
public interface TicketDB {
	
	/**
	 * This method must allow a user to purchase an available seat,
	 * and NOT allow multiple users to purchase the same seat simultaneously.
	 * You will have to ensure that only a single thread can access this method
	 * at a time to avoid the aforementioned scenario. It is likely that your
	 * purchaseTicket method will throw exceptions (invalid seat number, unavailable
	 * seat) so account for this. Again, the most important part of this method
	 * is that it WILL NOT ALLOW MULTIPLE CUSTOMERS TO PURCHASE THE SAME SEAT.
	 * @param seatNum
	 * @param c
	 */
	public void purchaseTicket(int seatNum, CustomerData c) throws Exception;
	
	/**
	 * This method must allow a customer to release a ticket if and only if
	 * they were the one who reserved it. The ticket should then become available
	 * for any customer to purchase. This method should be called after a set
	 * timeout period if the customer does not complete the transaction.
	 * @param seatNum
	 * @param c
	 * @throws Exception
	 */
	public void releaseTicket(int seatNum, CustomerData c) throws Exception;
	
	/**
	 * This method must allow a customer to reserve a ticket in such a way that
	 * it is unavailable for purchase by another customer. However, the customer
	 * who reserved the ticket can purchase the ticket within the timeout period.
	 * The reserved ticket should be released after a timeout, however this method
	 * does not necessarily have to handle that - it can be done elsewhere.
	 * @param seatNum
	 * @param c
	 * @throws Exception
	 */
	public void reserveTicket(int seatNum, CustomerData c) throws Exception;
	
	/**
	 * This should print a summary of all seats sold, and to whom.
	 */
	public void salesSummary();
	
}