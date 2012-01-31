package com.tcp.example.rudy;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class TCPExample extends Activity {
	
	/*
	 * This code demonstrate how to set up a TCP server and send a TCP packet.
	 * 
	 * In order to see the results, you will need to check LogCat in Eclipse.
	 * For more information on LogCat: http://developer.android.com/guide/developing/debug-tasks.html
	 */

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		// Start the server
		new Thread(new Server()).start();
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) { }

		// Start the client
		new Thread(new Client()).start();
	}

	public class Server implements Runnable {

		public static final String SERVERIP = "127.0.0.1";
		public static final int SERVERPORT = 4444;

		@Override
		public void run() {
			try {
				// Create a socket for handling incoming requests
				ServerSocket server = new ServerSocket(SERVERPORT);

				do {
					// Wait for an incoming connection
					Log.d("TCP", "S: Waiting for new connection...");
					Socket clientSocket = server.accept();
					Log.d("TCP", "S: New connection received.");

					// Read data from the client
					InputStream stream = clientSocket.getInputStream();
					// InputStream is an abstract class. We needed to use a subclass
					BufferedReader data = new BufferedReader(new InputStreamReader(stream));

					// Read a line at a time
					String line;
					while ((line = data.readLine()) != null) {
						Log.d("TCP", "S: Received: '" + line + "'");
					}
					Log.d("TCP", "S: Done.");

				} while (true);

			} catch (IOException e) {
				Log.e("TCP", "S: Error", e);
			}
		}
	}

	public class Client implements Runnable {

		@Override
		public void run() {
			try {
				InetAddress serverAddr = InetAddress.getByName(Server.SERVERIP);

				// Connect to the server
				Log.d("TCP", "C: Connecting...");
				Socket clientSocket = new Socket(serverAddr, Server.SERVERPORT);

				// Sending a message to the server
				Log.d("TCP", "C: Sending a packet.");
				PrintWriter out = new PrintWriter(new BufferedWriter(
						new OutputStreamWriter(clientSocket.getOutputStream())), true);
				out.println("Hello from Client");
				Log.d("TCP", "C: Sent.");
				Log.d("TCP", "C: Done.");

				// Close the connection
				clientSocket.close();
			} catch (UnknownHostException e) {
				Log.e("TCP", "C: Error", e);
			} catch (IOException e) {
				Log.e("TCP", "C: Error", e);
			}
		}
	}
}