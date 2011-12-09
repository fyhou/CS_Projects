import java.util.*; 
import java.io.*; 
import java.net.*;

public class DirectoryServer implements Runnable
{
    private int _port = 0;
    ArrayList<User> _directory = null;
    ArrayList<DirectoryServerConnection> _connections = null;
    
    VoiceServer _vs1;
    VoiceServer _vs2;
    
    boolean _viki = false;
    
    DirectoryServer(int port, VoiceServer vs1, VoiceServer vs2)
    {
        _port = port;
        _directory = new ArrayList<User>();
        _connections = new ArrayList<DirectoryServerConnection>();
        
        _viki = false;
        
        _vs1 = vs1;
        _vs2 = vs2;
    }

    public void run()
    {
        System.out.println("Directory Server started...");
        
        try
        {
            // create a socket for handling incoming requests
            ServerSocket server = new ServerSocket(_port);

            while (true)
            {
                System.out.println("Listening for conections on port " + _port + "...");
                
                // wait for an incoming connection
                Socket clientSocket = server.accept();
                
                System.out.println("Connection received.");                
                System.out.println("Launching new thread for connection...");
                
                // create a new connection for this socket
                DirectoryServerConnection cn = new DirectoryServerConnection(this, clientSocket);                
                _connections.add(cn);
                                
                // launch a new thread for this connection
                Thread th = new Thread(cn);
                th.start();
            }
        }
        catch (Exception ex)
        {
            // TODO: handle this exception
        }
    }
    
    public void sendUpdatedDirectory()
    {
        for (DirectoryServerConnection c : _connections)
        {
            c.getDirectory(); 
        }
    }
}

