package com.liangfu.pwptracker;

import java.util.ArrayList;
import android.content.Context;
import android.widget.ImageView;
import android.util.AttributeSet;
import android.graphics.Color;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.Matrix;
import android.graphics.RectF;
import android.view.animation.Animation;
import android.view.ScaleGestureDetector;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.widget.TextView;
import android.view.View;
import android.util.Log;
import android.util.FloatMath;
import android.graphics.PointF;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.view.animation.Transformation;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.Paint;
import android.content.res.Resources;
import android.graphics.drawable.LayerDrawable;
import android.graphics.drawable.ShapeDrawable;

import com.liangfu.pwptracker.R;

public class EditorImageView extends ImageView 
//implements SurfaceHolder.Callback 
{
	public static final String TAG="EditorImageView";

	private ArrayList<Bitmap> mLayers;

	private LayerDrawable mLayerDrawable=null;
	// private Drawable mMaskLayer=null;
	// private Drawable mImageLayer=null;
	// private Drawable [] mLayersHolder = new Drawable[2];

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

	public Matrix mMatrix = new Matrix();
	public Matrix mSavedMatrix = new Matrix();

	public boolean mFitFlag = false;

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

		mLayers = new ArrayList<Bitmap>();

		BitmapDrawable imageLayer = new BitmapDrawable();
    imageLayer.getPaint().setColor(Color.WHITE);
		BitmapDrawable maskLayer = new BitmapDrawable();
		maskLayer.getPaint().setColor(Color.WHITE);
		Drawable [] layers={maskLayer,imageLayer};
		mLayerDrawable = new LayerDrawable(layers);
		mLayerDrawable.setLayerInset(0,0,0,0,0);
		mLayerDrawable.setLayerInset(1,10,0,10,10);
	}

	public void setImagePath(String imagePath)
	{
		m_imagePath=imagePath;
		
		mBitmap=BitmapFactory.decodeFile(imagePath).copy(Bitmap.Config.ARGB_8888,true);
		mLayers.add(mBitmap);

		// mLayerDrawable.setDrawableByLayerId(0,Drawable.createFromPath(imagePath));
		// mLayerDrawable.setDrawableByLayerId(1,Drawable.createFromPath(imagePath));
		mLayerDrawable.setDrawableByLayerId(mLayerDrawable.getId(0),
																				new BitmapDrawable(getResources(),mBitmap));
		mLayerDrawable.setDrawableByLayerId(mLayerDrawable.getId(1),
																				new BitmapDrawable(getResources(),mBitmap));
		// ((BitmapDrawable)mLayerDrawable.getDrawable(0)).setBitmap(mBitmap);
		// ((BitmapDrawable)mLayerDrawable.getDrawable(1)).setBitmap(mBitmap);
		
		mFitFlag=true;
	}

	public static Bitmap drawableToBitmap (Drawable drawable) {
    if (drawable instanceof BitmapDrawable) {
			return ((BitmapDrawable)drawable).getBitmap();
    }

    Bitmap bitmap = Bitmap.createBitmap(drawable.getIntrinsicWidth(), 
																				drawable.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);
    Canvas canvas = new Canvas(bitmap); 
    drawable.setBounds(0, 0, canvas.getWidth(), canvas.getHeight());
    drawable.draw(canvas);

    return bitmap;
	}

	public void paintMask(float x, float y)
	{
		//Bitmap xx=((BitmapDrawable)mLayerDrawable.getDrawable(0)).getBitmap();
		// Bitmap xx=drawableToBitmap(mLayerDrawable.getDrawable(0));
		// if (xx==null){Log.d(TAG,String.format("xx is null"));}
		// Bitmap bitmap = mBitmap.copy(Bitmap.Config.ARGB_8888,true);
		//((BitmapDrawable)mLayerDrawable.getDrawable(0)).getBitmap();
		// ....
		//bitmap.setPixel((int)x,(int)y,Color.RED);
		// Canvas canvas=new Canvas(bitmap);
		Matrix inverse=new Matrix(mMatrix);
		if (mMatrix.invert(inverse)){Log.d(TAG,"inverted");}else{Log.d(TAG,"not inverted");}
		
		float [] pts={x,y};
		inverse.mapPoints(pts);
		x=pts[0];y=pts[1];

		Paint paint = new Paint();
		paint.setColor(Color.RED);
		paint.setStrokeWidth(3);
		Bitmap b = mLayers.get(0);
		Canvas canvas2=new Canvas(b);
		canvas2.drawRect((int)x, (int)y, (int)(x+5), (int)(y+5), paint);
		mLayers.set(0,b);
		invalidate();
		//canvas2.drawRect(30, 30, 80, 80, paint);
		//canvas.drawLine(1,1,100,100,paint);
		// mBitmap=bitmap.copy(Bitmap.Config.ARGB_8888,true);
		// mLayerDrawable.setDrawableByLayerId(mLayerDrawable.getId(0),
		// 																		new BitmapDrawable(getResources(),bitmap));
		// mLayerDrawable.setDrawableByLayerId(mLayerDrawable.getId(1),
		// 																		new BitmapDrawable(getResources(),bitmap));
		Log.d(TAG,String.format("paintMask (%d,%d)",(int)x,(int)y));
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

		Paint paint = new Paint();
		paint.setColor(Color.RED);
		paint.setStrokeWidth(3);

		Matrix matrix = getImageMatrix();
		
		if (matrix != null) {
			int numLayers = mLayers.size();
			for (int i = 0; i < numLayers; i++) {
				Bitmap b = mLayers.get(i);
				// Canvas canvas2=new Canvas(b);
				// canvas2.drawRect(30, 30, 80, 80, paint);
				canvas.drawBitmap(b, matrix, null);
				// draw(canvas,mLayerDrawable,matrix,255);
				// setImageDrawable(mLayerDrawable);
			}
		}
	}

	// private void draw(Canvas canvas, Drawable drawable, Matrix matrix, int alpha) {
	// 	canvas.save(Canvas.MATRIX_SAVE_FLAG);
	// 	canvas.concat(matrix);
	// 	drawable.setAlpha(alpha);
	// 	drawable.draw(canvas);
	// 	canvas.restore();
	// }

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

}

