package edu.purdue.cs252.lab06;

import java.io.IOException;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class CallActivity extends Activity
{
	public static Handler UIhandler;
	
	String username;
	String userAddress;
	String writeAddress;
	String readAddress;
	
	VoiceRecorder vr;
	VoicePlayer vp;
	
	Thread t1;
	Thread t2;
	
	@Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.call);
        
        // extract data from extras
        Bundle extras = getIntent().getExtras();
        username = extras.getString("username");
        userAddress = extras.getString("userAddress");
        readAddress = extras.getString("readAddress");
        writeAddress = extras.getString("writeAddress");
        
        Button btn = null;
        btn = (Button) findViewById(R.id.widget33); 
        btn.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v)
			{
				DirectoryClient dc = new DirectoryClient(DirectoryClient._socket, UIhandler);
				
				try
				{
					dc.hangUp(userAddress);
					displayHangup();
				}
				catch (IOException e)
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
        });
        
        TextView tV = null;
        tV = (TextView) findViewById(R.id.callerName); 
        tV.setText(username);
        
        setupHandler();        
        
        beginCall();
    }
	
	public void beginCall()
	{
		vr = new VoiceRecorder(writeAddress);
		t1 = new Thread(vr);  
		t1.start();
    	
		vp = new VoicePlayer(readAddress);
		t2 = new Thread(vp);  
		t2.start();
	}
	
	public void setupHandler()
    {
    	UIhandler = new Handler() {    		
    		public void handleMessage(Message msg)
    		{
    			if (msg.what == 2)
    			{
    				displayHangup();
    			}
    		}
    	};
    	
    	@SuppressWarnings("unused")
		CallReceiver cr = new CallReceiver(UIhandler);
    }
	
	public void displayHangup()
    {		
    	try
    	{
    		vr.close();
        	vp.close();
        	
        	t1.join();
        	t2.join();
		}
    	catch (Exception ex)
    	{
			// TODO: handle this exception
		}
    	
    	vr = null;
    	vp = null;    	
		
		finish();
    }
}
