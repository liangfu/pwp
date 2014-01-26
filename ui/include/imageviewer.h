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
  QGraphicsPixmapItem * imageLabel;
  QGraphicsScene * scrollArea;
  
public:
  ImageViewer(QWidget * parent):
	QGraphicsView(parent)
  {
	imageLabel = new QGraphicsPixmapItem;
	scrollArea = new QGraphicsScene;
	setScene(scrollArea);
	int w=parent->width()-4;
	int h=parent->height()-4;
	scrollArea->setSceneRect(0,0,w,h);
	scrollArea->addItem(imageLabel);
	setBackgroundBrush(QBrush(qRgb(0,0,0)));
  }

  void display(QString fname)
  {
	// const char * fnamestr=fname.toAscii();
	// fprintf(stderr,"%s\n",fnamestr);
	QImage img(fname);
	if (img.isNull()){
	  QMessageBox::warning(this,"File missing",QString("File %1 doesn't exist!").arg(fname));
	  return;
	}
	QImage scaled;
	int sw = scrollArea->sceneRect().width();
	int sh = scrollArea->sceneRect().height();
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
	imageLabel->setPixmap(QPixmap::fromImage(scaled));
	imageLabel->setPos(xpos,ypos);
  }
  
};

#endif // __IMAGE_VIEWER_H__
