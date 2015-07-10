/** -*- mode: c++ -*- 
 *
 * \file   objectdialog.h
 * \date   Thu May 21 11:07:10 2015
 *
 * \copyright 
 * Copyright (c) 2015 Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Brainnetome Center & NLPR at Institute of Automation, CAS. The 
 * name of the Brainnetome Center & NLPR at Institute of Automation, CAS 
 * may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * \brief  interface of object list dialog and object status dialogs
 */
#ifndef __OBJECTDIALOG_H__
#define __OBJECTDIALOG_H__

#include "_vatool.h"

class ObjectListDialog : public QGroupBox
{
  Q_OBJECT

  QButtonGroup * m_buttonGroup;
public:
  ObjectListDialog(QWidget * parent):QGroupBox(parent),m_buttonGroup(0)
  {}
  ~ObjectListDialog(){}

  void clearSelection();
private slots:
  void buttonPressed(int idx){emit selectionChanged(idx);}

signals:
  void selectionChanged(int index);
};

class ObjectStatusDialog : public QGroupBox
{

public:
  ObjectStatusDialog(QWidget * parent):QGroupBox(parent)
  {
	QGridLayout * gridLayout = new QGridLayout(this);
	gridLayout->addWidget(new QCheckBox("Outside of view frame",this));
	gridLayout->addWidget(new QCheckBox("Occluded or obstructed",this));
	gridLayout->setVerticalSpacing(2.f);
	setLayout(gridLayout);
	{
	  QFont font = this->font(); font.setPointSize(9); this->setFont(font);
	  for (int ridx=0;ridx<gridLayout->rowCount();ridx++){
		((QCheckBox*)gridLayout->itemAtPosition(ridx,0)->widget())->setFont(font);
	  }
	}
  }
  ~ObjectStatusDialog(){}

  void clearSelection();
protected:
  void resizeEvent(QResizeEvent * evt){
	// QGridLayout * gridLayout = (QGridLayout*)layout();
	// if (gridLayout->rowCount()>0){
	//   ((QCheckBox*)gridLayout->itemAtPosition(0,0)->widget())->setChecked(0);
	// }
  }
};

#endif // __OBJECTDIALOG_H__


