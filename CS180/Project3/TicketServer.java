import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @description Implements a ticket server providing clients
 * the ability to purchase tickets for an event.
 * 
 * You should ONLY HAVE TO MODIFY THE CODE FOLLOWING THE TODO
 * 
 * @author jwallrab
 *
 */
public class TicketServer {
 
 ServerSocket svrSocket = null;
 private static int port;
 private TicketDatabase td;

 /**
  * Static Entry Point
  * @param args
  */
 public static void main(String[] args) {
  
  TicketServer ts = new TicketServer();
  
  try{
   if(args[0] != null)
    port = Integer.parseInt(args[0]);
  }catch(Exception e){
   System.out.println("Error binding to port " + port + ".");
   port = 51500;
   System.out.println("Using " + port);
  }

  ts.run();
 }
 
 /**
  * Dynamic Entry Point
  */
 public void run(){
  
  td = new TicketDatabase();
  
  //Init Phase
  try {
   svrSocket = new ServerSocket(port);
  } catch (IOException err) {
   System.err.println("can't bind");
   System.exit(-1);
  }
  
  displayServerInfo();
  
  //Running Phase
  while (true) {
   Socket client;
   try {
    client = svrSocket.accept();
    
    NetworkCommunicator netcom = null;
    try {
     netcom = new NetworkCommunicator(client,port);
    } catch (Exception e) {
     System.out.println("Error accepting new client");
     continue;
    }
    
    /**
     * TODO - Process requests with a TicketAgent
     * The ONLY modifications to this class you should have to make
     * are to the next two lines of code!
     */
    TicketAgent t = new TicketAgent(netcom,td);
    t.start();
    
    
   } catch (IOException err) {
       System.out.println("Main Server Error - Handled by TicketAgent");
   } //ignore errors, they are now Ticket Agent's responsibility
  }
 }
 
 /**
  * Displays contact information for the server
  */
 public void displayServerInfo(){
  
  String ip = "IP UNAVAILABLE";
  
  try{
   ip = InetAddress.getLocalHost().getHostAddress();
  }catch(Exception e){}
  
  System.out.println("***********************");
  System.out.println("*TICKET SERVER RUNNING*");
  System.out.println("IP: " + ip);
  System.out.println("PORT: " + port);
  System.out.println("***********************");
 }
}
