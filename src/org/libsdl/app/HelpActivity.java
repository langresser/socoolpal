package org.libsdl.app;

import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharsetEncoder;

import org.socool.pal.R;

import com.nd.dianjin.DianJinPlatform;
import com.nd.dianjin.listener.AppActivatedListener;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.TextView;
import android.widget.Toast;

public class HelpActivity extends Activity {
	private boolean m_isFAQ = true;

	protected void onCreate(Bundle savedInstanceState) {
        //Log.v("SDL", "onCreate()");
        super.onCreate(savedInstanceState);
		
        setContentView(R.layout.help);
        
        DianJinPlatform.initialize(this, 7209, "13891e5c79ce10b018d2d5a7c44dabd4");
 
        /*应用安装激活获取奖励接口,如果不需要这个功能可以去掉
          */
         DianJinPlatform.setAppActivatedListener(new AppActivatedListener() {
             public void onAppActivatedResponse(int responseCode, Float money) {
                 switch (responseCode) {
                 case DianJinPlatform.APP_ACTIVATED_SUCESS:
                     Toast.makeText(HelpActivity.this,
                             "奖励M币:" + String.valueOf(money), Toast.LENGTH_SHORT)
                             .show();
                     break;
                 case DianJinPlatform.APP_ACTIVATED_ERROR:
                     Toast.makeText(HelpActivity.this, "奖励M币:0",
                             Toast.LENGTH_SHORT).show();
                     break;
                 default:
                     Toast.makeText(HelpActivity.this, "奖励M币:ERROR",
                             Toast.LENGTH_SHORT).show();
                     break;
                 }
             }
         });
        
        Button btnFeedback = (Button)findViewById(R.id.btnFeedback);
        btnFeedback.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
			}
		});
        
        Button btnBBS = (Button)findViewById(R.id.btnBBS);
        btnBBS.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				setIntent(new Intent("http://bananastudio.cn/"));
			}
		});
        
	    final SharedPreferences settings = getSharedPreferences("sdlpalsetting", 0);  
	    final SharedPreferences.Editor editor = settings.edit();  
//	    editor.putBoolean("silentMode", mSilentMode);  

        final Button btnBattlMode = (Button)findViewById(R.id.btnBattle);
        btnBattlMode.setText(settings.getBoolean("isclassic", true) ? "回合制" : "即时制");
        btnBattlMode.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				final boolean isClassicMode = !settings.getBoolean("isclassic", true);
				btnBattlMode.setText(isClassicMode ? "回合制" : "即时制");
				
				editor.putBoolean("isclassic", isClassicMode);
				editor.commit();
			}
		});
        
        final CheckBox joystick = (CheckBox)findViewById(R.id.chkJoystick);
        joystick.setChecked(settings.getBoolean("isjoystickshow", true));
        joystick.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {			
				editor.putBoolean("isjoystickshow", isChecked);
				editor.commit();
			}
		});
        
        
        final Button btnMoveMode = (Button)findViewById(R.id.btnMove);
        btnMoveMode.setText( (SDLActivity.nativeGetFlyMode() != 0) ? "穿墙" : "正常");
        btnMoveMode.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				final boolean isFlyMode = !(SDLActivity.nativeGetFlyMode() != 0);
				btnMoveMode.setText(isFlyMode ? "穿墙" : "正常");
				SDLActivity.nativeHack(0, isFlyMode ? 1 : 0);
			}
		});
        
        
        Button btnUplev = (Button)findViewById(R.id.btnUplev);
        btnUplev.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				SDLActivity.nativeHack(1, 0);
			}
		});
        
        Button btnAddMoney = (Button)findViewById(R.id.btnAddmoney);
        btnAddMoney.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				SDLActivity.nativeHack(2, 0);
			}
		});
        
        final TextView textView = (TextView)findViewById(R.id.gongl);
        final Button btnGongl = (Button)findViewById(R.id.btnGongl);
        btnGongl.setText(m_isFAQ ? "攻略" : "FAQ");
        btnGongl.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				m_isFAQ = !m_isFAQ;
				btnGongl.setText(m_isFAQ ? "攻略" : "FAQ");
				
				
				String fileName = m_isFAQ ? "sdlpal/faq.txt" : "sdlpal/gl.txt";
				 try {
						InputStream gongl = getAssets().open(fileName);
						int size = gongl.available();
						byte[] buffer = new byte[size];
						gongl.read(buffer);
						String text = new String(buffer, "utf-8");
						textView.setText(text);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
        
		String fileName = m_isFAQ ? "sdlpal/faq.txt" : "sdlpal/gl.txt";
		 try {
				InputStream gongl = getAssets().open(fileName);
				int size = gongl.available();
				byte[] buffer = new byte[size];
				gongl.read(buffer);
				String text = new String(buffer, "utf-8");
				textView.setText(text);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}    
	}
	
	protected void onDestroy() {
		super.onDestroy();
		DianJinPlatform.destroy();
	}
}
