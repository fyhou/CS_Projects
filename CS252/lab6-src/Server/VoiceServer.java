import java.util.*; 
import java.io.*; 
import java.net.*;

public class VoiceServer implements Runnable
{
    private int BUFFER_SIZE = 768;
    
    private int _port = 0;
    ArrayList<VoiceServerConnection> _connections = null;
    
    VoiceServer(int port)
    {
        _port = port;
        _connections = new ArrayList<VoiceServerConnection>();
    }

    public void run()
    {
        System.out.println("Voice Server started...");
        
        try
        {
            // create a socket for handling incoming requests
            DatagramSocket serverSocket = new DatagramSocket(_port);
            byte[] buffer = new byte[BUFFER_SIZE];
            
            while(true)
            {
                // receive the incoming packet
                DatagramPacket receivePacket = new DatagramPacket(buffer, buffer.length);
                serverSocket.receive(receivePacket);
                
                // extract the byte stream data
                buffer = receivePacket.getData();
                
                // extract the IP address and port number
                InetAddress ipAddress = receivePacket.getAddress();
                int port = receivePacket.getPort();
                
                // if this is a new connection, store it in our list
                VoiceServerConnection target = null;
                for (VoiceServerConnection c : _connections)
                {
                    if ((c.getIPAddress().toString().equals(ipAddress)) &&
                        (c.getPort() == port))
                    {
                        target = c;
                        break;
                    }
                }
                
                if (target == null)
                {
                    VoiceServerConnection vsc = new VoiceServerConnection(ipAddress, port);
                    _connections.add(vsc);
                }
                
                // send the packet data
                for (VoiceServerConnection c : _connections)
                {
                    try
                    {
                        if (!(c.getIPAddress().toString().equals(ipAddress))) // we don't need to hear our own audio
                        {
                            DatagramPacket sendPacket = new DatagramPacket(buffer, buffer.length, c.getIPAddress(), c.getPort());
                            serverSocket.send(sendPacket);
                        }
                    }
                    catch (IOException ex)
                    {
                        // TODO: handle this exception
                    }
                }
            }
        }
        catch (Exception ex)
        {
            // TODO: handle this exception
        }
    }
}

