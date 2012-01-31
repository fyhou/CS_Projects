/**
 * @description A timer to control the reservations (lasts a minute).
 * @author jmartel
 * 
 * 
 *
 */
public class TimerThread extends Thread
{
    private TicketDatabase td; // the ticket database
    private Ticket t;          // the reserved ticket
    private CustomerData c;    // the customer
    
    public TimerThread(TicketDatabase td, Ticket t, CustomerData c)
    {
        this.td = td;
        this.t = t;
        this.c = c; 
    }
    
    // makes thread sleep for a minute, when it wakes up, it releases ticket
    public void run()
    {
        try{
        Thread.sleep(60000);
        td.releaseTicket(t.getSeatNumber(), c);
        } catch (Exception e) {System.out.println("Thread can't sleep.");}
    }
    
}