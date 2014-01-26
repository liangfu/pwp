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

class ImageViewer : public QGraphicsView
{
  QGraphicsPixmapItem * m_pItem;
  QGraphicsScene * m_pScene;

  QString m_currdirname;
  QString m_currimgname;
  QStringList m_imgnamelist;
  QImage m_currimg;
  QImage m_currimg_scaled;

  void paint(const QImage & img)
  {
	QImage scaled;
	int sw = m_pScene->sceneRect().width();
	int sh = m_pScene->sceneRect().height();
	int w = img.width();
	int h = img.height();
	int xpos=0;
	int ypos=0;
	if ((w>sw)||(h>sh)){
	  float xratio=float(sw)/float(w);
	  float yratio=float(sh)/float(h);
	  if (xratio>yratio){
		scaled=img.scaledToHeight(sh);
		xpos=(sw-scaled.width())*.5;
	  }else{
		scaled=img.scaledToWidth(sw);
		ypos=(sh-scaled.height())*.5;
	  }
	}else{
	  scaled=img;
	  xpos=(sw-w)*.5;
	  ypos=(sh-h)*.5;
	}
	m_currimg_scaled=scaled;
	m_pItem->setPixmap(QPixmap::fromImage(scaled));
	m_pItem->setPos(xpos,ypos);
  }

  // for zoom-out and zoom-in
  void repaint(double scale)
  {
	QImage scaled=m_currimg.scaledToWidth(m_currimg_scaled.width()*scale);
	int sw = m_pScene->sceneRect().width();
	int sh = m_pScene->sceneRect().height();
	int w = scaled.width();
	int h = scaled.height();
	if ((w>sw)||(h>sh)){
	  m_pScene->setSceneRect(0,0,w,h);
	}else{
	  m_pScene->setSceneRect(0,0,width()-4,height()-4);
	}
	sw = m_pScene->sceneRect().width();
	sh = m_pScene->sceneRect().height();
	int xpos=0;
	int ypos=0;
	xpos=(sw-w)*.5;
	ypos=(sh-h)*.5;
	m_currimg_scaled=scaled;
	m_pItem->setPixmap(QPixmap::fromImage(scaled));
	m_pItem->setPos(xpos,ypos);
  }
  
public:
  ImageViewer(QWidget * parent):
	QGraphicsView(parent),m_pItem(0),m_pScene(0)
  {
	// create the container
	m_pItem = new QGraphicsPixmapItem;
	m_pScene = new QGraphicsScene;
	setScene(m_pScene);
	int w=parent->width()-4;
	int h=parent->height()-4;
	m_pScene->setSceneRect(0,0,w,h);
	m_pScene->addItem(m_pItem);
	setBackgroundBrush(QBrush(qRgb(0,0,0)));
  }
  ~ImageViewer()
  {
	if (m_pItem) { delete m_pItem; m_pItem=0; }
	if (m_pScene) { delete m_pScene; m_pScene=0; }
  }

  void display(QString fname)
  {
	// const char * fnamestr=fname.toAscii();
	// fprintf(stderr,"%s\n",fnamestr);
	QImage img(fname);
	if (img.isNull()){
	  QMessageBox::warning(this,"File missing",QString("File %1 doesn't exist!").arg(fname));
	  return;
	}else{
	  m_currdirname=QFileInfo(fname).absolutePath();
	  m_currimgname=QFileInfo(fname).fileName();
	  m_currimg=img;
	  QStringList filters;filters<<"*.jpg"<<"*.png";
	  m_imgnamelist=QDir(m_currdirname).entryList(filters,QDir::Files,
										  QDir::SortFlags(QDir::Name|QDir::IgnoreCase));
	  paint(img);
	}
  }

  void first()
  {
	if (m_imgnamelist.count()>0){
	  QFileInfo info=QFileInfo(m_currdirname,m_imgnamelist[0]);
	  display(info.absoluteFilePath());
	}
  }

  void last()
  {
	if (m_imgnamelist.count()>0){
	  QFileInfo info=QFileInfo(m_currdirname,m_imgnamelist[m_imgnamelist.count()-1]);
	  display(info.absoluteFilePath());
	}
  }
  
  void previous()
  {
	int i;
	for (i=0;i<m_imgnamelist.count();i++){
	  if (!m_imgnamelist[i].compare(m_currimgname)){
		QFileInfo info=QFileInfo(m_currdirname,m_imgnamelist[MAX(0,MIN(i-1,m_imgnamelist.count()-1))]);
		display(info.absoluteFilePath());
		break;
	  }
	}
  }

  void next()
  {
	int i;
	for (i=0;i<m_imgnamelist.count();i++){
	  if (!m_imgnamelist[i].compare(m_currimgname)){
		QFileInfo info=QFileInfo(m_currdirname,m_imgnamelist[MAX(0,MIN(i+1,m_imgnamelist.count()-1))]);
		display(info.absoluteFilePath());
		break;
	  }
	}
  }

  // bigger
  void zoomIn()
  {
	repaint(1.25);
  }
  // smaller
  void zoomOut()
  {
	repaint(.8);
  }
  
  QString currentFileName()
  {
	return m_currimgname;
  }
};

#endif // __IMAGE_VIEWER_H__
