package org.libsdl.app;

import java.io.InputStream;

import org.socool.pal.R;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class HelpActivity extends Activity {

	protected void onCreate(Bundle savedInstanceState) {
        //Log.v("SDL", "onCreate()");
        super.onCreate(savedInstanceState);
		
        setContentView(R.layout.help);
        
        Button btnFeedback = (Button)findViewById(R.id.btnFeedback);
        btnFeedback.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
			}
		});
        
        Button btnBBS = (Button)findViewById(R.id.btnBBS);
        btnBBS.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
			}
		});
        
        TextView textView = (TextView)findViewById(R.id.gongl);
        
        InputStream gongl = getAssets().open("sdlpal/gongl.txt");
        textView.setText();
	}
}
