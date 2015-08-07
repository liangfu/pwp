/**
 * @file   mainwindow.cpp
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Wed Sep  3 12:55:55 2014
 * 
 * @brief  
 * 
 * 
 */
#include "mainwindow.h"

void MainWindow::on_actionOpen_triggered()
{
  QString fileName =
	QFileDialog::getOpenFileName(this,"Open Media File",QDir::currentPath(),
								 "Video Files [*.avi *.mp4] (*.avi *.mp4);;"
								 "All Files [*.*] (*.*)");
  if (fileName.isEmpty() == true) { return; }
  QDir::setCurrent(QFileInfo(fileName).absolutePath());

  char fileName_str[1024];memset(fileName_str,0,sizeof(fileName_str));
  strcpy(fileName_str,fileName.toLocal8Bit().data());

  loadVideo((char*)fileName_str);
}

void MainWindow::on_pushButton_option_clicked()
{
}

void MainWindow::on_pushButton_save_clicked()
{
}

void MainWindow::on_pushButton_newobj_clicked()
{
  mediaplayer->pause();
  mediaplayer->videoWidget()->setCurrentState(1);
}

void MainWindow::displayVideo(char * fname)
{
  mediaplayer->openFile(fname);

  pushButton_option->setEnabled(1);
  pushButton_save->setEnabled(1);
  pushButton_newobj->setEnabled(1);

  groupBox_objlist->clearSelection();

  connect(mediaplayer->videoWidget(),SIGNAL(objectSelected()),
		  this,SLOT(listObjects()),Qt::UniqueConnection);
  connect(mediaplayer,SIGNAL(frameChanged(const QString)),
		  statusBar(),SLOT(showMessage(const QString)),Qt::UniqueConnection);
}

void MainWindow::listObjects()
{
  CvAnnotatedObject obj = mediaplayer->videoWidget()->lastSelectedObject();
  CvRect roi = obj.roi;
  CvScalar color = obj.color;
  
  // widget_newobj->setVisible(0);
  pushButton_newobj->setEnabled(0);
  groupBox_objlist->setVisible(1);

  connect(groupBox_objlist,SIGNAL(selectionChanged(int)),
		  this,SLOT(listOptions(int)),Qt::UniqueConnection);
}

void MainWindow::listOptions(int idx)
{
  // widget_newobj->setVisible(1);
  pushButton_newobj->setEnabled(1);
  groupBox_objlist->setVisible(0);

  ObjectStatusDialog * objstat = new ObjectStatusDialog(this);
  objstat->setTitle("Primate 1");
  objstat->setStyleSheet("background-color:rgb(255,127,127);");
  ((QGridLayout*)widget_objlist->layout())->addWidget(objstat);
}

// void MainWindow::setCurrentTime(float now, float total)
// {
//   setStatusBar();
// }

void MainWindow::recordEvent()
{
  // QString currTime = mediaplayer->currentTimeLabel().split("/")[0];
  // if (currTime.size()<1){return;}
  // if (m_behavior.size()==0){m_behavior.push_back(Behavior("0:00",-1,0));}
  // m_behavior.push_back(Behavior(currTime,m_prevStatus,m_currStatus));
  // updateHistoryTable();
  // m_currStatus = -1;
}

void MainWindow::updateHistoryTable()
{
  // int i;
  // for (i=0;i<m_behavior.size();i++){
  // 	qDebug()<< m_behavior[i].m_time << " at " <<
  // 	  m_behavior[i].m_prevEvent << " - " <<
  // 	  m_behavior[i].m_currEvent;
  // }
}
