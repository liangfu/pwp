/////////////////////////////////////////////////////////////////////////////
// Name:        mdi.cpp
// Purpose:     MDI sample
// Author:      Julian Smart
// Modified by: 2008-10-31 Vadim Zeitlin: big clean up
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) 1997 Julian Smart
//              (c) 2008 Vadim Zeitlin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".

// #include "wx/wxprec.h"
// #ifndef WX_PRECOMP
// #include "wx/wx.h"
// #include "wx/mdi.h"
// #endif

// #include "wx/toolbar.h"
// #include "mdi.h"

#include "mainwindow.h"
#include "canvas.h"

// ---------------------------------------------------------------------------
// event tables
// ---------------------------------------------------------------------------


// Note that wxID_NEW and wxID_ABOUT commands get passed
// to the parent window for processing, so no need to
// duplicate event handlers here.


// BEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
//     EVT_MOUSE_EVENTS(MyCanvas::OnEvent)
// END_EVENT_TABLE()
BEGIN_EVENT_TABLE(MyCanvas, wxWindow)
    EVT_MOUSE_EVENTS(MyCanvas::OnEvent)
END_EVENT_TABLE()

// ===========================================================================
// implementation
// ===========================================================================


// Define a new application
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// ---------------------------------------------------------------------------
// MyApp
// ---------------------------------------------------------------------------

// Initialise this in OnInit, not statically
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    // Create the main frame window

    MyFrame *frame = new MyFrame;

    frame->Show(true);

    return true;
}

int main(int argc, char * argv[])
{
  wxApp::SetInstance( new MyApp() );
  wxEntryStart( argc, argv );
  wxTheApp->OnInit();

  // you can create top level-windows here or in OnInit()
	
  // do your testing here

  wxTheApp->OnRun();
  wxTheApp->OnExit();
  wxEntryCleanup();
  return 0;
}
