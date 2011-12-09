import java.util.*; 
import java.io.*; 
import java.net.*;

public class Server
{
    public static void main(String[] args)
    {
        System.out.println("Starting server...");
        
        // create a new instance of the voice server for inbound data
        VoiceServer vs1 = new VoiceServer(7771);
        
        Thread t1 = new Thread(vs1);        
        t1.start();
        
        // create a new instance of the voice server for outbound data
        VoiceServer vs2 = new VoiceServer(7772);
        
        Thread t2 = new Thread(vs2);        
        t2.start();
        
        
        
        // create a new instance of the directory server
        DirectoryServer ds = new DirectoryServer(7770, vs1, vs2); 
		
        Thread t3 = new Thread(ds);        
        t3.start();

        // create a new instance of the heartbeat monitor
        if ((args.length > 0 && args[0].equals("--disable-keep-alive") == false) ||
            (args.length == 0))
        {
            HeartbeatMonitor hm = new HeartbeatMonitor(ds);
            
            Thread t4 = new Thread(hm);
            t4.start();
        }
    }
}

