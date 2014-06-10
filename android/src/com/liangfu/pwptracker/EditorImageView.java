package com.liangfu.pwptracker;

import android.content.Context;
// import android.view.SurfaceHolder;
import android.widget.ImageView;
import android.util.AttributeSet;
import android.graphics.Color;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.view.animation.Animation;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.widget.TextView;
import android.view.View;
import android.util.Log;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;

import com.liangfu.pwptracker.R;

public class EditorImageView extends ImageView 
//implements SurfaceHolder.Callback 
{
	private Bitmap m_bitmap=null;
	private String m_imagePath="";
	private GestureDetector gestureDetector;

	public EditorImageView(Context context, AttributeSet attrs) {
		super(context, attrs);
		// getHolder().addCallback(this);
		gestureDetector = new GestureDetector(context, new GestureListener(this));
	}

	public void setImagePath(String imagePath)
	{
		m_imagePath=imagePath;
		m_bitmap=BitmapFactory.decodeFile(imagePath);
	}

	@Override
	public void onDraw(Canvas canvas) {
		if (canvas!=null){
			canvas.drawColor(Color.BLACK);
			if (m_bitmap!=null){
				// setImageBitmap(m_bitmap);
				// setScaleType(ImageView.ScaleType.CENTER_INSIDE);
				
				Rect src = new Rect(0,0,m_bitmap.getWidth(),m_bitmap.getHeight());
				float imgw=m_bitmap.getWidth();
				float imgh=m_bitmap.getHeight();
				float w=getWidth();
				float h=getHeight();
				float xscale=w/imgw;float yscale=h/imgh;
				float scale=(xscale<=yscale)?xscale:yscale;
				long xloc=Math.round((w-imgw*scale)*.5);
				long yloc=Math.round((h-imgh*scale)*.5);
				Rect dst = new Rect((int)xloc,(int)yloc,(int)(w-xloc),(int)(h-yloc));
				canvas.drawBitmap(m_bitmap,src,dst,null);
			}
		}
	}

	private class GestureListener extends GestureDetector.SimpleOnGestureListener 
	{
		private EditorImageView holder;
		public GestureListener(EditorImageView v)
		{
			this.holder=v;
		}
		@Override
		public boolean onDown(MotionEvent e) {
			return true;
		}
		@Override
		public boolean onDoubleTap(MotionEvent e) {
			// float x = e.getX();
			// float y = e.getY();
			// Log.d("EditorImageView::GestureListener","Double Tapped at: (" + x + "," + y + ")");
			holder.onDoubleTap(e);
			return true;
		}
	}

	// delegate the event to the gesture detector
	@Override
	public boolean onTouchEvent(MotionEvent e) {
		return gestureDetector.onTouchEvent(e);
	}

	public boolean onDoubleTap(MotionEvent e) {
		float x = e.getX();
		float y = e.getY();
		Log.d("EditorImageView","Double Tapped at: (" + x + "," + y + ")");
		Animation anim = AnimationUtils.loadAnimation(getContext(), R.anim.scale_up);
		startAnimation(anim);
		return true;
	}

	// private void scaleUp()
	// {
	// 	Animation scale = new ScaleAnimation(fromXscale, toXscale, fromYscale, toYscale, 
	// 																			 Animation.RELATIVE_TO_SELF, 0.5f, 
	// 																			 Animation.RELATIVE_TO_SELF, 0.5f);
	// 	scale.setDuration(1000);
	// 	Animation slideUp = new TranslateAnimation(fromX, toX, fromY, toY);
	// 	slideUp.setDuration(1000);
	// 	AnimationSet animSet = new AnimationSet(true);
	// 	animSet.setFillEnabled(true);
	// 	animSet.addAnimation(scale);
	// 	animSet.addAnimation(slideUp);
	// 	logo.startAnimation(animSet);
	// }
	
}

