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

  private static final int CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE = 100;
  private static final int CAPTURE_VIDEO_ACTIVITY_REQUEST_CODE = 200;

  @Override
  protected void onActivityResult(int requestCode, int resultCode, Intent data) {
    if (requestCode == CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE) {
      if (resultCode == RESULT_OK) {
        // Image captured and saved to fileUri specified in the Intent
        Toast.makeText(this, "Image saved to:\n" +
                       data.getData(), Toast.LENGTH_LONG).show();
      } else if (resultCode == RESULT_CANCELED) {
        // User cancelled the image capture
      } else {
        // Image capture failed, advise user
      }
    }

    if (requestCode == CAPTURE_VIDEO_ACTIVITY_REQUEST_CODE) {
      if (resultCode == RESULT_OK) {
        // Video captured and saved to fileUri specified in the Intent
        Toast.makeText(this, "Video saved to:\n" +
                       data.getData(), Toast.LENGTH_LONG).show();
      } else if (resultCode == RESULT_CANCELED) {
        // User cancelled the video capture
      } else {
        // Video capture failed, advise user
      }
    }
  }
  
}

