package com.liangfu.pwptracker;

import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.net.Uri;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.View;
import android.widget.Button;
import android.provider.MediaStore;
import android.database.Cursor;
import android.widget.TextView;
import android.view.MotionEvent;
import android.util.Log;
import android.graphics.BitmapFactory;
import android.util.FloatMath;
import android.graphics.PointF;

import com.liangfu.widgets.GestureImageView;

import com.liangfu.pwptracker.R;

public class EditorActivity extends Activity 
{
	private static final String TAG="EditorActivity";
	private String selectedImagePath;

	private Button eraserButton=null;
	private Button regionButton=null;
	private EditorImageView editorImageView=null;

	private static final int NONE = 0;
	
	private int mMode = NONE;
	private static final int DRAG = 1;
	private static final int ZOOM = 2;
	private static final int DRAW = 3;

	private int mPressed = NONE;
	private static final int ERASER = 1;
	private static final int REGION = 2;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.editor);

		eraserButton=((Button)findViewById(R.id.eraserButton));
		regionButton=((Button)findViewById(R.id.regionButton));
		editorImageView=((EditorImageView)findViewById(R.id.editorImageView));

		Bundle extras = getIntent().getExtras();
		if (extras != null) {
			String path = extras.getString("selectedImagePath");
			TextView logger=((TextView)findViewById(R.id.editorLog));
			logger.setText(path);
			setImagePath(path);
		}

		eraserButton.setOnTouchListener(new EraserButtonOnTouchListener());
		regionButton.setOnTouchListener(new RegionButtonOnTouchListener());
		editorImageView.setOnTouchListener(new EditorImageViewOnTouchListener());
		
	}

	public void setImagePath(String imagePath)
	{
		selectedImagePath=imagePath;
		editorImageView.setImagePath(imagePath);

		// view=((GestureImageView)findViewById(R.id.gestureImageView));
		// view.setImageBitmap(BitmapFactory.decodeFile(imagePath));
	}

	// @Override
	// public boolean onTouchEvent(MotionEvent e) {
	// 	float x = e.getX();
	// 	float y = e.getY();
	// 	TextView logger=((TextView)findViewById(R.id.editorLog));
	// 	logger.setText("Tapped at: (" + x + "," + y + ")");
	// 	return true;
	// }

	private class EraserButtonOnTouchListener implements View.OnTouchListener
	{
		@Override
			public boolean onTouch(View v, MotionEvent event){
			// show interest in events resulting from ACTION_DOWN
			if(event.getAction()==MotionEvent.ACTION_DOWN) { return true; }
			// don't handle event unless its ACTION_UP so "doSomething()" only runs once.
			if(event.getAction()!=MotionEvent.ACTION_UP) { return false; }
			boolean pressed=eraserButton.isPressed();
			if (!pressed){
				eraserButton.setPressed(true);
				mPressed=ERASER;
			}else{
				eraserButton.setPressed(false);
				mPressed=NONE;
			}
			Log.d(TAG,String.format("status %d",mPressed));
			return true;
		}
	}

	private class RegionButtonOnTouchListener implements View.OnTouchListener
	{
		@Override
			public boolean onTouch(View v, MotionEvent event){
			// show interest in events resulting from ACTION_DOWN
			if(event.getAction()==MotionEvent.ACTION_DOWN) { return true; }
			// don't handle event unless its ACTION_UP so "doSomething()" only runs once.
			if(event.getAction()!=MotionEvent.ACTION_UP) { return false; }
			boolean pressed=regionButton.isPressed();
			if (!pressed){
				regionButton.setPressed(true);
				mPressed=REGION;
			}else{
				regionButton.setPressed(false);
				mPressed=NONE;
			}
			Log.d(TAG,String.format("status %d",mPressed));
			return true;
		}
	}

	private class EditorImageViewOnTouchListener implements View.OnTouchListener
	{
		private PointF mStartPoint = new PointF();
		private PointF mMidPoint = new PointF();

		private float mOldDistance;
		
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
		
		public boolean onTouch(View v, MotionEvent event) {
			Log.d(TAG,String.format("status %d",mPressed));
			switch (event.getAction() & MotionEvent.ACTION_MASK) {

			case MotionEvent.ACTION_DOWN:
				{
					if (mPressed==NONE) {
						mMode = DRAG;
						mStartPoint.set(event.getX(), event.getY());
						editorImageView.mSavedMatrix.set(editorImageView.mMatrix);
					}else
					{
						mMode = DRAW;
					}
				}
				break;

			case MotionEvent.ACTION_MOVE:
				if(mMode == DRAG) {
					editorImageView.mMatrix.set(editorImageView.mSavedMatrix);
					float x = event.getX() - mStartPoint.x;
					float y = event.getY() - mStartPoint.y;
					editorImageView.mMatrix.postTranslate(x, y);
				} else if (mMode == ZOOM) {
					float newDist = calcDistance(event);
					float scale = newDist / mOldDistance;
					editorImageView.mMatrix.set(editorImageView.mSavedMatrix);
					editorImageView.mMatrix.postScale(scale, scale, mMidPoint.x, mMidPoint.y);
				} else if (mMode == DRAW) {
					editorImageView.paintMask(event.getX(),event.getY());
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

			editorImageView.setImageMatrix(editorImageView.mMatrix);
			return true;
		}
	}
}

