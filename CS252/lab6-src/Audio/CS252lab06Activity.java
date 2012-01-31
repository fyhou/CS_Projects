package com.cs252.lab06;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class CS252lab06Activity extends Activity
{
	private Button button1;
	private Button button2;
	private Button button3;
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
    	super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        button1 = (Button)findViewById(R.id.record);
        
        this.button1 = (Button)this.findViewById(R.id.record);
		this.button1 .setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
		    	voiceRecorder vr = new voiceRecorder("lore.cs.purdue.edu");
		    	Thread threadVR = new Thread(vr);  
		    	threadVR.start();
			}
		});
		
		button2 = (Button)findViewById(R.id.listen);
		
        this.button2 = (Button)this.findViewById(R.id.listen);
		this.button2 .setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				voicePlayer vp = new voicePlayer("lore.cs.purdue.edu");
				Thread threadVP = new Thread(vp);  
				threadVP.start();
		    }
		});
		
		button3 = (Button)findViewById(R.id.stop);
		
        this.button3 = (Button)this.findViewById(R.id.stop);
		this.button3 .setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				finish();
	            System.exit(0);
		    }
		});
    }
}