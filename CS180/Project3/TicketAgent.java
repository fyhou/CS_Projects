import java.util.ArrayList;

/**
 * @description This class handles requests from a client
 * @author jwallrab
 *
 */
public class TicketAgent extends Thread implements Handler{
 
 private NetworkCommunicator netcom;
 private TicketDatabase td;
 private CustomerData c;

 /**
  * Constructor
  */
 public TicketAgent(NetworkCommunicator netC, TicketDatabase d) {
  netcom = netC;
  td = d;
 }

 /**
  * Entry point for handler thread
  */
 public void run() {
  
  /**
   * Receive relevant information about customer
   */
  try{
   receiveCustomer();
   System.out.println("Accepted new Customer " + c.getName());
  }catch(Exception e){
   System.out.println(e.getMessage());
   return; // Kills the thread
  }
  
  /**
   * Process Customer Requests
   */
  while(true){
   
   int request;
   try {
    request = netcom.receiveInt();
   } catch (Exception e) {
    try {
     netcom.closeConnection();
     System.out.println("Connection to Customer " + c.getName() + " closed.");
    } catch (Exception d) {
     System.out.println("Connection unable to close properly.");
    }
    return;
   }
   
   /**
    * Kill interaction due to customer request
    */
   if(request == 4){
    try {
     netcom.closeConnection();
     System.out.println("Connection to Customer " + c.getName() + " closed.");
    } catch (Exception e) {
     System.out.println("Connection unable to close properly.");
    }
    return;  //Customer requested exit
   }
   
   /**
    * Process User Requests
    */
   processRequest(request);
  }
 }
 
 /**
  * Processes the customer's request by returning the relevant information
  * to them or updating the Ticket Database accordingly.
  */
 public void processRequest(int req){
  
  switch(req){
  
  case 1:
   String date = "3:00PM April 11, 2010";
   String info = "Italian master Maurizio Pollini, a paragon of virtuosity, presents" +
   " an eagerly anticipated all-Chopin program to showcase his unprecedented artistry.\n" +
   "-Chicago Symphony Orchestra";
   try {
    netcom.sendObject(date + "\n" + info);
   } catch (Exception e) {
    System.out.println("Unable to send info about ticket to client");
   }
   break;
  case 2:
   ArrayList<Integer> availableTickets = td.getAvailableSeats();
   try{
    netcom.sendObject(availableTickets);
   }catch(Exception e){
    System.out.println("Unable to send available seats to client");
   }
   break;
  case 3:
   
   /**
    * Receive requested ticket to purchase
    */
   int ticketToPurchase = -1;
   try{
    ticketToPurchase = netcom.receiveInt();
   }catch(Exception e){
    System.out.println("Unable to receive client's purchase request");
    break;
   }
   
   /**
    * Send price to customer
    */
   try{
    Double price = td.getTicketBySeat(ticketToPurchase).getPrice();
    netcom.sendInt(1);
    netcom.sendObject(price);
   }catch(Exception e){
    System.out.println("Unable to send ticket price to Customer " + c.getName());
    try{
     netcom.sendInt(-1);
    }catch(Exception d){
     System.out.println("Unable to inform customer of failure");
    }
    break;
   }
   
   /**
    * Retrieve customer request to proceed or abort
    */
   int proceed = receiveProceed();
   if(proceed == -1)
    break;
   
   /**
    * Reserve Seat
    */
   try{
    /**
     * Reserve Seat Code HERE
     * This code should throw an exception if the
     * seat cannot be reserved
     */
    //TODO
       try{
       td.reserveTicket(ticketToPurchase, c);
       TimerThread timer = new TimerThread (td, td.getTicketBySeat(ticketToPurchase), c);
       timer.start(); // starts reserving ticket timer
       } catch (Exception e) {System.out.println ("Seat cannot be reserved.");}
    
    netcom.sendInt(1); //Executes if reservation was successful
   }catch(Exception e){
    System.out.println("Unable to reserve seat " + ticketToPurchase + " for Customer " + c.getName());
    try{
     netcom.sendInt(-1);
    }catch(Exception d){
     System.out.println("Unable to notify client of failure to reserve.");
     break;
    }
    break;
   }
   
   /**
    * Retrieve Credit Card Number
    */
   try{
    String cc = (String) netcom.receiveObject();
    c.setCC(cc);
   }catch(Exception e){
    System.out.println("Unable to receive Customer " + c.getName() + "'s Credit Card");
    break;
   }
   
   /**
    * Retrieve customer request to proceed or abort
    */
   proceed = receiveProceed();
   if(proceed == 0)
    break;
   else if(proceed == -1){
    /**
     * Release Seat Code HERE
     */
    //TODO
       try{
           td.releaseTicket(ticketToPurchase, c);
       } catch(Exception e) {}
   }
   
   /**
    * Purchase Ticket requested by customer
    */
   try {
    
    /**
     * 
     */
    //TODO
    
    td.purchaseTicket(ticketToPurchase, c); // purchases ticket
   } catch (Exception e) {
    System.out.println(e.getMessage());
    System.out.println("Unable to purchase seat " + ticketToPurchase + " for Customer " + c.getName());
    try{
     netcom.sendInt(-1);
    }catch(Exception d){
     System.out.println("Unable to notify client of failure to purchase.");
     break;
    }
    break;
   }
   
   /**
    * Send success as purchase went through without failure
    */
   try{
    netcom.sendInt(1);
   }catch(Exception e){
    System.out.println("Unable to notify client of purchase success.");
   }
   
   System.out.println("Printing Summary");
   td.salesSummary();
   break;
  }
 }
 
 /**
  * Retrieve customer request to proceed or abort
  */
 public int receiveProceed(){
  
  try{
   return netcom.receiveInt();
  }catch(Exception e){
   System.out.println("Unable to receive Customer " + c.getName() + " decision to purchase");
   return -1;
  }
 }
 
 /**
  * Receive the name and phone for a customer
  */
 public void receiveCustomer() throws Exception{
  
  String name, phone;
  
  try{
   name = (String) netcom.receiveObject();
   phone = (String) netcom.receiveObject();
   c = new CustomerData(name,phone);
   c.setNetCom(netcom);
  }catch(Exception e){
   System.out.println("Error receiving Customer Data");
   throw new Exception("Killing Thread");
  }
 }

}
