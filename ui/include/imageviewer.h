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

  QString m_currdir;
  QString m_currimg;
  QStringList m_imglist;
  
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
	  m_currdir=QFileInfo(fname).absolutePath();
	  m_currimg=QFileInfo(fname).fileName();
	  QStringList filters;filters<<"*.jpg"<<"*.png";
	  m_imglist=QDir(m_currdir).entryList(filters,QDir::Files,
										  QDir::SortFlags(QDir::Name|QDir::IgnoreCase));
	}
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
	}
	m_pItem->setPixmap(QPixmap::fromImage(scaled));
	m_pItem->setPos(xpos,ypos);
  }

  void previous()
  {
	int i;
	for (i=0;i<m_imglist.count();i++){
	  if (!m_imglist[i].compare(m_currimg)){
		QFileInfo info=QFileInfo(m_currdir,m_imglist[MAX(0,MIN(i-1,m_imglist.count()-1))]);
		display(info.absoluteFilePath());
		break;
	  }
	}
  }

  void next()
  {
	int i;
	for (i=0;i<m_imglist.count();i++){
	  if (!m_imglist[i].compare(m_currimg)){
		QFileInfo info=QFileInfo(m_currdir,m_imglist[MAX(0,MIN(i+1,m_imglist.count()-1))]);
		display(info.absoluteFilePath());
		break;
	  }
	}
  }

  QString currentFileName()
  {
	return m_currimg;
  }
};

#endif // __IMAGE_VIEWER_H__
