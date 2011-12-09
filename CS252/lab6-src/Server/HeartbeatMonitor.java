import java.util.*; 
import java.io.*; 
import java.net.*;

public class HeartbeatMonitor implements Runnable
{
    private DirectoryServer _ds = null;
    private int _sleepTime = 5000; // how often to check in ms
    private int _checkTime = 15000; // whatever is considered old in ms

    HeartbeatMonitor (DirectoryServer ds)
    {
        _ds = ds;
    }

    public void run()
    {
        System.out.println("HeartbeatMonitor is in action...");

        while (true)
        {
            System.out.println("Checking for stale threads...");
            Long currTime = Calendar.getInstance().getTimeInMillis();
            Long timeDiff = new Long(0);

            DirectoryServerConnection target = null;
            for (DirectoryServerConnection c : _ds._connections)
            {
				System.out.println("");
                if (c._user.getStatus().equals("Busy")) continue;
            
                timeDiff = currTime - c._lastKeepAliveTime;

                if (timeDiff > _checkTime)
                {
                    // kill connection
                    try
                    {
                        if (c._user != null)
                        {
                            _ds._directory.remove(c._user);  
							_ds.sendUpdatedDirectory();                          
                        }
                        
                        c._clientSocket.close();                        
                        target = c;
                    }
                    catch (IOException ex)
                    {
                        // TODO: handle this exception            
                    }
                    
                    System.out.println(c._user.getUsername() + " has been removed from the directory.");
                }
                else
                {
                    // connection is active
                    System.out.println(c._user.getUsername() + " can remain in the directory.");
                }
            }
            
            if (target != null)
            {
                _ds._connections.remove(target);                            
            }

            try
            {
                Thread.sleep(_sleepTime);    
            }
            catch (InterruptedException e)
            {
                // TODO: handle this exception
            }
        }
    }
}

