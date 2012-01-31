package edu.purdue.cs252.lab06;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class CallReceiver extends BroadcastReceiver {

	public Handler _UIThread;  
	
	public CallReceiver() {
	
	}
	
	public CallReceiver (Handler UIThread) {
		if (UIThread != null)
			Log.i("CallReceiver", "Created: " + UIThread.toString());
		else 
			Log.i("CallReceiver", "Created with null Handler");
		
		_UIThread = CallActivity.UIhandler; 
	}
	
	@Override
	public void onReceive(Context c, Intent i) {
		String action = i.getAction();
		
		if (action.equals("hangup.the.phone")) {
			
			if (CallActivity.UIhandler != null)
				Log.i("CallReceiver", "Received the Intent: " + CallActivity.UIhandler.toString());
			else 
				Log.i("CallReceiver", "Recevied the Intent, but _UIThread is null.");
			
			// generate message to send to CallActivity and send it
			Message msg = new Message();
			msg.obj = "finishActivity";
			msg.what = 2;
			
			if (CallActivity.UIhandler != null) 
			{			
				CallActivity.UIhandler.sendMessage(msg);
				Log.i("CallReceiver", "Sent the message to UI.");
			}
		}
		
		return;
	}

}
