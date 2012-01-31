import java.io.*;
import java.net.*;

/**
 * This class facilitates the transmission of data across a network
 * 
 * @author jwallrab
 * 
 * DO NOT MODIFY THIS CLASS
 * 
 */
public class NetworkCommunicator {
	private DataInputStream dis;
	private DataOutputStream dos;
	private ObjectOutputStream oos;
	private ObjectInputStream ois;
	private ServerSocket ss; 				// ServerSocket for incoming
	private Socket socket; 					// Socket for outgoing connections
	private int port;
	private String connectIp;

	/**
	 * Constructor
	 */
	public NetworkCommunicator(){
		port = 51500;
		connectIp = "127.0.0.1";
	}

	public NetworkCommunicator(String ip, int port){
		this.port = port;
		connectIp = ip;
	}

	public NetworkCommunicator(Socket s, int port) throws Exception{
		socket = s;
		this.port = port;
		dos = new DataOutputStream(socket.getOutputStream());
		oos = new ObjectOutputStream(socket.getOutputStream());
		dis = new DataInputStream(socket.getInputStream());
		ois = new ObjectInputStream(socket.getInputStream());
	}

	/**
	 * Returns the socket for communication
	 * @return
	 */
	public Socket getSocket(){
		return socket;
	}

	/**
	 * Returns the server socket
	 * @return
	 */
	public ServerSocket getServerSocket(){
		return ss;
	}

	/**
	 * Return the IP address
	 * @return
	 */
	public String getIP() throws Exception {
		return InetAddress.getLocalHost().getHostAddress();
	}

	/**
	 * Return the server socket port
	 * @return
	 */
	public int getPort() {
		return ss.getLocalPort();
	}

	/**
	 * Sets the server socket port
	 * @param p
	 */
	public void setPort(int p){
		port = p;
	}


	/**
	 * Sends an integer
	 */
	public void sendInt(int i) throws Exception {
		
		dos.writeInt((int)i);
	}
	
	/**
	 * Sends a double
	 * @param d
	 * @throws Exception
	 */
	public void sendDouble(double d) throws Exception {
		dos.writeDouble(d);
	}

	/**
	 * Sends a serializable object
	 * @param o
	 * @throws Exception
	 */
	public void sendObject(Object o) throws Exception{
		
		oos.writeObject(o);
	}


	/**
	 * Resets the input stream
	 */
	public void resetInputStream() throws Exception {
		dis = new DataInputStream(socket.getInputStream());
	}

	/**
	 * Receive an integer
	 * @return
	 */
	public int receiveInt() throws Exception {
		
		return (int) dis.readInt();
	}
	
	/**
	 * Receive a double
	 * @return
	 * @throws Exception
	 */
	public Double receiveDouble() throws Exception {
		return dis.readDouble();
	}

	/**
	 * Receives an object
	 * @return
	 * @throws Exception
	 */
	public Object receiveObject() throws Exception{
		
		return ois.readObject();
	}

	/**
	 * Sends a connection request to the server
	 */
	public void sendConnect() throws Exception{
		socket = new Socket(InetAddress.getByName(connectIp), port);
		dos = new DataOutputStream(socket.getOutputStream());
		oos = new ObjectOutputStream(socket.getOutputStream());
		dis = new DataInputStream(socket.getInputStream());
		ois = new ObjectInputStream(socket.getInputStream());
		
	}

	/**
	 * Sends a connection request to the server
	 */
	public void sendConnect(String ip) throws Exception{
		socket = new Socket(InetAddress.getByName(ip), port);
		dos = new DataOutputStream(socket.getOutputStream());
		oos = new ObjectOutputStream(socket.getOutputStream());
		dis = new DataInputStream(socket.getInputStream());
		ois = new ObjectInputStream(socket.getInputStream());
	}

	/**
	 * Opens a socket to listen for incoming connections on
	 */
	public void openConnection() throws Exception {
		System.out.println("Listening...");
		socket = ss.accept();
		dos = new DataOutputStream(socket.getOutputStream());
		oos = new ObjectOutputStream(socket.getOutputStream());
		dis = new DataInputStream(socket.getInputStream());
		ois = new ObjectInputStream(socket.getInputStream());
		System.out.println("Connection Accepted");
	}

	/**
	 * Closes network connections
	 */
	public void closeConnection() throws Exception {
		socket.close();
	}

	/**
	 * Opens the ServerSocket for incoming messages
	 */
	public void openServerSocket() throws Exception{

		try {
			ss = new ServerSocket(port);
		} catch (IOException e) {
			ss = new ServerSocket();
			System.out.print("Using port " + port + " failed. ");
			port = ss.getLocalPort();
			System.out.println("Port is " + port);
		}
		System.out.println("Connection Open");
	}

	/**
	 * Closes the ServerSocket for incoming messages
	 */
	public void closeServerSocket() throws Exception {
		ss.close();
		System.out.println("Server Socket closed");
	}
}
