/**
 * @file   main.cpp
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Wed Jan 15 19:47:18 2014
 * 
 * @brief  
 * 
 * 
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow win;
  win.show();

  return app.exec();
}

