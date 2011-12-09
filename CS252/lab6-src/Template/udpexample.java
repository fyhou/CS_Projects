package com.updclient.rudy;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class udpexample extends Activity {

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

		public static final String SERVERIP = "127.0.0.1"; // 'Within' the emulator!
		public static final int SERVERPORT = 4444;

		@Override
		public void run() {
			try {
				/* Retrieve the ServerName */
				InetAddress serverAddr = InetAddress.getByName(SERVERIP);

				Log.d("UDP", "S: Connecting...");
				/* Create new UDP-Socket */
				DatagramSocket socket = new DatagramSocket(SERVERPORT, serverAddr);

				/* By magic we know, how much data will be waiting for us */
				byte[] buf = new byte[17];
				/* Prepare a UDP-Packet that can
				 * contain the data we want to receive */
				DatagramPacket packet = new DatagramPacket(buf, buf.length);
				Log.d("UDP", "S: Receiving...");

				/* Receive the UDP-Packet */
				socket.receive(packet);
				Log.d("UDP", "S: Received: '" + new String(packet.getData()) + "'");
				Log.d("UDP", "S: Done.");
			} catch (Exception e) {
				Log.e("UDP", "S: Error", e);
			}
		}
	}

	public class Client implements Runnable {
		@Override
		public void run() {
			try {
				// Retrieve the ServerName
				InetAddress serverAddr = InetAddress.getByName(Server.SERVERIP);

				Log.d("UDP", "C: Connecting...");
				/* Create new UDP-Socket */
				DatagramSocket socket = new DatagramSocket();

				/* Prepare some data to be sent. */
				byte[] buf = ("Hello from Client").getBytes();

				/* Create UDP-packet with
				 * data & destination(url+port) */
				DatagramPacket packet = new DatagramPacket(buf, buf.length, serverAddr, Server.SERVERPORT);
				Log.d("UDP", "C: Sending: '" + new String(buf) + "'");

				/* Send out the packet */
				socket.send(packet);
				Log.d("UDP", "C: Sent.");
				Log.d("UDP", "C: Done.");
			} catch (Exception e) {
				Log.e("UDP", "C: Error", e);
			}
		}
	}
}