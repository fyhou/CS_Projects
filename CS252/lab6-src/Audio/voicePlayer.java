package com.cs252.lab06;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;

public class voicePlayer implements  Runnable{
	
	private int sampleRate = 8000;
	private int channelConfig = AudioFormat.CHANNEL_CONFIGURATION_MONO;
	private int audioFormat = AudioFormat.ENCODING_PCM_16BIT;
	private DatagramSocket socket;
	private AudioTrack speaker;
	
	voicePlayer(String server) {
		try {
			this.socket = new DatagramSocket(8890);

		} catch (SocketException e) {
			System.out.printf("Socket Exception!");
		}  
	}
	
	public void run() {
		//android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_URGENT_AUDIO);
		int minBuf = AudioTrack.getMinBufferSize(sampleRate, channelConfig, audioFormat);
		speaker = new AudioTrack(AudioManager.STREAM_VOICE_CALL, sampleRate, channelConfig, audioFormat, minBuf, AudioTrack.MODE_STREAM);
		speaker.play();
		byte[] buffer = new byte[2048];
		DatagramPacket dummyPacket = null;
		DatagramPacket packet;
		
		while(true) {
			try {
				final InetAddress serverAddr = InetAddress.getByName("lore.cs.purdue.edu");
				
				byte[] dummyBuf = new byte[1];
				dummyBuf[0] = 0;
				
				dummyPacket = new DatagramPacket(dummyBuf, dummyBuf.length, serverAddr, 8890);
				packet = new DatagramPacket(buffer, buffer.length);

				socket.send(dummyPacket);
				socket.receive(packet);

				buffer = packet.getData();
				speaker.write(buffer,0,buffer.length);
			} catch (Exception e) {
			}
		}
	}
}