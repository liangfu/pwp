/** -*- mode: c++ -*- 
 *
 * \file   videowidget.h
 * \date   Mon May 18 17:00:29 2015
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
 * \brief  widget for displaying video frames
 */
#ifndef __VIDEOWIDGET_H__
#define __VIDEOWIDGET_H__

#include "_vatool.h"

CVAPI(QPixmap) cvGetQtPixmap(CvMat * bgr);

class VideoWidget : public QWidget
{
  Q_OBJECT

  int m_currentState;

  CvMat * m_dispImage;

  CvPoint2D32f m_offset;
  float m_globalScale;
  CvRect m_dispRect;
  
  int m_dragging;
  CvPoint m_dragStart;
  CvPoint m_dragCurrent;

  QList<CvAnnotatedObject> m_objlist;

  void adjustSize();
  
protected:
  void paintEvent(QPaintEvent * evt);
  void mousePressEvent(QMouseEvent * evt);
  void mouseMoveEvent(QMouseEvent * evt);
  void mouseReleaseEvent(QMouseEvent * evt);
  void resizeEvent(QResizeEvent * evt);
  
public:
  VideoWidget(QWidget * parent):
	QWidget(parent),m_currentState(0),m_dispImage(0),m_globalScale(1.f),m_dragging(0)
  {
	m_offset=cvPoint2D32f(0,0);
	m_dispRect = cvRect(0,0,0,0);
	update();
  }
  ~VideoWidget()
  {
	if (m_dispImage){cvReleaseMat(&m_dispImage);m_dispImage=0;}
  }

  void display(CvMat * img)
  {
	if (m_dispImage){cvReleaseMat(&m_dispImage);m_dispImage=0;}
	m_dispImage=cvCloneMat(img);
	update();
  }

  void setCurrentState(int state);

  CvAnnotatedObject lastSelectedObject(){ 
	if (m_objlist.size()>0){
	  return m_objlist[m_objlist.size()-1];
	}else{
	  CvAnnotatedObject obj;
	  return obj;
	}
  }

  QList<CvAnnotatedObject> currentObjectList(){return m_objlist;}
  
signals:
  void objectSelected();
};

#endif // __VIDEOWIDGET_H__

