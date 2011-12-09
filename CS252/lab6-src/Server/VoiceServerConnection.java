import java.util.*; 
import java.io.*; 
import java.net.*;

public class VoiceServerConnection
{
    private InetAddress _ipAddress = null; 
    private int _port = 0;
    
    VoiceServerConnection(InetAddress ipAddress, int port)
    {
        _ipAddress = ipAddress;
        _port = port;
    } 

    public InetAddress getIPAddress()
    {
        return _ipAddress;
    }
    
    public int getPort()
    {
        return _port;
    }
}

