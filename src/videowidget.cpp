/** -*- c++ -*- 
 *
 * \file   videowidget.cpp
 * \date   Mon May 18 17:02:55 2015
 *
 * \copyright 
 * Copyright (c) 2015 Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Brainnetome Center & NLPR at Institute of Automation, CAS. The 
 * name of the Brainnetome Center & NLPR at Institute of Automation, CAS 
 * may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * \brief  implement of the video frame displaying widget
 */
 
#include "videowidget.h"

QPixmap cvGetQtPixmap(CvMat * bgr)
{
  assert(CV_MAT_TYPE(bgr->type==CV_8U)==CV_8U);
  assert(bgr->step==bgr->cols*3);
  CvMat * rgb=cvCreateMat(bgr->rows,bgr->cols,CV_8UC3);
  // cvCvtColor(bgr,rgb,CV_BGR2RGB);
  int from_to[]={0,2,2,0,1,1};
  cvMixChannels((const CvArr**)&bgr,1,(CvArr**)&rgb,1,from_to,3);
  QPixmap retval =  QPixmap::fromImage(QImage(rgb->data.ptr,rgb->cols,rgb->rows,rgb->step,
											  QImage::Format_RGB888));
  cvReleaseMat(&rgb);
  return retval;
}

void VideoWidget::paintEvent(QPaintEvent *)
{
  float w = width();
  float h = height();
  QPainter painter(this);

  // fill background .. 
  CvMat * img = cvCreateMat(h,w,CV_8UC3);
  cvSet(img,cvScalarAll(0));
  painter.drawPixmap(QRect(0,0,w,h),cvGetQtPixmap(img));
  cvReleaseMat(&img);

  if (m_dispImage){
	adjustSize();
	QRect dispRect = QRect(m_dispRect.x,m_dispRect.y,m_dispRect.width,m_dispRect.height);
	painter.drawPixmap(dispRect,cvGetQtPixmap(m_dispImage));

	if (m_dragging && m_currentState==1){
	  int x = MIN(m_dragCurrent.x,m_dragStart.x);
	  int w = MAX(m_dragCurrent.x,m_dragStart.x)-x;
	  int y = MIN(m_dragCurrent.y,m_dragStart.y);
	  int h = MAX(m_dragCurrent.y,m_dragStart.y)-y;
	  painter.setBrush(Qt::NoBrush);
	  QPen pen(Qt::red);pen.setWidth(3);
	  painter.setPen(pen);
	  painter.drawRect(x,y,w,h);
	}
  }
}

void VideoWidget::mousePressEvent(QMouseEvent * evt)
{
  if (m_dispImage){
	if (evt->button() == Qt::LeftButton){
	  m_dragging = 1;
	  m_dragStart = m_dragCurrent = cvPoint(evt->x(),evt->y());
	}
	if (evt->button() == Qt::RightButton){
	}
  }
}

void VideoWidget::mouseMoveEvent(QMouseEvent * evt)
{
  if (m_dispImage && m_dragging){
	m_dragCurrent = cvPoint(evt->x(),evt->y());
  }  
}

void VideoWidget::mouseReleaseEvent(QMouseEvent * evt)
{
  if (evt->button() == Qt::LeftButton){
	if (m_dispImage && m_dragging && m_currentState==1){
	  CvPoint dragCurrent = cvPoint(evt->x(),evt->y());
	  int x = MIN(dragCurrent.x,m_dragStart.x);
	  int w = MAX(dragCurrent.x,m_dragStart.x)-x;
	  int y = MIN(dragCurrent.y,m_dragStart.y);
	  int h = MAX(dragCurrent.y,m_dragStart.y)-y;
	  float invscale = 1./m_globalScale;
	  // m_roilist.push_back(cvRect((x-m_offset.x)*invscale,(y-m_offset.y)*invscale,
	  // 							 w*invscale,h*invscale));
	  setCurrentState(2);
	  emit objectSelected();
	}  
	m_dragging = 0;
  }
}

void VideoWidget::resizeEvent(QResizeEvent * evt)
{
  adjustSize();
}

void VideoWidget::adjustSize()
{
  float w = width();
  float h = height();
  if (m_dispImage){
	float nr = m_dispImage->rows;
	float nc = m_dispImage->cols;
	if (((nr/nc)/(h/w))>1.){
	  m_globalScale=h/nr;
	  m_offset=cvPoint2D32f((w-(nc/nr*h))*.5,0);
	}else{
	  m_globalScale=w/nc;
	  m_offset=cvPoint2D32f(0,(h-(nr/nc*w))*.5);
	}
	m_dispRect=cvRect(m_offset.x,m_offset.y,nc*m_globalScale,nr*m_globalScale);
  }
  update();
}

void VideoWidget::setCurrentState(int state)
{
  m_currentState = state;
  if (state==1){
	this->setCursor(Qt::CrossCursor);
  }else{
	this->setCursor(Qt::ArrowCursor);
  }
}
