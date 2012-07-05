package org.libsdl.app;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.KeyEvent;
import android.view.Window;
import android.view.WindowManager;
import android.os.PowerManager;
import android.widget.TextView;
import android.view.Menu;   
import android.view.MenuItem; 
import org.socool.pal.R;
import org.socool.pal.R.layout;
import org.socool.pal.R.style;

public class TransparentActivity extends Activity {
	public void onCreate(Bundle savedInstanceState) {   
        super.onCreate(savedInstanceState);   
        setTheme(R.style.Transparent);    
        setContentView(R.layout.transparent);   
	}
}
