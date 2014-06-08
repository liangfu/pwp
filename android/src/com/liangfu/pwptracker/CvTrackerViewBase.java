package com.liangfu.pwptracker;

import java.io.IOException;
import java.util.List;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.hardware.Camera;
import android.hardware.Camera.PreviewCallback;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

// public abstract class SampleViewBase
public abstract class CvTrackerViewBase
    extends SurfaceView implements SurfaceHolder.Callback, Runnable
{
  private static final String TAG = "Sample::SurfaceView";

  private Camera              mCamera;
  private SurfaceHolder       mHolder;
  private int                 mFrameWidth;
  private int                 mFrameHeight;
  private byte[]              mFrame;
  private boolean             mThreadRun;

  public CvTrackerViewBase(Context context) {
    super(context);
    mHolder = getHolder();
    mHolder.addCallback(this);
    Log.i(TAG, "Instantiated new " + this.getClass());
  }

  public int getFrameWidth() {
    return mFrameWidth;
  }

  public int getFrameHeight() {
    return mFrameHeight;
  }

  public void surfaceChanged(SurfaceHolder _holder, int format,
                             int width, int height)
  {
    Log.i(TAG, "surfaceCreated");
    if (mCamera != null) {
      Camera.Parameters params = mCamera.getParameters();
      List<Camera.Size> sizes = params.getSupportedPreviewSizes();
      mFrameWidth = width;
      mFrameHeight = height;
      
      // selecting optimal camera preview size
      {
        double minDiff = Double.MAX_VALUE;
        for (Camera.Size size : sizes) {
          if (Math.abs(size.height - height) < minDiff) {
            mFrameWidth = size.width;
            mFrameHeight = size.height;
            minDiff = Math.abs(size.height - height);
          }
        }
      }

      params.setPreviewSize(getFrameWidth(), getFrameHeight());
      mCamera.setParameters(params);
      try {
        mCamera.setPreviewDisplay(null);
      } catch (IOException e) {
        Log.e(TAG, "mCamera.setPreviewDisplay fails: " + e);
      }
      mCamera.startPreview();
    }
  }

  public void surfaceCreated(SurfaceHolder holder)
  {
    Log.i(TAG, "surfaceCreated");
    mCamera = Camera.open();
    mCamera.setDisplayOrientation(90);
    mCamera.setPreviewCallback(
        new PreviewCallback()
        {
          public void onPreviewFrame(byte[] data, Camera camera) {
            synchronized (CvTrackerViewBase.this) {
              mFrame = data;
              CvTrackerViewBase.this.notify();
            }
          }
        });
    (new Thread(this)).start();
  }

  public void surfaceDestroyed(SurfaceHolder holder)
  {
    Log.i(TAG, "surfaceDestroyed");
    mThreadRun = false;
    if (mCamera != null) {
      synchronized (this) {
        mCamera.stopPreview();
        mCamera.setPreviewCallback(null);
        mCamera.release();
        mCamera = null;
      }
    }
  }

  protected abstract int[] processFrame(byte[] data, int width, int height);

  public void run()
  {
    mThreadRun = true;
    Log.i(TAG, "Starting processing thread");
    while (mThreadRun)
    {
      Bitmap bmp = null;
      synchronized (this)
      {
        try {
          this.wait();
          bmp = Bitmap.createBitmap(mFrameWidth, mFrameHeight,
                                    Bitmap.Config.ARGB_8888);
          int[] rgba = processFrame(mFrame, mFrameWidth, mFrameHeight);
          bmp.setPixels(rgba, 0/* offset */, mFrameWidth /* stride */,
                        0, 0, mFrameWidth, mFrameHeight);
        } catch (InterruptedException e) {
          e.printStackTrace();
        }
      }
      if (bmp != null)
      {
        Canvas canvas = mHolder.lockCanvas();
        if (canvas != null) {
          canvas.drawBitmap(bmp,
                            (canvas.getWidth() - getFrameWidth()) / 2,
                            (canvas.getHeight() - getFrameHeight()) / 2,
                            null);
          mHolder.unlockCanvasAndPost(canvas);
        }
        bmp.recycle();
      }
    } // while loop
  }

}