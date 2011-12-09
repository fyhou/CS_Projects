package edu.purdue.cs252.lab06;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;

public class VoicePlayer implements Runnable
{	
	private int BUFFER_SIZE = 768;
	
	private int sampleRate = 8000;
	private int channelConfig = AudioFormat.CHANNEL_CONFIGURATION_MONO;
	private int audioFormat = AudioFormat.ENCODING_PCM_16BIT;
	private DatagramSocket socket;
	private AudioTrack speaker;
	
	private String _server;
	private int _port;
	
	private boolean playAudio = true;
	
	VoicePlayer(String address)
	{
		Log.i("VoicePlayer", address);
		
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
		
		int minBuf = AudioTrack.getMinBufferSize(sampleRate, channelConfig, audioFormat);
		speaker = new AudioTrack(AudioManager.STREAM_VOICE_CALL, sampleRate, channelConfig, audioFormat, minBuf, AudioTrack.MODE_STREAM);
		speaker.play();
		
		byte[] buffer = new byte[BUFFER_SIZE];
		DatagramPacket packet;
		
		DatagramPacket dummyPacket = null;
		
		try
		{
			// send the dummy packet to join the server
			byte[] dummyBuf = new byte[1];
			dummyBuf[0] = 0;
			dummyPacket = new DatagramPacket(dummyBuf, dummyBuf.length, InetAddress.getByName(_server), _port);
			
			socket.send(dummyPacket);
		}
		catch (Exception ex)
		{
			// TODO: handle this exception
		}
				
		while(playAudio)
		{
			try
			{				
				packet = new DatagramPacket(buffer, buffer.length);
				socket.receive(packet);

				buffer = packet.getData();
				speaker.write(buffer,0,buffer.length);
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
		playAudio = false;
		
		try 
		{
			speaker.stop();
			speaker.release();
			
			speaker = null;
		}
		catch (Exception ex)
		{
			Log.e("VoicePlayer", ex.getMessage());
		}
		
		socket.close();
	}
}