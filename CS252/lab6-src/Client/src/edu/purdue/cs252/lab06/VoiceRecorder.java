package edu.purdue.cs252.lab06;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

public class VoiceRecorder implements Runnable
{
	private int BUFFER_SIZE = 768;
	
	private int sampleRate = 8000;
	private int channelConfig = AudioFormat.CHANNEL_CONFIGURATION_MONO;
	private int audioFormat = AudioFormat.ENCODING_PCM_16BIT;
	private DatagramSocket socket;
	AudioRecord recorder;
	
	private String _server;
	private int _port;
	
	private boolean recordAudio = true;

	VoiceRecorder(String address)
	{
		Log.i("VoiceRecorder", address);
		
		try
		{			
			_server = address.substring(0, address.length() - 5);
			_port = Integer.parseInt(address.substring(address.length() - 4, address.length()));
			
			this.socket = new DatagramSocket(_port);
		}
		catch (SocketException e)
		{
			// TODO: handle this exception
		}  
	}
	
	public void run()
	{
		android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_AUDIO);
		
		byte[] buffer = new byte[BUFFER_SIZE];
		DatagramPacket packet;
		
		try
		{			
			int minBuf = AudioRecord.getMinBufferSize(sampleRate, channelConfig, audioFormat);
			recorder = new AudioRecord(MediaRecorder.AudioSource.MIC, sampleRate, channelConfig, audioFormat, minBuf); 
			recorder.startRecording();
		}
		catch (Exception ex)
		{
			// TODO: handle this exception
		}
		
		while(recordAudio)
		{
			try
			{
				recorder.read(buffer, 0, buffer.length);
				
				packet = new DatagramPacket(buffer, buffer.length, InetAddress.getByName(_server), _port);	
				socket.send(packet);
			}
			catch (Exception ex)
			{
				// TODO: handle this exception					
			}
		}
		
		buffer = null;
	}
	
	public void close()
	{
		recordAudio = false;
				
		recorder.stop();
		recorder.release();
		
		socket.close();
	}
}