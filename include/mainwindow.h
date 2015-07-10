/**
 * @file   mainwindow.h
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Fri Aug 22 14:41:20 2014
 * 
 * @brief  
 * 
 * 
 */
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "ui_mainwindow.h"

#include "_vatool.h"

class Behavior
{
public:
  Behavior(QString time, int prevEvent=-1, int currEvent=-1):
	m_time(time),m_prevEvent(prevEvent),m_currEvent(currEvent)
  {}
  ~Behavior(){}
  QString m_time;
  int m_prevEvent;
  int m_currEvent;
};

class MainWindow : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget * parent=0):
	QMainWindow(parent),m_prevStatus(-1),m_currStatus(-1)
  {
	setupUi(this);

	groupBox_objlist->setVisible(0);
	groupBox_objstat->setVisible(0);
  }
  ~MainWindow(){}

private slots:

  void on_actionOpen_triggered();
  void on_pushButton_newobj_clicked();

  void listObjects();
  void listOptions(int index);

private:
  QList<Behavior> m_behavior;
  int m_prevStatus;
  int m_currStatus;

  void recordEvent();
  void updateHistoryTable();

  void loadVideo(char *  fname)
  {
	typedef void (MainWindow::*CvTestFuncType)(char *);
	static CvTestFuncType func[]={
	  &MainWindow::displayVideo,0
	};
	(this->*func[0])(fname);
  }
  
  void displayVideo(char * fname)
  {
	mediaplayer->openFile(fname);

	pushButton_newobj->setEnabled(1);
	groupBox_objlist->clearSelection();

	connect(mediaplayer->videoWidget(),SIGNAL(objectSelected()),
			this,SLOT(listObjects()),Qt::UniqueConnection);
	connect(mediaplayer,SIGNAL(frameChanged(const QString)),
			statusBar(),SLOT(showMessage(const QString)),Qt::UniqueConnection);
  }
};

#endif // __MAIN_WINDOW_H__


