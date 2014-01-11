/**
 * @file   mainwindow.cpp
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Thu Jan  9 16:38:05 2014
 * 
 * @brief  
 * 
 * 
 */

#include "mainwindow.h"

#include "../res/sample.xpm"
#include "../res/bitmaps/new.xpm"
#include "../res/bitmaps/open.xpm"
#include "../res/bitmaps/save.xpm"
#include "../res/bitmaps/copy.xpm"
#include "../res/bitmaps/cut.xpm"
#include "../res/bitmaps/paste.xpm"
#include "../res/bitmaps/print.xpm"
#include "../res/bitmaps/help.xpm"

#include "../res/bitmaps/go-next.xpm"
#include "../res/bitmaps/go-previous.xpm"
#include "../res/bitmaps/zoom-fit-best.xpm"
#include "../res/bitmaps/zoom-in.xpm"
#include "../res/bitmaps/zoom-out.xpm"
#include "../res/bitmaps/zoom-original.xpm"
#include "../res/bitmaps/object-rotate-left.xpm"
#include "../res/bitmaps/object-rotate-right.xpm"

// menu items ids
enum
{
    MDI_FULLSCREEN = 100,
    MDI_REFRESH,
    MDI_CHANGE_TITLE,
    MDI_CHANGE_POSITION,
    MDI_CHANGE_SIZE
};

// BEGIN_EVENT_TABLE(MyFrame, wxMDIParentFrame)
//     EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
//     EVT_MENU(wxID_NEW, MyFrame::OnNewWindow)
//     EVT_MENU(MDI_FULLSCREEN, MyFrame::OnFullScreen)
//     EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
//     EVT_MENU(wxID_CLOSE_ALL, MyFrame::OnCloseAll)
//     EVT_CLOSE(MyFrame::OnClose)
// END_EVENT_TABLE()
// BEGIN_EVENT_TABLE(MyChild, wxMDIChildFrame)
//     EVT_MENU(wxID_CLOSE, MyChild::OnClose)
//     EVT_MENU(MDI_REFRESH, MyChild::OnRefresh)
//     EVT_MENU(MDI_CHANGE_POSITION, MyChild::OnChangePosition)
//     EVT_MENU(MDI_CHANGE_SIZE, MyChild::OnChangeSize)
//     EVT_SIZE(MyChild::OnSize)
//     EVT_MOVE(MyChild::OnMove)
//     EVT_CLOSE(MyChild::OnCloseWindow)
// END_EVENT_TABLE()

// ---------------------------------------------------------------------------
// MyFrame
// ---------------------------------------------------------------------------

// Define my frame constructor
MyFrame::MyFrame():
  wxMDIParentFrame(NULL, wxID_ANY, "CompVis Demo", // wxDefaultPosition
				   wxPoint(200,200), wxSize(640,480))
{
  SetIcon(wxICON(sample));

  // Make a menubar

  // Associate the menu bar with the frame
  SetMenuBar(CreateMainMenubar());

  // This shows that the standard window menu may be customized:

  CreateStatusBar();

  // m_textWindow = new wxTextCtrl(this, wxID_ANY, "A help window",
  // 								wxDefaultPosition, wxDefaultSize,
  // 								wxTE_MULTILINE | wxSUNKEN_BORDER);

  // CreateToolBar(wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL);
  CreateToolBar(wxTB_HORIZONTAL|wxTB_HORZ_TEXT);
  InitToolBar(GetToolBar());

  // connect it only now, after creating m_textWindow
  Connect(wxEVT_SIZE, wxSizeEventHandler(MyFrame::OnSize));
  //Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnQuit, this, wxID_EXIT);
  Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::OnQuit));
  //Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnOpen, this, wxID_OPEN);
  Connect(wxID_OPEN,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::OnOpen));
  //Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnAbout, this, wxID_ABOUT);
  Connect(wxID_ABOUT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::OnAbout));
}

MyFrame::~MyFrame()
{
  // and disconnect it to prevent accessing already deleted m_textWindow in
  // the size event handler if it's called during destruction
  Disconnect(wxEVT_SIZE, wxSizeEventHandler(MyFrame::OnSize));
  Disconnect(wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::OnQuit));
}

wxMenuBar *MyFrame::CreateMainMenubar()
{
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(wxID_OPEN, "&Open file\tCtrl-O", "Open a file");
  menuFile->Append(wxID_EXIT, "&Exit\tCtrl-Q", "Quit the program");
  wxMenu *menuEdit = new wxMenu;
  menuEdit->Append(wxID_UNDO, "&Undo\tCtrl-Z", "Undo previous operation");
  wxMenu *menuView = new wxMenu;
  menuView->Append(0xff, "&Toolbar", "Display toolbar");
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT, "&About\tF1");

  wxMenuBar *mbar = new wxMenuBar;
  mbar->Append(menuFile, "&File");
  mbar->Append(menuEdit, "&Edit");
  mbar->Append(menuView, "&View");
  mbar->Append(menuHelp, "&Help");

  return mbar;
}

void MyFrame::OnOpen(wxCommandEvent& event)
{
  wxFileDialog* OpenDialog =
	new wxFileDialog(this, "Choose a file to open", wxEmptyString, wxEmptyString,
					 "Image files (*.png,*.jpg)|*.png;*.jpg|"
					 "Text files (*.txt)|*.txt|"
					 "C++ Source Files (*.cpp, *.cxx)|*.cpp;*.cxx|"
					 "C Source files (*.c)|*.c|"
					 "C header files (*.h)|*.h", wxFD_OPEN, wxDefaultPosition);

  // Creates a "open file" dialog with 4 file types
  if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
  {
	wxString currpath = OpenDialog->GetPath();
	// Sets our current document to the file the user selected
	// MainEditBox->LoadFile(currpath); 
	SetTitle(wxString("Edit - ") << OpenDialog->GetFilename()); 
  }

  // Clean up after ourselves
  OpenDialog->Destroy();
}

void MyFrame::OnClose(wxCloseEvent& event)
{
  // unsigned int numChildren = MyChild::GetChildrenCount();
  // if ( event.CanVeto() && (numChildren > 0) )
  // {
  // 	wxString msg;
  // 	msg.Printf("%d windows still open, close anyhow?", numChildren);
  // 	if ( wxMessageBox(msg, "Please confirm",
  // 					  wxICON_QUESTION | wxYES_NO) != wxYES )
  // 	{
  // 	  event.Veto();
  // 	  return;
  // 	}
  // }

  event.Skip();
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close();
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
  (void)wxMessageBox("wxWidgets 2.0 MDI Demo\n"
					 "Author: Julian Smart (c) 1997\n"
					 "Usage: mdi.exe", "About MDI Demo");
}

void MyFrame::OnNewWindow(wxCommandEvent& WXUNUSED(event) )
{
  // create and show another child frame
  // MyChild * subframe = new MyChild(this);
  // subframe->Show(true);
}

void MyFrame::OnFullScreen(wxCommandEvent& event)
{
  // ShowFullScreen(event.IsChecked());
}

void MyFrame::OnCloseAll(wxCommandEvent& WXUNUSED(event))
{
  wxWindowList::const_iterator iter;
  for ( iter = GetChildren().begin(); iter != GetChildren().end(); ++iter )
  {
	if ( wxDynamicCast(*iter, wxMDIChildFrame) ) { (*iter)->Close(); }
  }
}

void MyFrame::OnSize(wxSizeEvent& event)
{
  int w, h;
  GetClientSize(&w, &h);

  // m_textWindow->SetSize(0, 0, 200, h);
  GetClientWindow()->SetSize(200, 0, w - 200, h);

  event.Skip();
}

void MyFrame::InitToolBar(wxToolBar* toolBar)
{
  // wxBitmap bitmaps[8];
  // bitmaps[0] = wxBitmap( new_xpm );
  // bitmaps[1] = wxBitmap( open_xpm );
  // bitmaps[2] = wxBitmap( save_xpm );
  // bitmaps[3] = wxBitmap( copy_xpm );
  // bitmaps[4] = wxBitmap( cut_xpm );
  // bitmaps[5] = wxBitmap( paste_xpm );
  // bitmaps[6] = wxBitmap( print_xpm );
  // bitmaps[7] = wxBitmap( help_xpm );
  // toolBar->AddTool(wxID_NEW, "New", bitmaps[0], "New file");
  // toolBar->AddTool(1, "Open", bitmaps[1], "Open file");
  // toolBar->AddTool(2, "Save", bitmaps[2], "Save file");
  // toolBar->AddSeparator();
  // toolBar->AddTool(3, "Copy", bitmaps[3], "Copy");
  // toolBar->AddTool(4, "Cut", bitmaps[4], "Cut");
  // toolBar->AddTool(5, "Paste", bitmaps[5], "Paste");
  // toolBar->AddSeparator();
  // toolBar->AddTool(6, "Print", bitmaps[6], "Print");
  // toolBar->AddSeparator();
  // toolBar->AddTool(wxID_ABOUT, "About", bitmaps[7], "Help");

  // #include "../res/bitmaps/go-next.xpm"
  // #include "../res/bitmaps/go-previous.xpm"
  // #include "../res/bitmaps/zoom-fit-best.xpm"
  // #include "../res/bitmaps/zoom-in.xpm"
  // #include "../res/bitmaps/zoom-out.xpm"
  // #include "../res/bitmaps/zoom-original.xpm"
  // #include "../res/bitmaps/object-rotate-left.xpm"
  // #include "../res/bitmaps/object-rotate-right.xpm"
  wxBitmap bitmaps[8];
  bitmaps[0] = wxBitmap( go_previous_xpm );
  bitmaps[1] = wxBitmap( go_next_xpm );
  bitmaps[2] = wxBitmap( zoom_fit_best_xpm );
  bitmaps[3] = wxBitmap( zoom_in_xpm );
  bitmaps[4] = wxBitmap( zoom_out_xpm );
  bitmaps[5] = wxBitmap( zoom_original_xpm );
  bitmaps[6] = wxBitmap( object_rotate_left_xpm );
  bitmaps[7] = wxBitmap( object_rotate_right_xpm );
  toolBar->AddTool(0, "Previous", bitmaps[0], "New file");
  toolBar->AddTool(1, "Next", bitmaps[1], "Open file");
  toolBar->AddSeparator();
  toolBar->AddTool(2, "", bitmaps[2], "Best fit");
  toolBar->AddTool(3, "", bitmaps[3], "Zoom in");
  toolBar->AddTool(4, "", bitmaps[4], "Zoom out");
  toolBar->AddTool(5, "", bitmaps[5], "Original size");
  toolBar->AddSeparator();
  toolBar->AddTool(6, "", bitmaps[6], "Rotate left");
  toolBar->AddTool(7, "", bitmaps[7], "Rotate right");

  toolBar->Realize();

  MyChild * subframe0 = new MyChild(this);
  subframe0->Show(true);
  MyChild * subframe1 = new MyChild(this);
  subframe1->Show(true);
}

