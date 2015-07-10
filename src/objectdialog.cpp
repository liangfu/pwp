/** -*- c++ -*- 
 *
 * \file   objectdialog.cpp
 * \date   Thu May 21 13:32:56 2015
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
 * \brief  implement of object selection dialogs;
 */
 
#include "objectdialog.h"

void ObjectListDialog::clearSelection()
{
  QGridLayout * gridLayout = (QGridLayout*)layout();
  for (int ridx=0;ridx<gridLayout->rowCount();ridx++){
	((QRadioButton*)gridLayout->itemAtPosition(ridx,0)->widget())->setChecked(0);
  }
  if (!m_buttonGroup){
	m_buttonGroup = new QButtonGroup(this);
	for (int ridx=0;ridx<gridLayout->rowCount();ridx++){
	  m_buttonGroup->addButton((QRadioButton*)gridLayout->itemAtPosition(ridx,0)->widget());
	}
	m_buttonGroup->setExclusive(1);
	connect(m_buttonGroup,SIGNAL(buttonPressed(int)),
			this,SLOT(buttonPressed(int)),Qt::UniqueConnection);
  }
}
