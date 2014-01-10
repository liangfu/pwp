/**
 * @file   mainwindow.h
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Thu Jan  9 16:37:56 2014
 * 
 * @brief  
 * 
 * 
 */

#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "tabsmgr.h"

// Define a new frame
class MyFrame : public wxMDIParentFrame
{
public:
  MyFrame();
  virtual ~MyFrame();

  wxMenuBar * CreateMainMenubar();

  int m_numtabs;
  MyChild * m_tabs;

private:
  void InitToolBar(wxToolBar* toolBar);

  void OnSize(wxSizeEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnNewWindow(wxCommandEvent& event);
  void OnFullScreen(wxCommandEvent& event);
  void OnQuit(wxCommandEvent& event);
  void OnCloseAll(wxCommandEvent& event);

  void OnClose(wxCloseEvent& event);

  wxTextCtrl *m_textWindow;

  // DECLARE_EVENT_TABLE()
};


#endif // __MAIN_WINDOW_H__
