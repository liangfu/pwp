/**
 * @file   _vatool.h
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Fri Aug 22 17:25:40 2014
 * 
 * @brief  
 * 
 * 
 */
#ifndef __VA_TOOL_H__
#define __VA_TOOL_H__

#include <QtCore>
#include <QtGui>

#include "cxcore.h"
#include "highgui.h"

namespace Qt{
  enum InteractState{NoInteract=0,NewObject=1,MoveObject=2,ResizeObject=3};
  enum SelectionState{SelectionDenied=0,SelectionReady=1,SelectionFinished=2};
}

#endif // __VA_TOOL_H__
