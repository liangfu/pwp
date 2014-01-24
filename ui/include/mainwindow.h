/**
 * @file   mainwindow.h
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Thu Jan 23 20:35:25 2014
 * 
 * @brief  
 * 
 * 
 */

#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <stdio.h>
#include <assert.h>

#include "ui_compvis.h"
#include <QtGui>
#include <QtOpenGL>

#include "compvis.h"
#include "imageviewer.h"
#include "meshviewer.h"

class MainWindow : public QMainWindow,public Ui::MainWindow
{
  Q_OBJECT
  
public:
  // Worker * m_pDataWorker;
  static const int DisplayMode_IMAGE=1;
  static const int DisplayMode_MESH=2;
  
private:
  int m_mode;
  ImageViewer * graphicsView;
  MeshViewer * glcanvas;
  
  int m_initialized;
  int initialized(){return m_initialized;}
  int initialize(int mode)
  {
	if (mode==DisplayMode_IMAGE){
	  if (!graphicsView){graphicsView = new ImageViewer(widget);}
	  graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
	  gridLayout->addWidget(graphicsView, 0, 0, 1, 1);
	}else if (mode==DisplayMode_MESH){
	  if (!glcanvas) { glcanvas = new MeshViewer(widget); }
	  glcanvas->setObjectName(QString::fromUtf8("glcanvas"));
	  gridLayout->addWidget(glcanvas,0,0,1,1);
	}else{assert(false);}
	m_initialized=1;
  }

  void displayImage(QString fname)
  {
	// QImage img(fname);
	// graphicsView->displayImage(img);
	initialize(MainWindow::DisplayMode_IMAGE);
	graphicsView->display(fname);
  }

  void displayMesh(QString fname)
  {
	// CvMat * verts = 0;
	// CvMat * faces = 0;
	// icvLoadSurface(fname.toAscii(),verts,faces);
	initialize(MainWindow::DisplayMode_MESH);
	glcanvas->display(fname);
  }
					
private slots:
  void on_actionOpen_triggered()
  {
	QString fileName =
	  QFileDialog::getOpenFileName(this,"select file",".",
								   "Images files [*.png,*.jpg] (*.png *.xpm *.jpg);;"
								   "Text files [*.txt] (*.txt);;"
								   "Video files [*.avi,*.mp4] (*.avi,*.mp4);;"
								   "Mesh files [*.obj] (*.obj);;"
								   "Volume data [*.rawiv] (*.rawiv)");
	if (!fileName.isEmpty())
	{
	  const char * suffix=QFileInfo(fileName).suffix().toAscii();
	  if ((!strcmp(suffix,"jpg"))||(!strcmp(suffix,"png"))){
		displayImage(fileName);
	  }else if (!strcmp(suffix,"txt")){
		
	  }else if (!strcmp(suffix,"xml")){
		
	  }else if ((!strcmp(suffix,"avi"))||(!strcmp(suffix,"mp4"))){
		
	  }else if (!strcmp(suffix,"obj")){
		displayMesh(fileName);
	  }else if (!strcmp(suffix,"rawiv")){
		
	  }else{
		assert(false);
	  }
	}
  }
  
  void on_actionToolbar_toggled()
  {
	if (actionToolbar->isChecked()){
	  toolBar->show();
	}else{
	  toolBar->hide();
	}
  }
  
  void on_actionStatusbar_toggled()
  {
	if (actionStatusbar->isChecked()){
	  statusbar->show();
	}else{
	  statusbar->hide();
	}
  }
  
  void on_actionAbout_triggered()
  {
	QMessageBox::about(this, tr("About CompVis"),
					   tr("<b>CompVis</b> is an application designed for "
						  "vision-base media content manipulations."));
  }
  
public:
  MainWindow(QWidget * parent=0):
	QMainWindow(parent),m_initialized(0),graphicsView(NULL),glcanvas(NULL)
  {
	setupUi(this);
  }
};

#endif // __MAIN_WINDOW_H__
