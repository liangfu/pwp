package com.liangfu.pwptracker;

import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.net.Uri;
import android.view.View.OnClickListener;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.provider.MediaStore;
import android.database.Cursor;

import com.liangfu.pwptracker.R;

public class CaptureActivity extends Activity 
{
	// this is the action code we use in our intent, 
	// this way we know we're looking at the response from our own action
	// private static final int SELECT_PICTURE = 1;

	// private String selectedImagePath;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.capture);

		// ((Button) findViewById(R.id.cameraButton)).setOnClickListener(new OnClickListener() {
		// 		public void onClick(View arg0) {
		// 			Intent intent = new Intent();
		// 			intent.setType("image/*");
		// 			intent.setAction(Intent.ACTION_GET_CONTENT);
		// 			startActivityForResult(Intent.createChooser(intent,
		// 																									"Select Picture"), SELECT_PICTURE);
		// 		}
		// 	});
	}
  
}

