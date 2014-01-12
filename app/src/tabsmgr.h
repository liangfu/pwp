/**
 * @file   tabsmgr.h
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Fri Jan 10 14:58:38 2014
 * 
 * @brief  
 * 
 * 
 */
#ifndef __TABS_MANAGER_H__
#define __TABS_MANAGER_H__

// #include "wx/wx.h"
#include "canvas.h"

// simple test event handler class
class EventHandler : public wxEvtHandler
{
public:
    EventHandler(unsigned numChild) : m_numChild(numChild) { }
private:
    void OnRefresh(wxCommandEvent& event)
    {
        wxLogMessage("Child #%u refreshed.", m_numChild);
        event.Skip();
    }
    const unsigned m_numChild;
    // DECLARE_EVENT_TABLE()
    // wxDECLARE_NO_COPY_CLASS(EventHandler);
};

// class MyChild : public wxMDIChildFrame
class MyChild : public wxPanel
{
public:
  // MyChild(wxMDIParentFrame *parent);
  MyChild(wxFrame *parent);
  virtual ~MyChild();

  // unsigned int GetChildrenCount() { return ms_numChildren; }
  unsigned int ms_numChildren;
  int LoadFile(wxString fname);
  wxBitmap * pixmap;

private:
  void OnActivate(wxActivateEvent& event);

  void OnRefresh(wxCommandEvent& event);
  void OnUpdateRefresh(wxUpdateUIEvent& event);
  void OnChangePosition(wxCommandEvent& event);
  void OnChangeSize(wxCommandEvent& event);
  void OnClose(wxCommandEvent& event);
  void OnSize(wxSizeEvent& event);
  void OnMove(wxMoveEvent& event);
  void OnCloseWindow(wxCloseEvent& event);

  
  MyCanvas *m_canvas;

  // DECLARE_EVENT_TABLE()
};

#endif // __TABS_MANAGER_H__
