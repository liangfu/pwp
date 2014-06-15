package com.liangfu.pwptracker;

import android.content.Context;
// import android.view.SurfaceHolder;
import android.widget.ImageView;
import java.util.ArrayList;
import android.util.AttributeSet;
import android.graphics.Color;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.Matrix;
import android.graphics.RectF;
import android.graphics.PointF;
import android.view.animation.Animation;
import android.view.ScaleGestureDetector;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.widget.TextView;
import android.view.View;
import android.util.Log;
import android.util.FloatMath;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.view.animation.Transformation;
import android.graphics.drawable.Drawable;
import android.graphics.Paint;
import android.content.res.Resources;

//import com.liangfu.widgets.GestureImageView;

import com.liangfu.pwptracker.R;

public class EditorImageView extends ImageView 
//implements SurfaceHolder.Callback 
{
	public static final String TAG="EditorImageView";

	private ArrayList<Bitmap> mLayers;

	private Bitmap mBitmap=null;
	private String m_imagePath="";

	// private GestureDetector gestureDetector;

	// private Drawable mIcon=null;
	// private float mPosX=0;
	// private float mPosY=0;
    
	// private float mLastTouchX=0;
	// private float mLastTouchY=0;

	// private static final int INVALID_POINTER_ID = -1;
	// private int mActivePointerId = INVALID_POINTER_ID;

	// private ScaleGestureDetector mScaleDetector;
	// private float mScaleFactor = 1.f;

	// private Paint borderPaint = null;
	// private Paint backgroundPaint = null;

	// private float pivotPointX = 0f;
	// private float pivotPointY = 0f;

	private Matrix mMatrix = new Matrix();
	private Matrix mSavedMatrix = new Matrix();

	private int mMode = NONE;
	private static final int NONE = 0;
	private static final int DRAG = 1;
	private static final int ZOOM = 2;
	private static final int DRAW = 3;

	private PointF mStartPoint = new PointF();
	private PointF mMidPoint = new PointF();
	private float mOldDistance;

	private boolean mFitFlag = false;


	public EditorImageView(Context context) {
		super(context);
		init(context);
	}
	public EditorImageView(Context context, AttributeSet attrs) {
		super(context, attrs);
		init(context);
	}
	public EditorImageView(Context context, AttributeSet attrs, int style) {
		super(context, attrs, style);
		init(context);
	}

	private void init(Context context)
	{
		setClickable(true);

		setScaleType(ImageView.ScaleType.MATRIX);

		setOnTouchListener(new EditorOnTouchListener());
		
		// gestureDetector = new GestureDetector(context, new GestureListener(this));
    // mScaleDetector = new ScaleGestureDetector(context, new ScaleListener());

		// borderPaint = new Paint();
    // borderPaint.setARGB(255, 255, 128, 0);
    // borderPaint.setStyle(Paint.Style.STROKE);
    // borderPaint.setStrokeWidth(4);

    // backgroundPaint = new Paint();
    // backgroundPaint.setARGB(32, 255, 255, 255);
    // backgroundPaint.setStyle(Paint.Style.FILL);

		mLayers = new ArrayList<Bitmap>();
	}

	public void setImagePath(String imagePath)
	{
		m_imagePath=imagePath;
		mBitmap=BitmapFactory.decodeFile(imagePath);
		//mIcon = context.getResources().getDrawable(R.drawable.icon);
		//mIcon = Drawable.createFromPath(imagePath);
		mLayers.add(mBitmap);
		// mIcon.setBounds(0, 0, mIcon.getIntrinsicWidth(), mIcon.getIntrinsicHeight());
		// float w=mBitmap.getWidth() *getResources().getDisplayMetrics().density;
		// float h=mBitmap.getHeight()*getResources().getDisplayMetrics().density;
		//mIcon.setBounds(0, 0, Math.round(w), Math.round(h));

		mFitFlag=true;
	}

	private void scaleToFit()
	{
		Matrix m=getImageMatrix();
		int imageWidth=mBitmap.getWidth();
		int imageHeight=mBitmap.getHeight();
		RectF drawableRect = new RectF(0, 0, imageWidth, imageHeight);
		RectF viewRect = new RectF(0, 0, getWidth(), getHeight());
		m.setRectToRect(drawableRect, viewRect, Matrix.ScaleToFit.CENTER);
		mMatrix.set(m);
		setImageMatrix(m);
	}

	private float calcDistance(MotionEvent event) {
		float x = event.getX(0) - event.getX(1);
		float y = event.getY(0) - event.getY(1);
		return FloatMath.sqrt(x * x + y * y);
	}

	private void calcMidPoint(PointF midPoint, MotionEvent event) {
		float x = event.getX(0) + event.getX(1);
		float y = event.getY(0) + event.getY(1);
		midPoint.set(x / 2, y / 2);
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

		if (mFitFlag){scaleToFit();mFitFlag=false;}
        
		Matrix matrix = getImageMatrix();
		if (matrix != null) {
			int numLayers = mLayers.size();
			for (int i = 0; i < numLayers; i++) {
				Bitmap b = mLayers.get(i);
				canvas.drawBitmap(b, matrix, null);
			}
		}

		// canvas.save();
		// canvas.translate(mPosX, mPosY);
		// canvas.scale(mScaleFactor, mScaleFactor);
		// mIcon.draw(canvas);
		// canvas.restore();

		// if (canvas!=null){
		// 	canvas.drawColor(Color.BLACK);
		// 	if (mBitmap!=null){
		// 		// setImageBitmap(mBitmap);
		// 		// setScaleType(ImageView.ScaleType.CENTER_INSIDE);
		// 		Rect src = new Rect(0,0,mBitmap.getWidth(),mBitmap.getHeight());
		// 		float imgw=mBitmap.getWidth();
		// 		float imgh=mBitmap.getHeight();
		// 		float w=getWidth();
		// 		float h=getHeight();
		// 		float xscale=w/imgw;float yscale=h/imgh;
		// 		float scale=(xscale<=yscale)?xscale:yscale;
		// 		long xloc=Math.round((w-imgw*scale)*.5);
		// 		long yloc=Math.round((h-imgh*scale)*.5);
		// 		Rect dst = new Rect((int)xloc,(int)yloc,(int)(w-xloc),(int)(h-yloc));
		// 		canvas.drawBitmap(mBitmap,src,dst,null);
		// 	}
		// }
	}

	// delegate the event to the gesture detector
	// @Override
	// public boolean onTouchEvent(MotionEvent e) {
	// 	return gestureDetector.onTouchEvent(e);
	// }

	/*
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

		Log.d(TAG,"setImageDrawable:0");
		if (borderPaint==null){return;}
		Log.d(TAG,"setImageDrawable:1");

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
	*/

	/*
	public class Layer 
	{
		private Drawable drawable;
		private Animation animation;
		private Transformation transformation;
		private Matrix matrix;
		private boolean valid;

		private Layer(Drawable d, Matrix m) {
			drawable = d;
			transformation = new Transformation();
			matrix = m;
			valid = true;
			Rect bounds = d.getBounds();
			if (bounds.isEmpty()) {
				if (d instanceof BitmapDrawable) {
					int right = d.getIntrinsicWidth();
					int bottom = d.getIntrinsicHeight();
					d.setBounds(0, 0, right, bottom);
				} else {
					String detailMessage = "drawable bounds are empty, use d.setBounds()";
					throw new RuntimeException(detailMessage);
				}
			}
			d.setCallback(LayeredImageView.this);
		}

		public void startLayerAnimation(Animation a) throws RuntimeException {
			if (!valid) {
				String detailMessage = "this layer has already been removed";
				throw new RuntimeException(detailMessage);
			}
			transformation.clear();
			animation = a;
			if (a != null) {
				a.start();
			}
			invalidate();
		}

		public void stopLayerAnimation(int idx) throws RuntimeException {
			if (!valid) {
				String detailMessage = "this layer has already been removed";
				throw new RuntimeException(detailMessage);
			}
			if (animation != null) {
				animation = null;
				invalidate();
			}
		}
	}

	private class LayeredImageViewResources extends Resources 
	{
		public LayeredImageViewResources() {
			super(getContext().getAssets(), new DisplayMetrics(), null);
		}

		@Override
			public Drawable getDrawable(int id) throws NotFoundException {
			Drawable d = super.getDrawable(id);
			if (d instanceof BitmapDrawable) {
				BitmapDrawable bd = (BitmapDrawable) d;
				bd.getBitmap().setDensity(DisplayMetrics.DENSITY_DEFAULT);
				bd.setTargetDensity(DisplayMetrics.DENSITY_DEFAULT);
			}
			return d;
		}
	}
	*/

	private class EditorOnTouchListener implements View.OnTouchListener
	{
		public boolean onTouch(View v, MotionEvent event) {
			switch (event.getAction() & MotionEvent.ACTION_MASK) {

			case MotionEvent.ACTION_DOWN:
				mMode = DRAG;
				mStartPoint.set(event.getX(), event.getY());
				mSavedMatrix.set(mMatrix);
				break;

			case MotionEvent.ACTION_MOVE:
				if(mMode == DRAG) {
					mMatrix.set(mSavedMatrix);
					float x = event.getX() - mStartPoint.x;
					float y = event.getY() - mStartPoint.y;
					mMatrix.postTranslate(x, y);
				} else if (mMode == ZOOM) {
					float newDist = calcDistance(event);
					float scale = newDist / mOldDistance;
					mMatrix.set(mSavedMatrix);
					mMatrix.postScale(scale, scale, mMidPoint.x, mMidPoint.y);
				}
				break;

			case MotionEvent.ACTION_UP:
				mMode = NONE;
				break;

			case MotionEvent.ACTION_POINTER_DOWN:
				mMode = ZOOM;
				mOldDistance = calcDistance(event);
				calcMidPoint(mMidPoint, event);
				break;

			case MotionEvent.ACTION_POINTER_UP:
				mMode = NONE;
				break;
			default:
				break;
			}

			setImageMatrix(mMatrix);
			return true;
		}
	}
}

