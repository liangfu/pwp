/** -*- mode: c++ -*- 
 *
 * \file   videoplayer.h
 * \date   Tue May 19 09:45:44 2015
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
 * \brief  interface of videoplayer class that processes frames of a video content
 */

#ifndef __VIDEOPLAYER_H__
#define __VIDEOPLAYER_H__

#include "_vatool.h"

#include "videowidget.h"

class VideoPlayer : public QWidget
{
  Q_OBJECT

public:
  VideoPlayer(QWidget *parent = 0);
  ~VideoPlayer();

  VideoWidget * videoWidget(){return m_videoWidget;}
  QPushButton * playButton(){return m_playButton;}

private:
  void presentImage(CvMat * image);

  enum MovieState {NotRunning=0,Running=1,Paused=2};

  MovieState m_moviestate;
  float m_framerate;
  int m_framecount;
  QTimer m_timer;
  
  CvCapture * m_capture;
  VideoWidget * m_videoWidget;
  
  QPushButton * m_playButton;
  QSlider * positionSlider;
  
public slots:
  void openFile(char * fname);
  void play();
  void pause();

private slots:
  void movieStateChanged(MovieState state);
  void setPosition(int frame);
  void grabNextFrame();

signals:
  void frameChanged(const QString msg);
};

#endif // __VIDEOPLAYER_H__


