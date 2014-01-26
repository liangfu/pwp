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

int fakemain(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  // QApplication app(vargc, vargv);
  // MainWindow win;
  // win.show();
  // retval=app.exec();
  // return retval;
  return fakemain(argc, argv);
}

int fakemain(int argc, char *argv[])
{
  int i;
  int vargc=1;
  char * vargv[]={argv[0],0};
  int retval=0;
  struct Options{
	int display;int openfile;char fname[1024];
	Options():display(1),openfile(0){memset(fname,0,sizeof(fname));}
  } opts;

  // parse input arguments
  for (i=1;i<argc;i++){
	if (!strcmp(argv[i],"-h")){
	  fprintf(stderr,"usage: %s filename\n",argv[0]);
	}else if (!strcmp(argv[i],"-nodisplay")){
	  opts.display=0;
	}else{
	  opts.openfile=1;
	  strcpy(opts.fname,argv[i]);
	}
  }
	
  QApplication app(vargc, vargv);
  MainWindow win;
  if (opts.display){win.show();}
  if (opts.openfile&&opts.fname[0]){win.openFile(opts.fname);}
  retval=app.exec();
  return retval;
}

