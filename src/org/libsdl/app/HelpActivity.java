package org.libsdl.app;

import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharsetEncoder;

import org.socool.pal.R;

import com.nd.dianjin.DianJinPlatform;
import com.nd.dianjin.DianJinPlatform.Oriention;
import com.nd.dianjin.listener.AppActivatedListener;
import com.nd.dianjin.webservice.WebServiceListener;
import com.umeng.analytics.MobclickAgent;
import com.umeng.fb.UMFeedbackService;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.TextView;
import android.widget.Toast;

public class HelpActivity extends Activity {
	private boolean m_isFAQ = true;
	private float m_currentFB = 0;

	protected void onCreate(Bundle savedInstanceState) {
        //Log.v("SDL", "onCreate()");
        super.onCreate(savedInstanceState);
        
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,  
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        MobclickAgent.onError(this);
        setContentView(R.layout.help);
        
        DianJinPlatform.initialize(this, 7209, "13891e5c79ce10b018d2d5a7c44dabd4");
 
        /*应用安装激活获取奖励接口,如果不需要这个功能可以去掉
          */
         DianJinPlatform.setAppActivatedListener(new AppActivatedListener() {
             public void onAppActivatedResponse(int responseCode, Float money) {
                 switch (responseCode) {
                 case DianJinPlatform.APP_ACTIVATED_SUCESS:
                	 updateScore();
                     Toast.makeText(HelpActivity.this,
                             "奖励元宝:" + String.valueOf(money), Toast.LENGTH_SHORT)
                             .show();
                     break;
                 case DianJinPlatform.APP_ACTIVATED_ERROR:
                     Toast.makeText(HelpActivity.this, "奖励元宝:0",
                             Toast.LENGTH_SHORT).show();
                     break;
                 default:
                     Toast.makeText(HelpActivity.this, "奖励M币:ERROR",
                             Toast.LENGTH_SHORT).show();
                     break;
                 }
             }
         });
         
         Button btnMoreApp = (Button)findViewById(R.id.btnMoreApp);
		 btnMoreApp.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				DianJinPlatform.showOfferWall(HelpActivity.this, Oriention.SENSOR);
			}
		});
        
        Button btnFeedback = (Button)findViewById(R.id.btnFeedback);
        btnFeedback.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				UMFeedbackService.openUmengFeedbackSDK(HelpActivity.this);
			}
		});
        
        Button btnBBS = (Button)findViewById(R.id.btnBBS);
        btnBBS.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				startActivity(new Intent("http://bananastudio.cn/"));
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
        
        final TextView hackview = (TextView)findViewById(R.id.textEnableHack);
        hackview.setText(isEnableHack() ? "金手指功能（已开启）" : "金手指功能（未开启）");
        
        final Button btnMoveMode = (Button)findViewById(R.id.btnMove);
        btnMoveMode.setText( (SDLActivity.nativeGetFlyMode() != 0) ? "穿墙" : "正常");
        btnMoveMode.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				if (!checkEnableHack()) {
					return;
				}
				final boolean isFlyMode = !(SDLActivity.nativeGetFlyMode() != 0);
				btnMoveMode.setText(isFlyMode ? "穿墙" : "正常");
				SDLActivity.nativeHack(0, isFlyMode ? 1 : 0);
			}
		});
        
        
        Button btnUplev = (Button)findViewById(R.id.btnUplev);
        btnUplev.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				if (!checkEnableHack()) {
					return;
				}
				SDLActivity.nativeHack(1, 0);
			}
		});
        
        Button btnAddMoney = (Button)findViewById(R.id.btnAddmoney);
        btnAddMoney.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				if (!checkEnableHack()) {
					return;
				}
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
	
	protected boolean isEnableHack()
	{
		final SharedPreferences settings = getSharedPreferences("sdlpalsetting", 0);
		return settings.getBoolean("enablehack", false);
	}
	
	protected boolean checkEnableHack()
	{
		final SharedPreferences settings = getSharedPreferences("sdlpalsetting", 0);
		boolean enable = settings.getBoolean("enablehack", false);
		if (enable) {
			return true;
		}
		
		final String text = "当您获得100元宝时将自动开启金手指功能。您可以通过安装精品推荐应用的方式免费获取元宝。当前元宝:" + m_currentFB;
		Dialog dialog = new AlertDialog.Builder(HelpActivity.this).setTitle("").setMessage(text)
				.setPositiveButton("知道了",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int whichButton) {
								dialog.cancel();
							}
						}).setNegativeButton("获取元宝",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int which) {
								DianJinPlatform.showOfferWall(HelpActivity.this, Oriention.SENSOR);
								dialog.cancel();
							}
						}).create();// 创建按钮
		dialog.show();
		updateScore();
		return false;
	}
	
	protected void updateScore()
	{
		DianJinPlatform.getBalance(this,
                new WebServiceListener<Float>() {
                    @Override
                    public void onResponse(int responseCode, Float t) {
                        switch (responseCode) {
                        case DianJinPlatform.DIANJIN_SUCCESS:
                        	m_currentFB = t;
                        	if (m_currentFB >= 100.0) {
                        		final SharedPreferences settings = getSharedPreferences("sdlpalsetting", 0);  
                        	    final SharedPreferences.Editor editor = settings.edit(); 
                        	    editor.putBoolean("enablehack", true);
                        	    editor.commit();
                        	    
                        	    final TextView hackview = (TextView)findViewById(R.id.textEnableHack);
                                hackview.setText("金手指功能（已开启）");
                        	}
                            break;
                        case DianJinPlatform.DIANJIN_ERROR:
                            Toast.makeText(HelpActivity.this, "获取余额失败",
                                    Toast.LENGTH_SHORT).show();
                            break;
                        default:
                            Toast.makeText(HelpActivity.this,
                                    "未知错误，错误码为:" + responseCode,
                                    Toast.LENGTH_SHORT).show();
                        }
                    }
                });
	}
	
	protected void onDestroy() {
		super.onDestroy();
		DianJinPlatform.destroy();
	}
	
	protected void onPause() {
		super.onPause();
		
		MobclickAgent.onPause(this);
	}
	
	protected void onResume() {
		super.onResume();
		MobclickAgent.onResume(this);
	}
}
