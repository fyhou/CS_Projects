package edu.purdue.cs252.lab06;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        setupBindings();
    }
    
    public void setupBindings()
	{
		Button button1 = (Button)findViewById(R.id.button1);
		
		button1.setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v)
			{
				EditText serverAddress = (EditText)findViewById(R.id.editText1);
				EditText username = (EditText)findViewById(R.id.editText2);
				
				if (serverAddress.getText().length() > 0 &&
					username.getText().length() > 0)
				{
					Intent i = new Intent(MainActivity.this, DirectoryActivity.class);
					i.putExtra("serverAddress", serverAddress.getText().toString());
					i.putExtra("username", username.getText().toString());
					
					startActivity(i);
				}
				else
				{
				   AlertDialog.Builder adb = new AlertDialog.Builder(MainActivity.this);
				   
				   adb.setTitle("Error");
				   adb.setMessage("Please specify your Server Address and Username to continue.");
				   adb.setPositiveButton("OK", null);
				   adb.show();
				}	       
	        }
        });
	}
}
