package com.liangfu.pwptracker;

import android.content.Context;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.util.AttributeSet;
import android.graphics.Color;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;

public class EditorSurfaceView extends SurfaceView implements SurfaceHolder.Callback 
{
	private Bitmap m_bitmap=null;
	private String m_imagePath="";

	public EditorSurfaceView(Context context, AttributeSet attrs) {
		super(context, attrs);
		getHolder().addCallback(this);
	}

	public void setImagePath(String imagePath)
	{
		m_imagePath=imagePath;
		m_bitmap=BitmapFactory.decodeFile(imagePath);
	}

	@Override
	public void draw(Canvas canvas) {
		if (canvas!=null){
			canvas.drawColor(Color.BLACK);
			if (m_bitmap!=null){
				canvas.drawBitmap(m_bitmap,10,10,null);
			}
		}
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
	}
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Canvas c = holder.lockCanvas(null);
		draw(c);
		holder.unlockCanvasAndPost(c);
	}
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
	}
	
}

