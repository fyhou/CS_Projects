import java.util.*; 
import java.io.*; 
import java.net.*;

public class DirectoryServerConnection implements Runnable
{
    private DirectoryServer _host = null; 
    Socket _clientSocket = null;
    Long _lastKeepAliveTime = new Long(0);
    
    User _user = null;
    
    DirectoryServerConnection(DirectoryServer host, Socket clientSocket)
    {
        _host = host;
        _clientSocket = clientSocket; 
        _lastKeepAliveTime = Calendar.getInstance().getTimeInMillis();
    }
    
    public String getIPAddress()
    {
        return _clientSocket.getRemoteSocketAddress().toString().substring(1);
    }

    public void run()
    {
        try
        {
            System.out.println("Thread for connection started.");
            
            // load in the stream data
            InputStream is = _clientSocket.getInputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(is));

            String line;
            
            // read each line
            while ((line = br.readLine()) != null)
            {
                // AddUser request
                if (line.startsWith("<AddUser>"))
                {
                    String username = br.readLine();
                    username = username.substring(10, username.length() - 11);

                    /*System.out.println("\nAddUser Request");
                    System.out.println("---------------");
                    System.out.println("New user:   " + username);
                    System.out.println("IP Address: " + _clientSocket.getRemoteSocketAddress().toString().substring(1));*/
                    
                    addUser(username);
                }
                // GetDirectory request
                else if (line.startsWith("<GetDirectory>"))
                {
                    //System.out.println("\nGetDirectory Request");
                    
                    getDirectory();
                }    
                // SendCall request
                else if (line.startsWith("<SendCall>"))
                {
                    String sendIP = br.readLine();
                    sendIP = sendIP.substring(11, sendIP.length() - 12);
                    /*System.out.println("\nSendCall Request");
                    System.out.println("----------------");
                    System.out.println("IP Address: " + sendIP);*/

                    sendCallRequest(sendIP);
                }
                // AcceptCall request
                else if (line.startsWith("<AcceptCall>"))
                {
                    String senderIP = br.readLine();
                    senderIP = senderIP.substring(11, senderIP.length() - 12);
                    /*System.out.println("\nAcceptCall Request");
                    System.out.println("------------------");
                    System.out.println("IP Address: " + senderIP);*/

                    acceptCallRequest(senderIP);
                }
                // Hangup request
                else if (line.startsWith("<Hangup>"))
                {
                    String senderIP = br.readLine();
                    senderIP = senderIP.substring(11, senderIP.length() - 12);
                    /*System.out.println("\nHangup Request");
                    System.out.println("--------------");
                    System.out.println("IP Address: " + hangupIP);*/

                    hangupRequest(senderIP);
                }
                // KeepAlive request
                else if (line.startsWith("<KeepAlive>")) 
                {
                    _lastKeepAliveTime = Calendar.getInstance().getTimeInMillis();
                    
                    /*System.out.println("\nKeepAlive Request");
                    System.out.println("-----------------");
                    System.out.println("Timestamp for " + _clientSocket.getRemoteSocketAddress().toString().substring(1) + ": " + _lastKeepAliveTime);*/
                }    
            }
        }
        catch (IOException ex)
        {
            // TODO: handle this exception
        }
    }
    
    public void addUser(String username)
    {
        // TODO: check if IP already exists
        User u = new User(username, _clientSocket.getRemoteSocketAddress().toString().substring(1));
        _host._directory.add(u);
        
        _user = u;

        _host.sendUpdatedDirectory();
    }
    
    public void getDirectory()
    {
        try
        {
            PrintWriter out = new PrintWriter(_clientSocket.getOutputStream(), true);
                        
            out.println("<Directory>");
            for (User u : _host._directory)
            {
                out.println("<User>");
                out.println("<Username>" + u.getUsername() + "</Username>");
                out.println("<IPAddress>" + u.getIPAddress() + "</IPAddress>");
                out.println("<Status>" + u.getStatus() + "</Status>");
                out.println("</User>");
            }
            out.println("</Directory>");
        }
        catch (IOException ex)
        {
            // TODO: handle this exception
        }
    }

    public void sendCallRequest(String connectionIP)
    {
        Socket _connectionSocket = null;

        try 
        {
            // get socket to write to
            for (DirectoryServerConnection _con: _host._connections)
            {
                if (_con._user.getIPAddress().equals(connectionIP))
                {
                    _connectionSocket = _con._clientSocket;
                    break;
                }
            }

            PrintWriter out = new PrintWriter(_connectionSocket.getOutputStream(), true);

            out.println("<IncomingCall>");
            out.println("<Username>" + _user.getUsername() + "</Username>");
            out.println("<IpAddress>" + _user.getIPAddress() + "</IpAddress>");
            out.println("</IncomingCall>");

            return;
        }
        catch (IOException ex) 
        {
            System.out.println("Error: " + ex.getMessage());
        }
    }

    public void acceptCallRequest(String senderIP) 
    {
        Socket _senderSocket = null;

        try 
        {
            // get the socket of the caller
            for (DirectoryServerConnection _con: _host._connections)
            {
                if (_con._user.getIPAddress().equals(senderIP))
                {
                    _senderSocket = _con._clientSocket;

                    // set the sender to Busy status
                    _con._user.setStatus("Busy");
                    break;
                }
            }

            PrintWriter outSender = new PrintWriter(_senderSocket.getOutputStream(), true);
            outSender.println("<Connect>");
            outSender.println("<IpAddress>lore.cs.purdue.edu:7771</IpAddress>");
            outSender.println("<IpAddress>lore.cs.purdue.edu:7772</IpAddress>");
            outSender.println("</Connect>");

            PrintWriter outClient = new PrintWriter(_clientSocket.getOutputStream(), true);
            outClient.println("<Connect>");
            outClient.println("<IpAddress>lore.cs.purdue.edu:7772</IpAddress>");
            outClient.println("<IpAddress>lore.cs.purdue.edu:7771</IpAddress>");
            outClient.println("</Connect>");

            // set sendee to Busy status
            _user.setStatus("Busy");

            // send updated directory to everyone
            _host.sendUpdatedDirectory();

            return;
        }
        catch (IOException ex) 
        {
            System.out.println("Error: " + ex.getMessage());
        }     
    }

    public void hangupRequest(String senderIP) 
    {
        Socket _senderSocket = null;

        try 
        {
            // get the socket of the caller
            for (DirectoryServerConnection _con: _host._connections)
            {
                if (_con._user.getIPAddress().equals(senderIP))
                {
                    _senderSocket = _con._clientSocket;

                    // set the sender to Available status
                    _con._user.setStatus("Available");
                    break;
                }
            }

            PrintWriter outSender = new PrintWriter(_senderSocket.getOutputStream(), true);
            outSender.println("<Hangup>");
            outSender.println("<IpAddress>"+_user.getIPAddress()+"</IpAddress>");
            outSender.println("</Hangup>");

            // set sendee to Busy status
            _user.setStatus("Available");

            // send updated directory to everyone
            _host.sendUpdatedDirectory();
            
            // reset the connections on the VoiceServers
            if (_host._viki == true)
            {
                _host._vs1._connections = null;
                _host._vs2._connections = null;
                
                _host._vs1._connections = new ArrayList<VoiceServerConnection>();
                _host._vs2._connections = new ArrayList<VoiceServerConnection>();
                
                _host._viki = false;
            }
            else
            {
                _host._viki = true;
            }

            return;
        }
        catch (IOException ex) 
        {
            System.out.println("Error: " + ex.getMessage());
        } 
    }
}
