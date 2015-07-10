/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "videoplayer.h"

#include <QtMultimedia>

VideoPlayer::VideoPlayer(QWidget * parent):
  QWidget(parent),m_moviestate(NotRunning),
  m_framerate(0),m_framecount(0),
  m_capture(0),m_videoWidget(new VideoWidget(this)),
  m_playButton(0),positionSlider(0)
{
  m_timer.setInterval(33);
  m_timer.setSingleShot(0);
  m_timer.stop();
 
  m_playButton = new QPushButton(this);
  m_playButton->setEnabled(0);
  m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

  connect(m_playButton, SIGNAL(clicked()),this, SLOT(play()),Qt::UniqueConnection);

  positionSlider = new QSlider(Qt::Horizontal);
  positionSlider->setRange(0, 0);

  connect(positionSlider, SIGNAL(sliderMoved(int)),
		  this, SLOT(setPosition(int)),Qt::UniqueConnection);

  QBoxLayout *controlLayout = new QHBoxLayout;
  controlLayout->setMargin(0);
  controlLayout->addWidget(m_playButton);
  controlLayout->addWidget(positionSlider);

  QBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_videoWidget);
  layout->addLayout(controlLayout);

  setLayout(layout);
}

VideoPlayer::~VideoPlayer()
{
  if (m_capture){cvReleaseCapture(&m_capture);m_capture=0;}
}

void VideoPlayer::openFile(char * fname)
{
  if (m_capture){cvReleaseCapture(&m_capture);m_capture=0;}
  m_capture = cvCreateFileCapture(fname);
  if (!m_capture){
	QMessageBox::warning(this,"Warning","fail to load video file.");return;
  }
  m_framerate = cvGetCaptureProperty(m_capture,CV_CAP_PROP_FPS);
  m_framecount = cvGetCaptureProperty(m_capture,CV_CAP_PROP_FRAME_COUNT);
  cvSetCaptureProperty(m_capture,CV_CAP_PROP_POS_FRAMES,0);

  m_timer.setInterval(cvRound(1000./m_framerate));
  connect(&m_timer,SIGNAL(timeout()),this,SLOT(grabNextFrame()));
  
  // present first frame
  IplImage * rawImage = cvQueryFrame(m_capture);
  CvMat rawMat_stub;
  CvMat * rawMat = cvGetMat(rawImage,&rawMat_stub);
  presentImage(rawMat);

  m_playButton->setEnabled(1);
  positionSlider->setRange(0,m_framecount-1);
  positionSlider->setValue(0);
}

void VideoPlayer::grabNextFrame()
{
  int frame = cvGetCaptureProperty(m_capture,CV_CAP_PROP_POS_FRAMES);
  if (frame>=m_framecount){
	m_timer.stop();
	positionSlider->setRange(0,0);
	m_playButton->setEnabled(0);
  }
  setPosition(frame+1);
}

void VideoPlayer::play()
{
  switch(m_moviestate) {
  case NotRunning:
	m_moviestate = Running;
	break;
  case Paused:
	m_moviestate = Running;
	break;
  case Running:
	m_moviestate = Paused;
	break;
  }
  emit movieStateChanged(m_moviestate);
}

void VideoPlayer::pause()
{
  m_moviestate = Paused;
  emit movieStateChanged(m_moviestate);
}

void VideoPlayer::movieStateChanged(MovieState state)
{
  switch(m_moviestate) {
  case NotRunning:
	m_timer.stop();
	m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	m_playButton->setEnabled(0);
	positionSlider->setRange(0,0);
	break;
  case Running:
	m_timer.start();
	m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	break;
  case Paused:
	m_timer.stop();
	m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	break;
  }
}

void VideoPlayer::setPosition(int frame)
{
  if (frame>=m_framecount-1){
	positionSlider->setValue(0);
	emit movieStateChanged(Paused);
	return;
  }
  cvSetCaptureProperty(m_capture,CV_CAP_PROP_POS_FRAMES,frame);

  IplImage * rawImage = cvQueryFrame(m_capture);
  CvMat rawMat_stub;
  CvMat * rawMat = cvGetMat(rawImage,&rawMat_stub);
  presentImage(rawMat);

  float now = cvGetCaptureProperty(m_capture,CV_CAP_PROP_POS_MSEC)/1000.f;
  float total = m_framecount/m_framerate;
  emit frameChanged(QString("Playing | %1:%2/%3:%4").
					arg(cvFloor(now/60.f)).arg(cvRound(now)%60,2,10,QChar('0')).
					arg(cvFloor(total/60.f)).arg(cvRound(total)%60,2,10,QChar('0')));
}

void VideoPlayer::presentImage(CvMat * image)
{
  m_videoWidget->display(image);
}

// void VideoPlayer::setCurrentState(Qt::InteractState state)
// {
//   if (state==Qt::NewObject){
// 	m_videoWidget->setCurrentState(state);
//   }
// }


