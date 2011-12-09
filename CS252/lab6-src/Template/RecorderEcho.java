package com.recorder.echo.rudy;

import android.app.Activity;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.MediaRecorder;
import android.os.Bundle;

public class RecorderEcho extends Activity {

	private int bufferSize;
	private byte[] buffer;

	private int sampleRate = 11025;
	private int channelConfig = AudioFormat.CHANNEL_CONFIGURATION_MONO;
	private int audioFormat = AudioFormat.ENCODING_PCM_16BIT;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		bufferSize = AudioRecord.getMinBufferSize(sampleRate, 
				channelConfig, audioFormat);

		// Temporary buffer to store the audio input. Used to record and play.
		buffer = new byte[bufferSize];

		// Start a thread to play the sound
		new Thread(new Player()).start();
		// Start a thread that records sound
		new Thread(new Recorder()).start();
	}

	public class Player implements Runnable {

		/**
		 * Class that will play the sound
		 */

		private AudioTrack player;

		@Override
		public void run() {
			player = new AudioTrack(AudioManager.STREAM_VOICE_CALL, sampleRate, 
					channelConfig, audioFormat, bufferSize, AudioTrack.MODE_STREAM);

			player.play();

			// Loop forever playing the audio
			while (true) {
				// Play the sound
				player.write(buffer, 0, bufferSize);
			}

		}
	}

	public class Recorder implements Runnable {

		/**
		 * Class that will record sound.
		 */

		private AudioRecord recorder;

		@Override
		public void run() {
			// Create a new recorder
			recorder = new AudioRecord(MediaRecorder.AudioSource.MIC, sampleRate,
					channelConfig, audioFormat, bufferSize);

			// Start the recording
			recorder.startRecording();

			// Loop forever recording input
			while (true) {
				// Read from the microphone
				recorder.read(buffer, 0, bufferSize);
			}

		}
	}
}