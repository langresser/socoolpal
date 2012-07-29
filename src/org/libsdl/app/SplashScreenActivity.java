package org.libsdl.app;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
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

public class SplashScreenActivity extends Activity {
	public static byte m_dataVersion = 1;
	public void onCreate(Bundle savedInstanceState) {   
        super.onCreate(savedInstanceState);   
  
        setContentView(R.layout.transparent);
        
        if (!isSdCardEnable()) {
        	Dialog dialog = new AlertDialog.Builder(SDLActivity.mSingleton).setTitle("PAL").setMessage("未检测到SD卡，请加载SD卡，然后重新开启游戏。")
					.setPositiveButton("确定",
							new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int whichButton) {
									finish();
									dialog.cancel();
								}
							}).setNegativeButton("取消",
							new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog, int which) {
									finish();
									dialog.cancel();
								}
							}).create();// 创建按钮
			dialog.show();
			return;
        }
        
        TextView textView = (TextView)findViewById(R.id.TextView01);
        textView.setText("正在检测游戏数据...");
        if (isNeedUpdateData()) {
        	textView.setText("正在初始化游戏数据，请稍后...");

			Thread thread = new Thread(new Runnable() {
				public void run() {
					updateData();
					startActivity(new Intent(SplashScreenActivity.this, SDLActivity.class));
					finish();
				}
			});
			thread.start();
        	
        } else {
        	startActivity(new Intent(this, SDLActivity.class));
        	finish();
        }    
	}
	
	public boolean isSdCardEnable()
	{
		if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {  
            // sd card 可用  
            return true;     
         }else {  
            //当前不可用  
        	return false;
         } 
	}
	
	public String getSDCardPath(String file)
	{
		return Environment.getExternalStorageDirectory().getPath() + "/" + file;
	}
	
	public boolean isNeedUpdateData()
	{
		try {
			InputStream checkFile = new FileInputStream(getSDCardPath("sdlpal/dataflag.cfg"));
			int data = checkFile.read();
			checkFile.close();
			if (data < m_dataVersion) {
				return true;
			}
		} catch (FileNotFoundException e) {
			return true;
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return false;
	}
	
	public void updateData()
	{
		AssetManager amgr = getAssets();
		boolean updateOk = true;
		try {
			String[] fileList = amgr.list("sdlpal");
			int count = fileList.length;
			
			File dir = new File(getSDCardPath("sdlpal"));
			if (!dir.exists()) {
				dir.mkdir();
			}

			for (int i = 0; i < count; ++i) {
				String file = fileList[i];
				if (!copyFile("sdlpal/" + file)) {
					updateOk = false;
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
			updateOk = false;
		}
		
		// 更新成功，写入新的版本号
		if (updateOk) {
			try {
				File checkFile = new File(getSDCardPath("sdlpal/dataflag.cfg"));
				if (!checkFile.exists()) {
					checkFile.createNewFile();
				}
				OutputStream output = new FileOutputStream(checkFile);
				output.write(m_dataVersion);
				output.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public boolean copyFile(String file)
	{
		boolean isPartFile = file.indexOf(".part") != -1;
		try {
			if (isPartFile) {
				// 只处理头一个
				if (file.endsWith(".part1") == false) {
					return true;
				}
				
				String destFile = file.substring(0, file.lastIndexOf('.'));
				File outputFile = new File(getSDCardPath(destFile));
				if (!outputFile.exists()) {
					outputFile.createNewFile();
				}
				OutputStream output = new FileOutputStream(outputFile);
				
				for (int i = 1; i < 30; ++i) {
					final String fileName = destFile + ".part" + i;
					try {
						InputStream input = getAssets().open(fileName);
						
						byte bt[] = new byte[1024];
						int c;
						while ((c = input.read(bt)) > 0) {
							output.write(bt, 0, c); 
						}
						
						input.close();
					} catch (FileNotFoundException e){
						break;
					}
				}
				
				output.close();
				return true;
			} else {
				InputStream input = getAssets().open(file);
				File outputFile = new File(getSDCardPath(file));
				if (!outputFile.exists()) {
					outputFile.createNewFile();
				}
				OutputStream output = new FileOutputStream(outputFile);
				
				byte bt[] = new byte[1024];
				int c;
				while ((c = input.read(bt)) > 0) {
					output.write(bt, 0, c); 
				}
				
				input.close();
				output.close();
				return true;
			}	
		}catch (IOException e) {
			e.printStackTrace();
			return false;
		}
	}
}
