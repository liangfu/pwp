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

import com.liangfu.pwptracker.R;

// Sample0Base
public class CvTracker extends Activity 
{
  private static final String TAG            = "CompVis::EntryActivity";

	private static final int SELECT_PICTURE = 1;

	private String selectedImagePath;
	
  // public static final int     VIEW_MODE_RGBA = 0;
  // public static final int     VIEW_MODE_GRAY = 1;

  // private MenuItem            mItemPreviewRGBA;
  // private MenuItem            mItemPreviewGray;
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

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (resultCode == RESULT_OK) {
			if (requestCode == SELECT_PICTURE) {
				Uri selectedImageUri = data.getData();
				selectedImagePath = getPath(selectedImageUri);
				Intent intent = new Intent(this, EditorActivity.class);
				intent.putExtra("selectedImagePath",selectedImagePath);
				startActivity(intent);
			}
		}
	}

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
