package com.audiorecorderandudp.rudy;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;

import android.app.Activity;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.media.MediaPlayer.OnCompletionListener;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class audiorecorderudp extends Activity {

	public static final String SERVERIP = "127.0.0.1";
	public static final int SERVERPORT = 4444;

	boolean recording = false;

	MediaRecorder recorder;
	MediaPlayer player;

	Button recordButton;

	Uri audioFilePath;
	Uri inputFilePath;

	File outputFile;
	File inputFile;

	long fileSize;
	int bytesNeeded = 50000;

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

		// File to which audio should be recorded
		outputFile = getFileStreamPath("output.amr");
		inputFile = getFileStreamPath("input.amr");
		audioFilePath = Uri.parse(outputFile.getAbsolutePath());
		inputFilePath = Uri.parse(inputFile.getAbsolutePath());

		// Button to record to a file using microphone
		recordButton = (Button) findViewById(R.id.record);
		recordButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				if (!recording) {
					// Start the recording
					recording = true;
					recordButton.setText("Stop Recording");

					recorder = new MediaRecorder();
					// This parameter set the input to be the microphone
					recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
					recorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
					recorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
					// We set the path of the file
					recorder.setOutputFile(audioFilePath.getPath());
					try {
						recorder.prepare();
						// Recording will start after next instruction
						recorder.start();
					} catch (IllegalStateException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				else {
					recording = false;
					//Stop the recording and tidy up
					recorder.stop();
					recorder.release();

					try {
						InetAddress serverAddr = InetAddress.getByName(SERVERIP);
						/* Create new UDP-Socket */
						DatagramSocket socket = new DatagramSocket();;
						InputStream is = new FileInputStream(outputFile);
						long length = outputFile.length();

						if (length > Integer.MAX_VALUE) {
							// File is too large
						}

						// Create the byte array to hold the data
						byte[] bytes = new byte[(int)length];
						fileSize = length;

						int offset = 0;
						int numRead = 0;

						while (offset < bytes.length
								&& (numRead=is.read(bytes, offset, bytes.length-offset)) >= 0) {
							offset += numRead;
						}
						if (offset < bytes.length) {
							throw new IOException("Could not completely read file "+outputFile.getName());
						}

						is.close();

						/* Create UDP-packet with
						 * data & destination(url+port) */
						DatagramPacket packet = new DatagramPacket(bytes, bytes.length, serverAddr, SERVERPORT); // TO BE CHANGED
						Log.d("UDP", "C: Sending: '" + new String(bytes) + "'");

						/* Send out the packet */
						socket.send(packet);
						Log.d("UDP", "C: Sent.");

						recordButton.setText("Record");
					} catch (UnknownHostException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (FileNotFoundException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		});
	}

	class Server implements Runnable {

		@Override
		public void run() {
			try {
				/* Retrieve the ServerName */
				InetAddress serverAddr = InetAddress.getByName(SERVERIP);

				Log.d("UDP", "S: Connecting...");
				/* Create new UDP-Socket */
				DatagramSocket socket = new DatagramSocket(SERVERPORT, serverAddr);

				/* By magic we know, how much data will be waiting for us */
				byte[] buf = new byte[bytesNeeded];
				
				do {
					/* Prepare a UDP-Packet that can
					 * contain the data we want to receive */
					DatagramPacket packet = new DatagramPacket(buf, buf.length);
					Log.d("UDP", "S: Receiving...");
					/* Receive the UDP-Packet */
					socket.receive(packet);
					Log.d("UDP", "S: Received: '" + new String(packet.getData()) + "'");

					FileOutputStream inputStream = new FileOutputStream(inputFile); 
					inputStream.write(packet.getData());
					inputStream.close();

					// Play
					player = new MediaPlayer();

					inputFile = getFileStreamPath("input.amr");
					inputFilePath = Uri.parse(inputFile.getAbsolutePath());

					File file = new File(inputFilePath.getPath());

					long newSize = file.length();
					if (newSize != fileSize) {
						Log.d("ERROR", "File size are different");
					}
					FileInputStream fis = new FileInputStream(file);
					player.setDataSource(fis.getFD());

					// We do not allow to loop/repeat the sound
					player.setLooping(false);

					player.prepare();
					player.start();
					//Thread.sleep(1000);
				} while (true);
			} catch (IllegalArgumentException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IllegalStateException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				StackTraceElement[] stack = e.getStackTrace();
			}

//			// When we reach the end of the file
//			player.setOnCompletionListener(new OnCompletionListener() { 
//				@Override 
//				public void onCompletion(MediaPlayer player) { 
//					player.stop();
//				}
//			});
		}
	}
}
