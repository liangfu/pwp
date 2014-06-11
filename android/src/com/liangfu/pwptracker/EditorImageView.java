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
import android.view.ScaleGestureDetector;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.widget.TextView;
import android.view.View;
import android.util.Log;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.graphics.drawable.Drawable;
import android.graphics.Paint;

import com.liangfu.widgets.GestureImageView;

import com.liangfu.pwptracker.R;

public class EditorImageView extends ImageView 
//implements SurfaceHolder.Callback 
{
	private Bitmap m_bitmap=null;
	private String m_imagePath="";
	private GestureDetector gestureDetector;

	private Drawable mIcon;
	private float mPosX=0;
	private float mPosY=0;
    
	private float mLastTouchX=0;
	private float mLastTouchY=0;

	private static final int INVALID_POINTER_ID = -1;
	private int mActivePointerId = INVALID_POINTER_ID;

	private ScaleGestureDetector mScaleDetector;
	private float mScaleFactor = 1.f;

	private Paint borderPaint = null;
	private Paint backgroundPaint = null;

	private float pivotPointX = 0f;
	private float pivotPointY = 0f;

	public EditorImageView(Context context, AttributeSet attrs) {
		super(context, attrs);

		gestureDetector = new GestureDetector(context, new GestureListener(this));
    mScaleDetector = new ScaleGestureDetector(context, new ScaleListener());

		borderPaint = new Paint();
    borderPaint.setARGB(255, 255, 128, 0);
    borderPaint.setStyle(Paint.Style.STROKE);
    borderPaint.setStrokeWidth(4);

    backgroundPaint = new Paint();
    backgroundPaint.setARGB(32, 255, 255, 255);
    backgroundPaint.setStyle(Paint.Style.FILL);
	}

	public void setImagePath(String imagePath)
	{
		m_imagePath=imagePath;
		m_bitmap=BitmapFactory.decodeFile(imagePath);
		//mIcon = context.getResources().getDrawable(R.drawable.icon);
		mIcon = Drawable.createFromPath(imagePath);
		// mIcon.setBounds(0, 0, mIcon.getIntrinsicWidth(), mIcon.getIntrinsicHeight());
		float w=m_bitmap.getWidth()*getResources().getDisplayMetrics().density;
		float h=m_bitmap.getHeight()*getResources().getDisplayMetrics().density;
		mIcon.setBounds(0, 0, Math.round(w), Math.round(h));
	}

	// @Override
	// public void onDraw(Canvas canvas) {
	// 	super.onDraw(canvas);
	// 	canvas.save();
	// 	canvas.translate(mPosX, mPosY);
	// 	canvas.scale(mScaleFactor, mScaleFactor);
	// 	mIcon.draw(canvas);
	// 	canvas.restore();
	// }
	
	@Override
	public void onDraw(Canvas canvas) {
		super.onDraw(canvas);
        
		canvas.save();
		canvas.translate(mPosX, mPosY);

		//canvas.scale(mScaleFactor, mScaleFactor);
		

		mIcon.draw(canvas);
		canvas.restore();

		// if (canvas!=null){
		// 	canvas.drawColor(Color.BLACK);
		// 	if (m_bitmap!=null){
		// 		// setImageBitmap(m_bitmap);
		// 		// setScaleType(ImageView.ScaleType.CENTER_INSIDE);
		// 		Rect src = new Rect(0,0,m_bitmap.getWidth(),m_bitmap.getHeight());
		// 		float imgw=m_bitmap.getWidth();
		// 		float imgh=m_bitmap.getHeight();
		// 		float w=getWidth();
		// 		float h=getHeight();
		// 		float xscale=w/imgw;float yscale=h/imgh;
		// 		float scale=(xscale<=yscale)?xscale:yscale;
		// 		long xloc=Math.round((w-imgw*scale)*.5);
		// 		long yloc=Math.round((h-imgh*scale)*.5);
		// 		Rect dst = new Rect((int)xloc,(int)yloc,(int)(w-xloc),(int)(h-yloc));
		// 		canvas.drawBitmap(m_bitmap,src,dst,null);
		// 	}
		// }
	}

	// delegate the event to the gesture detector
	// @Override
	// public boolean onTouchEvent(MotionEvent e) {
	// 	return gestureDetector.onTouchEvent(e);
	// }

	@Override
	public boolean onTouchEvent(MotionEvent ev) {
		// Let the ScaleGestureDetector inspect all events.
		mScaleDetector.onTouchEvent(ev);
    
		final int action = ev.getAction();
		switch (action & MotionEvent.ACTION_MASK) {
		case MotionEvent.ACTION_DOWN: 
			{
				final float x = ev.getX();
				final float y = ev.getY();
        
				mLastTouchX = x;
				mLastTouchY = y;
				mActivePointerId = ev.getPointerId(0);
				break;
			}

		case MotionEvent.ACTION_MOVE: 
			{
				final int pointerIndex = ev.findPointerIndex(mActivePointerId);
				final float x = ev.getX(pointerIndex);
				final float y = ev.getY(pointerIndex);

				// Only move if the ScaleGestureDetector isn't processing a gesture.
				if (!mScaleDetector.isInProgress()) {
					final float dx = x - mLastTouchX;
					final float dy = y - mLastTouchY;

					mPosX += dx;
					mPosY += dy;

					invalidate();
				}

				mLastTouchX = x;
				mLastTouchY = y;

				break;
			}
        
		case MotionEvent.ACTION_UP: 
			{
				mActivePointerId = INVALID_POINTER_ID;
				break;
			}
        
		case MotionEvent.ACTION_CANCEL: 
			{
				mActivePointerId = INVALID_POINTER_ID;
				break;
			}
    
		case MotionEvent.ACTION_POINTER_UP: 
			{
				final int pointerIndex = (ev.getAction() & MotionEvent.ACTION_POINTER_INDEX_MASK) 
					>> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
				final int pointerId = ev.getPointerId(pointerIndex);
				if (pointerId == mActivePointerId) {
					// This was our active pointer going up. Choose a new
					// active pointer and adjust accordingly.
					final int newPointerIndex = pointerIndex == 0 ? 1 : 0;
					mLastTouchX = ev.getX(newPointerIndex);
					mLastTouchY = ev.getY(newPointerIndex);
					mActivePointerId = ev.getPointerId(newPointerIndex);
				}
				break;
			}
		}
    
		return true;
	}

	public boolean onDoubleTap(MotionEvent e) {
		float x = e.getX();
		float y = e.getY();
		Log.d("EditorImageView","Double Tapped at: (" + x + "," + y + ")");
		Animation anim = AnimationUtils.loadAnimation(getContext(), R.anim.scale_up);
		startAnimation(anim);
		return true;
	}
	
	@Override 
	public void setImageDrawable(Drawable drawable) {
    // Constrain to given size but keep aspect ratio
    int width = drawable.getIntrinsicWidth();
    int height = drawable.getIntrinsicHeight();
    mLastTouchX = mPosX = 0;
    mLastTouchY = mPosY = 0;

    int borderWidth = (int) borderPaint.getStrokeWidth();
    mScaleFactor = Math.min(((float) getLayoutParams().width - borderWidth)
														/ width, ((float) getLayoutParams().height - borderWidth)
														/ height);
    pivotPointX = (((float)getLayoutParams().width - borderWidth)-(int)(width *mScaleFactor))*.5f;
    pivotPointY = (((float)getLayoutParams().height- borderWidth)-(int)(height*mScaleFactor))*.5f;
    super.setImageDrawable(drawable);
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
			holder.onDoubleTap(e);
			return true;
		}
	}

	private class ScaleListener extends ScaleGestureDetector.SimpleOnScaleGestureListener 
	{
    @Override
		public boolean onScale(ScaleGestureDetector detector) {
			mScaleFactor *= detector.getScaleFactor();
			mScaleFactor = Math.max(0.1f, Math.min(mScaleFactor, 5.0f));
			invalidate();
			return true;
    }
	}

}

