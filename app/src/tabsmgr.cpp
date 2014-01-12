/**
 * @file   tabsmgr.cpp
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Fri Jan 10 14:58:25 2014
 * 
 * @brief  
 * 
 * 
 */

#include "tabsmgr.h"

#include "../res/chart.xpm"

enum {	wxID_PANEL_REFRESH = wxID_HIGHEST+1};



// MyChild::MyChild(wxMDIParentFrame *parent):
//   wxMDIChildFrame(parent,wxID_ANY,wxString::Format("Child 0"))
MyChild::MyChild(wxFrame *parent):
  wxPanel(parent,wxID_ANY,wxDefaultPosition,parent->GetClientSize()),pixmap(0)
  // wxPanel(parent,wxID_ANY)
{
  m_canvas = new MyCanvas(this, wxPoint(0, 0), GetClientSize());
  wxBoxSizer * sizer=new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(m_canvas,1,wxEXPAND|wxALL,0);
  //sizer->SetSizeHints(this);
  SetSizer(sizer);


  fprintf(stderr,"parent->GetSize(): %d,%d\n",
		  parent->GetSize().GetWidth(),parent->GetSize().GetHeight());
  fprintf(stderr,"parent->GetClientSize(): %d,%d\n",
		  parent->GetClientSize().GetWidth(),parent->GetClientSize().GetHeight());
  fprintf(stderr,"GetClientSize(): %d,%d\n",
		  GetClientSize().GetWidth(),GetClientSize().GetHeight());

  // SetIcon(wxICON(chart));

  // const bool canBeResized = !IsAlwaysMaximized();

  // create our menu bar: it will be shown instead of the main frame one when
  // we're active

  // this should work for MDI frames as well as for normal ones, provided
  // they can be resized at all
  // if ( canBeResized ) {
  // SetSizeHints(100, 100);
  //}

  // test that event handlers pushed on top of MDI children do work (this
  // used to be broken, see #11225)
  PushEventHandler(new EventHandler(ms_numChildren));

  //Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnAbout, this, wxID_ABOUT);
  // Connect(wxID_ABOUT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::OnAbout));
  // Connect(wxID_PANEL_REFRESH,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyChild::OnRefresh));
  Connect(wxEVT_SIZE,wxSizeEventHandler(MyChild::OnSize));
  // Connect(wxEVT_SIZE,wxSizeEventHandler(MyChild::OnSize));
}

MyChild::~MyChild()
{
  PopEventHandler(true);

  ms_numChildren--;
}

int MyChild::LoadFile(wxString fname)
{
  fprintf(stderr,"%s\n",(const char *)fname.c_str());
  if (!pixmap){pixmap=new wxBitmap();}
  *pixmap=wxBitmap(fname,wxBITMAP_TYPE_ANY);
  m_canvas->Display(*pixmap);
}

void MyChild::OnClose(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

void MyChild::OnRefresh(wxCommandEvent& WXUNUSED(event))
{
  if ( m_canvas ) { m_canvas->Refresh(); }
}

void MyChild::OnChangePosition(wxCommandEvent& WXUNUSED(event))
{
  Move(10, 10);
}

void MyChild::OnChangeSize(wxCommandEvent& WXUNUSED(event))
{
  SetClientSize(100, 100);
}

void MyChild::OnActivate(wxActivateEvent& event)
{
  if ( event.GetActive() && m_canvas ) { m_canvas->SetFocus(); }
}

void MyChild::OnMove(wxMoveEvent& event)
{
  // VZ: here everything is totally wrong under MSW, the positions are
  //     different and both wrong (pos2 is off by 2 pixels for me which seems
  //     to be the width of the MDI canvas border)
  wxPoint pos1 = event.GetPosition(),
	pos2 = GetPosition();
  wxLogStatus("position from event: (%d, %d), from frame (%d, %d)",
			  pos1.x, pos1.y, pos2.x, pos2.y);

  event.Skip();
}

void MyChild::OnSize(wxSizeEvent& event)
{
  // VZ: under MSW the size event carries the client size (quite
  //     unexpectedly) *except* for the very first one which has the full
  //     size... what should it really be? TODO: check under wxGTK
  wxSize size1 = event.GetSize(),
	size2 = GetSize(),
	size3 = GetClientSize();
  wxLogStatus("size from event: %dx%d, from frame %dx%d, client %dx%d",
			  size1.x, size1.y, size2.x, size2.y, size3.x, size3.y);

  // m_canvas->SetClientSize(GetClientSize());
  // if (pixmap){m_canvas->Display(*pixmap);}
  

  event.Skip();
}

void MyChild::OnCloseWindow(wxCloseEvent& event)
{
  if ( m_canvas && m_canvas->IsDirty() ) {
	if ( wxMessageBox("Really close?", "Please confirm", wxICON_QUESTION | wxYES_NO) != wxYES ) {
	  event.Veto();
	  return;
	}
  }

  event.Skip();
}

