/**
 * @file   cvjnitracker.h
 * @author Liangfu Chen <liangfu.chen@cn.fix8.com>
 * @date   Mon Apr 22 17:16:18 2013
 * 
 * @brief  
 * 
 * 
 */

#ifndef __CV_JNI_TRACKER_H__
#define __CV_JNI_TRACKER_H__

#include "cvext_c.h"
#include "cvtracker.h"

class CV_EXPORTS CvJNITracker
{
  CvGenericTracker m_tracker;
public:
  CvJNITracker()
  {
    
  }

  void update(CvMat * img)
  {
    // cvLine(img, cvPoint(20,50), cvPoint(50,50), cvScalar(0,0,255), 2);
    if (!m_tracker.initialized()){
      m_tracker.initialize(img);
    }else{
      m_tracker.update(img);
    }

    cvMerge(m_tracker.m_silhImage, m_tracker.m_silhImage,
            m_tracker.m_silhImage, NULL, img);
  }
};

#endif // __CV_JNI_TRACKER_H__
