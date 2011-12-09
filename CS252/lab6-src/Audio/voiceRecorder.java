package com.cs252.lab06;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Handler;
import android.util.Log;


public class voiceRecorder implements Runnable {
	private int sampleRate = 8000;
	private int channelConfig = AudioFormat.CHANNEL_CONFIGURATION_MONO;
	private int audioFormat = AudioFormat.ENCODING_PCM_16BIT;
	private DatagramSocket socket;
	static boolean onCall = false;

	voiceRecorder(String server) {
		try {
			this.socket = new DatagramSocket(8890);

			
		} catch (SocketException e) {		}  
	}
	
	public void run(){
		try {
			//android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_URGENT_AUDIO);
			
			DatagramPacket packet;
			int minBuf = AudioRecord.getMinBufferSize(sampleRate,channelConfig,audioFormat);
			AudioRecord recorder = new AudioRecord(MediaRecorder.AudioSource.MIC,sampleRate,channelConfig,audioFormat,minBuf*10);
			recorder.startRecording();
			
			while(true) {
				try {
					
					byte[] buffer = new byte[2048] ;
					recorder.read(buffer,0,buffer.length);
					packet = new DatagramPacket(buffer,buffer.length,InetAddress.getByName("lore.cs.purdue.edu"),8890);
	
					socket.send(packet);
				} catch (Exception e) {
					System.out.println(e);
				}
			}
		} catch (Exception e1) {
			System.out.println(e1);
		}
	}
}