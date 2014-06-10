package com.liangfu.pwptracker;

import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.net.Uri;
import android.view.View.OnClickListener;
import android.view.View;
import android.widget.Button;
import android.provider.MediaStore;
import android.database.Cursor;
import android.widget.TextView;
import android.view.MotionEvent;
import android.util.Log;

import com.liangfu.pwptracker.R;

public class EditorActivity extends Activity 
{
	private String selectedImagePath;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.editor);

		Bundle extras = getIntent().getExtras();
		if (extras != null) {
			String path = extras.getString("selectedImagePath");
			TextView logger=((TextView)findViewById(R.id.editorLog));
			logger.setText(path);
			setImagePath(path);
		}

	}

	public void setImagePath(String imagePath)
	{
		selectedImagePath=imagePath;
		EditorImageView v=((EditorImageView)findViewById(R.id.editorImageView));
		v.setImagePath(imagePath);
	}

	// @Override
	// public boolean onTouchEvent(MotionEvent e) {
	// 	float x = e.getX();
	// 	float y = e.getY();
	// 	TextView logger=((TextView)findViewById(R.id.editorLog));
	// 	logger.setText("Tapped at: (" + x + "," + y + ")");
	// 	return true;
	// }

}

