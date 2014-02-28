/**
 * @file   imageviewer.h
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Fri Jan 24 15:37:45 2014
 * 
 * @brief  
 * 
 * 
 */
#ifndef __IMAGE_VIEWER_H__
#define __IMAGE_VIEWER_H__

#include <QtGui>
#include "cxcore.h"
// #include "cv.h"

CV_INLINE
QPixmap icvQPixmap(CvMat * bgr)
{
  assert(CV_MAT_TYPE(bgr->type==CV_8U)==CV_8U);
  assert(bgr->step==bgr->cols*3);
  CvMat * rgb=cvCreateMat(bgr->rows,bgr->cols,CV_8UC3);
  // cvCvtColor(bgr,rgb,CV_BGR2RGB);
  int from_to[]={0,2,2,0,1,1};
  cvMixChannels((const CvArr**)&bgr,1,(CvArr**)&rgb,1,from_to,3);
  return QPixmap::fromImage(QImage(rgb->data.ptr,rgb->cols,rgb->rows,rgb->step,
								   QImage::Format_RGB888));
  cvReleaseMat(&rgb);
}

class Canvas : public QWidget
{
  CvMat * m_dispImage;
protected:
  void paintEvent(QPaintEvent *)
  {
	QPainter painter(this);
	if (m_dispImage){
	  // display image in unknown size, adjust pose to fit window
	  painter.drawPixmap(QRect(0,0,320,240),icvQPixmap(m_dispImage));
	}else{
	  CvMat * img = cvCreateMat(240,320,CV_8UC3);
	  cvSet(img,cvScalarAll(218));
	  painter.drawPixmap(QRect(0,0,320,240),icvQPixmap(img));
	  cvReleaseMat(&img);
	}
  }
  
public:
  Canvas(QWidget * parent):QWidget(parent),m_dispImage(0)
  {
	// QTimer *timer = new QTimer(this);
	// connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	// timer->start(1000);
	repaint();
  }
  ~Canvas()
  {
	if (m_dispImage){cvReleaseMat(&m_dispImage);m_dispImage=0;}
  }

  void display(CvMat * img)
  {
	if (m_dispImage){cvReleaseMat(&m_dispImage);m_dispImage=0;}
	m_dispImage=cvCloneMat(img);
	repaint();
  }
};

#endif // __IMAGE_VIEWER_H__
