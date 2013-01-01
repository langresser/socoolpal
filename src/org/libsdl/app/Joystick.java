/*
 * Copyright 2011 Thomas Niederberger
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.libsdl.app;

import org.socool.pal.R;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

public class Joystick extends View {
    public final static int JOYSTICK_WIDTH = 166;
    public final static int JOYSTICK_HEIGHT = 166;
    public final static int STICK_WIDTH = 36;
    public final static int STICK_HEIGHT = 76;
    
    public final static int DIR_UP = 1;
    public final static int DIR_DOWN = 2;
    public final static int DIR_LEFT = 3;
    public final static int DIR_RIGHT = 4;
    public int m_dir = 0;
    
    Paint painter = new Paint();
    Bitmap m_dock;
    Bitmap m_up, m_down, m_left, m_right;
    Matrix matrixDock, matUp, matDown, matLeft, matRight;
    
    public Joystick(Context context) {
        super(context);
        
        int density = getResources().getDisplayMetrics().densityDpi;

		Bitmap jsbg = BitmapFactory.decodeResource(getResources(), R.drawable.jsbg);
		m_dock = Bitmap.createScaledBitmap(jsbg, JOYSTICK_WIDTH * density / 160, JOYSTICK_HEIGHT * density / 160, true);
		Bitmap jsup = BitmapFactory.decodeResource(getResources(), R.drawable.js4);
		m_up = Bitmap.createScaledBitmap(jsup, STICK_WIDTH * density / 160, STICK_HEIGHT * density / 160, true);
		Bitmap jsdown = BitmapFactory.decodeResource(getResources(), R.drawable.js8);
		m_down = Bitmap.createScaledBitmap(jsdown, STICK_WIDTH * density / 160, STICK_HEIGHT * density / 160, true);
		Bitmap jsleft = BitmapFactory.decodeResource(getResources(), R.drawable.js2);
		m_left = Bitmap.createScaledBitmap(jsleft, STICK_HEIGHT * density / 160, STICK_WIDTH * density / 160, true);
		Bitmap jsright = BitmapFactory.decodeResource(getResources(), R.drawable.js6);
		m_right = Bitmap.createScaledBitmap(jsright, STICK_HEIGHT * density / 160, STICK_WIDTH * density / 160, true);
		
		matrixDock = new Matrix();
		matUp = new Matrix();
		matUp.setTranslate((JOYSTICK_WIDTH - STICK_WIDTH) / 2  * density / 160, 15  * density / 160);
		matDown = new Matrix();
		matDown.setTranslate((JOYSTICK_WIDTH - STICK_WIDTH) / 2 * density / 160, (JOYSTICK_HEIGHT / 2 + 15) * density / 160);
		matLeft = new Matrix();
		matLeft.setTranslate(15 * density / 160, (JOYSTICK_HEIGHT - STICK_WIDTH) / 2 * density / 160);
		matRight = new Matrix();
		matRight.setTranslate((JOYSTICK_WIDTH / 2 + 10) * density / 160, (JOYSTICK_HEIGHT - STICK_WIDTH) / 2 * density / 160);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        //super.onDraw(canvas);
		canvas.drawBitmap(m_dock, matrixDock, painter);
		
		switch (m_dir) {
		case DIR_UP:
			canvas.drawBitmap(m_up, matUp, painter);
			break;
		case DIR_DOWN:
			canvas.drawBitmap(m_down, matDown, painter);
			break;
		case DIR_LEFT:
			canvas.drawBitmap(m_left, matLeft, painter);
			break;
		case DIR_RIGHT:
			canvas.drawBitmap(m_right, matRight, painter);
			break;
		}
    }
    
    private int getDirByPoint(int x, int y)
    {
        int centerX = getWidth() / 2;
        int centerY = getHeight() / 2;
        int diffX = x - centerX;
        int diffY = centerY - y;
        int absX = Math.abs(diffX);
        int absY = Math.abs(diffY);
        int dir = 0;
        
        if (diffY > 0 && (absX <= absY)) {
            dir = DIR_UP;
        } else if (diffY < 0 && absX <= absY) {
            dir = DIR_DOWN;
        } else if (diffX > 0 && absX >= absY) {
            dir = DIR_RIGHT;
        } else if (diffX < 0 && absX >= absY) {
            dir = DIR_LEFT;
        } else {
            dir = 0;
        }
        
 //       Log.v("dir", String.format("%1d %2d    %3d", x, y, dir));
        return dir;
    }
    
    @Override
    public boolean onTouchEvent(MotionEvent event) {
    	int x = (int) event.getX();
    	int y = (int) event.getY();
    	int action = event.getAction();
    	if (action == MotionEvent.ACTION_DOWN) {
    		
    	}
    	switch (action) {
    	case MotionEvent.ACTION_DOWN:
    	case MotionEvent.ACTION_MOVE:
    		int dir = getDirByPoint(x, y);
        	if (dir != m_dir) {
        		m_dir = dir;
        		SDLActivity.nativeDirChange(m_dir);
        		invalidate();
        	}
    		break;
    	case MotionEvent.ACTION_UP:
    	case MotionEvent.ACTION_CANCEL:
        	if (0 != m_dir) {
        		m_dir = 0;
        		SDLActivity.nativeDirChange(m_dir);
        		invalidate();
        	}
    		break;
    	}
    	
//    	if (listener != null && event.getAction() == MotionEvent.ACTION_DOWN) {
//    		listener.onValueChanged(getXValue(), getYValue());
//    	}
    	return true;
    }
}

