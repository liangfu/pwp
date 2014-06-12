package com.liangfu.pwptracker;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.content.pm.ActivityInfo;
import android.content.Intent;;
import android.provider.MediaStore;
import android.database.Cursor;
import android.net.Uri;
import android.widget.Toast;
import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;
import android.os.Environment;

import com.liangfu.pwptracker.R;

// Sample0Base
public class CvTracker extends Activity 
{
  private static final String TAG            = "CompVis::EntryActivity";

	private static final int SELECT_PICTURE = 1;
  private static final int REQUEST_IMAGE_CAPTURE = 1;

  public static final int MEDIA_TYPE_IMAGE = 1;
  public static final int MEDIA_TYPE_VIDEO = 2;
  
  private static final int CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE = 100;
  private static final int CAPTURE_VIDEO_ACTIVITY_REQUEST_CODE = 200;
  private Uri fileUri;
  
	private String selectedImagePath;
	
  // public static final int     VIEW_MODE_RGBA = 0;
  // public static final int     VIEW_MODE_GRAY = 1;

	// private Button cameraButton  = (Button) findViewById(R.id.cameraButton);
	// private Button galleryButton = (Button) findViewById(R.id.galleryButton);

  // public static int           viewMode       = VIEW_MODE_RGBA;

  public CvTracker() {
    Log.i(TAG, "Instantiated new " + this.getClass());
  }

  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState) {
    Log.i(TAG, "onCreate");

		super.onCreate(savedInstanceState);
		
    requestWindowFeature(Window.FEATURE_NO_TITLE);
    getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                         WindowManager.LayoutParams.FLAG_FULLSCREEN);
    
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

		setContentView(R.layout.main);
    // setContentView(new CvTrackerView(this));

  }

	public void browsePicture(View v)
	{
		Intent intent = new Intent();
		intent.setType("image/*");
		intent.setAction(Intent.ACTION_GET_CONTENT);
		startActivityForResult(Intent.createChooser(intent, "Select Picture"), SELECT_PICTURE);
		// Intent intent = new Intent(this, BrowsePictureActivity.class);
		// startActivity(intent);
	}

  public void dispatchTakePictureIntent(View v) {
		Log.d(TAG,"=======================================================");
    Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
    // if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
    //   startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE);
    // }
		Log.d(TAG,"1");
    fileUri = getOutputMediaFileUri(MEDIA_TYPE_IMAGE);
		Log.d(TAG,"2");
    intent.putExtra(MediaStore.EXTRA_OUTPUT, fileUri);
		Log.d(TAG,"3");
    startActivityForResult(intent, CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE);
		Log.d(TAG,"4");
		Log.d(TAG,"=======================================================");
  }

	public void onActivityResult(int requestCode, int resultCode, Intent data)
  {
		Log.d(TAG,"-------------------------------------------------------");
		if (resultCode == RESULT_OK) {
			if (requestCode == SELECT_PICTURE) {
				Uri selectedImageUri = data.getData();
				selectedImagePath = getPath(selectedImageUri);
				Intent intent = new Intent(this, EditorActivity.class);
				intent.putExtra("selectedImagePath",selectedImagePath);
				startActivity(intent);
			}
		}

		Log.d(TAG,"5");
    if (requestCode == CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE) {
		Log.d(TAG,"6");
      if (resultCode == RESULT_OK) {
		Log.d(TAG,"7");
        // Image captured and saved to fileUri specified in the Intent
        // Toast.makeText(this, "Image saved to:\n" +
        //                data.getData(), Toast.LENGTH_LONG).show();
        Toast.makeText(this, "Image saved to:\n" +
                       fileUri, Toast.LENGTH_LONG).show();
		Log.d(TAG,"8");
		    Uri selectedImageUri = fileUri;//data.getData();
		Log.d(TAG,"9");
				selectedImagePath = getPath(selectedImageUri);
		Log.d(TAG,"10");
				Intent intent = new Intent(this, EditorActivity.class);
		Log.d(TAG,"11");
				intent.putExtra("selectedImagePath",selectedImagePath);
		Log.d(TAG,"12");
				startActivity(intent);
		Log.d(TAG,"13");
      } else if (resultCode == RESULT_CANCELED) {
        // User cancelled the image capture
      } else {
        // Image capture failed, advise user
      }
    }
	}

  private static Uri getOutputMediaFileUri(int type){
    return Uri.fromFile(getOutputMediaFile(type));
  }

  private static File getOutputMediaFile(int type){
    // To be safe, you should check that the SDCard is mounted
    // using Environment.getExternalStorageState() before doing this.

    File mediaStorageDir = new File(Environment.getExternalStoragePublicDirectory(
        Environment.DIRECTORY_PICTURES), "MyCameraApp");
    // This location works best if you want the created images to be shared
    // between applications and persist after your app has been uninstalled.

    // Create the storage directory if it does not exist
    if (! mediaStorageDir.exists()){
      if (! mediaStorageDir.mkdirs()){
        Log.d("MyCameraApp", "failed to create directory");
        return null;
      }
    }

    // Create a media file name
    String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
    File mediaFile;
    if (type == MEDIA_TYPE_IMAGE){
      mediaFile = new File(mediaStorageDir.getPath() + File.separator +
                           "IMG_"+ timeStamp + ".jpg");
    } else if(type == MEDIA_TYPE_VIDEO) {
      mediaFile = new File(mediaStorageDir.getPath() + File.separator +
                           "VID_"+ timeStamp + ".mp4");
    } else {
      return null;
    }

    return mediaFile;
  }
  
  // private MenuItem            mItemPreviewRGBA;
  // private MenuItem            mItemPreviewGray;
  // @Override
  // public boolean onCreateOptionsMenu(Menu menu) {
  //   Log.i(TAG, "onCreateOptionsMenu");
  //   mItemPreviewRGBA = menu.add("Preview RGBA");
  //   mItemPreviewGray = menu.add("Preview GRAY");
  //   return true;
  // }
  // @Override
  // public boolean onOptionsItemSelected(MenuItem item) {
  //   Log.i(TAG, "Menu Item selected " + item);
  //   if (item == mItemPreviewRGBA){
  //     viewMode = VIEW_MODE_RGBA;
  //   }else if (item == mItemPreviewGray){
  //     viewMode = VIEW_MODE_GRAY;
  //   }
  //   return true;
  // }

	/**
	 * helper to retrieve the path of an image URI
	 */
	public String getPath(Uri uri) {
		// just some safety built in 
		if( uri == null ) {
			// TODO perform some logging or show user feedback
			return null;
		}
		// try to retrieve the image from the media store first
		// this will only work for images selected from gallery
		String[] projection = { MediaStore.Images.Media.DATA };
		Cursor cursor = managedQuery(uri, projection, null, null, null);
		if( cursor != null ){
                int column_index = cursor
									.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
                cursor.moveToFirst();
                return cursor.getString(column_index);
		}
		// this is our fallback here
		return uri.getPath();
	}

}
