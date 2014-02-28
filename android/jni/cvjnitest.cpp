/**
 * @file   cvjnitest.cpp
 * @author Liangfu Chen <liangfu.chen@cn.fix8.com>
 * @date   Thu Apr 18 09:43:44 2013
 * 
 * @brief  
 * 
 * 
 */

#include <string.h>
#include <jni.h>
#include <math.h>
#include "cxcore.h"

#define DEBUG 1

#if DEBUG
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_INFO,"cvext",x)
#else
#  define  D(...)  do {} while (0)
#endif

inline double round(double d)
{
  return floor(d + 0.5);
}

void launch(CvMat * img);

extern "C"
jintArray
Java_com_liangfu_pwptracker_CvTrackerView_nativeProcessFrame(
    JNIEnv * env, jobject thiz,
    jbyteArray jdata, jint width, jint height)
{
  int y,u,v,r,g,b,i,j;
  int frameSize = width*height;

  jbyte * data = env->GetByteArrayElements(jdata,0);
  jintArray outarr = env->NewIntArray(frameSize);
  int * rgba = new int[frameSize];
  
  CvMat * imgBGR = cvCreateMat(height, width, CV_8UC3);
  {
    uchar * imgptr = imgBGR->data.ptr;
    int step = imgBGR->step/sizeof(uchar);
    for (i = 0; i < height; i++)
    {
      for (j = 0; j < width; j++)
      {
        y = (0xff & ((int) data
                         [i * width + j]));
        u = (0xff & ((int) data
                         [frameSize + (i >> 1) * width + (j & ~1) + 0]));
        v = (0xff & ((int) data
                         [frameSize + (i >> 1) * width + (j & ~1) + 1]));
        y = y < 16 ? 16 : y;
        r = round(1.164f * (y - 16) + 1.596f * (v - 128));
        g = round(1.164f * (y - 16) - 0.813f * (v - 128) - 0.391f * (u - 128));
        b = round(1.164f * (y - 16) + 2.018f * (u - 128));

        r = r < 0 ? 0 : (r > 255 ? 255 : r);
        g = g < 0 ? 0 : (g > 255 ? 255 : g);
        b = b < 0 ? 0 : (b > 255 ? 255 : b);
        //rgba[i * width + j] = 0xff000000 + (b << 16) + (g << 8) + r;
        (imgptr+j*3)[0]=b;
        (imgptr+j*3)[1]=g;
        (imgptr+j*3)[2]=r;
      }
      imgptr+=step;
    }

    //cvLine(imgBGR, cvPoint(20,50), cvPoint(50,50), cvScalar(0,0,255), 2);
    launch(imgBGR);

    imgptr = imgBGR->data.ptr;
    for (i = 0; i < height; i++)
    {
      for (j = 0; j < width; j++)
      {
        b=(imgptr+j*3)[0]; g=(imgptr+j*3)[1]; r=(imgptr+j*3)[2];
        rgba[i * width + j] = 0xff000000 + (b << 16) + (g << 8) + r;
      }
      imgptr+=step;
    }
  }
  cvReleaseMat(&imgBGR);

  env->ReleaseByteArrayElements(jdata,data,0);
  env->SetIntArrayRegion(outarr,0,frameSize,rgba);
  delete [] rgba;

  return outarr;
}

void launch(CvMat * img)
{
  cvLine(img, cvPoint(20,50), cvPoint(50,50), cvScalar(0,0,255), 2);
}
