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

  void openFile(QString fname)
  {
	if (!fname.isEmpty())
	{
	  qDebug(fname.toAscii());
	  char suffix[1024];
	  cvGetFileSuffix(fname.toAscii(),suffix);
	  //const char * suffix=QFileInfo(fname).suffix().toAscii();
	  if ((!strncmp(suffix+1,"jpg",3))||(!strncmp(suffix+1,"png",3))){
		displayImage(fname);
	  }else if (!strncmp(suffix+1,"txt",3)){
	  }else if (!strncmp(suffix+1,"xml",3)){
	  }else if ((!strncmp(suffix+1,"avi",3))||(!strncmp(suffix+1,"mp4",3))){
	  }else if (!strncmp(suffix+1,"obj",3)){
		displayMesh(fname);
	  }else if (!strncmp(suffix+1,"rawiv",5)){
	  }else{
		assert(false);
	  }
	}
  }
  
private:
  int m_mode;
  ImageViewer * graphicsView;
  MeshViewer * glcanvas;
  
  int m_initialized;
  int initialized(){return m_initialized;}
  void initialize(int mode)
  {
	removeAllWidgets();
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
  void removeAllWidgets()
  {
	if (graphicsView){
	  gridLayout->removeWidget(graphicsView);
	  delete graphicsView;
	  graphicsView=NULL;
	}
	if (glcanvas){
	  gridLayout->removeWidget(glcanvas);
	  delete glcanvas;
	  glcanvas=NULL;
	}
  }

  void displayImage(QString fname)
  {
	initialize(MainWindow::DisplayMode_IMAGE);
	graphicsView->display(fname);
	setWindowTitle(graphicsView->currentFileName());
  }

  void displayMesh(QString fname)
  {
	initialize(MainWindow::DisplayMode_MESH);
	glcanvas->display(fname);
  }

protected:
  void dragEnterEvent(QDragEnterEvent *e)
  {
    if (e->mimeData()->hasUrls()) {
	  e->acceptProposedAction();
	}
  }

  void dropEvent(QDropEvent *e)
  {
	int i;
    for (i=0;i<e->mimeData()->urls().count();i++) {
	  const QUrl url=e->mimeData()->urls()[i];
	  const QString fname = url.toLocalFile();
	  //fprintf(stderr,"Dropped file: %s",qPrintable(fname));
	  openFile(fname);
	}
  }

private slots:
  void on_actionOpen_triggered()
  {
	QString fname =
	  QFileDialog::getOpenFileName(this,"select file",".",
								   "Images files [*.png,*.jpg] (*.png *.xpm *.jpg);;"
								   "Text files [*.txt] (*.txt);;"
								   "Video files [*.avi,*.mp4] (*.avi,*.mp4);;"
								   "Mesh files [*.obj] (*.obj);;"
								   "Volume data [*.rawiv] (*.rawiv)");
	openFile(fname);
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

  void on_actionFirst_triggered()
  {
	if (graphicsView){
	  graphicsView->first();
	  setWindowTitle(graphicsView->currentFileName());
	}
  }
  
  void on_actionLast_triggered()
  {
	if (graphicsView){
	  graphicsView->last();
	  setWindowTitle(graphicsView->currentFileName());
	}
  }
  
  void on_actionPrevious_triggered()
  {
	if (graphicsView){
	  graphicsView->previous();
	  setWindowTitle(graphicsView->currentFileName());
	}
  }
  
  void on_actionNext_triggered()
  {
	if (graphicsView){
	  graphicsView->next();
	  setWindowTitle(graphicsView->currentFileName());
	}
  }
  
  void on_actionZoomIn_triggered()
  {
	if (graphicsView){ graphicsView->zoomIn(); }
  }
  void on_actionZoomOut_triggered()
  {
	if (graphicsView){ graphicsView->zoomOut(); }
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
