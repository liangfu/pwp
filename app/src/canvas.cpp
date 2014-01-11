// ---------------------------------------------------------------------------
// MyCanvas
// ---------------------------------------------------------------------------

#include "canvas.h"


// Define a constructor for my canvas
MyCanvas::MyCanvas(wxWindow *parent, const wxPoint& pos, const wxSize& size)
        // : wxScrolledWindow(parent, wxID_ANY, pos, size,
        : wxWindow(parent, wxID_ANY, pos, size,
                           wxSUNKEN_BORDER |
                           wxNO_FULL_REPAINT_ON_RESIZE |
                           wxVSCROLL | wxHSCROLL)
{
    SetBackgroundColour(*wxWHITE);
    // SetCursor(wxCursor(wxCURSOR_PENCIL));

    // SetScrollbars(20, 20, 50, 50);

    m_dirty = false;
}

// Define the repainting behaviour
void MyCanvas::OnDraw(wxDC& dc)
{
  if ( !m_text.empty() ) { dc.DrawText(m_text, 10, 10); }

  dc.SetFont(*wxSWISS_FONT);
  dc.SetPen(*wxGREEN_PEN);
  dc.DrawLine(0, 0, 200, 200);
  dc.DrawLine(200, 0, 0, 200);

  dc.SetBrush(*wxCYAN_BRUSH);
  dc.SetPen(*wxRED_PEN);
  dc.DrawRectangle(100, 100, 100, 50);
  dc.DrawRoundedRectangle(150, 150, 100, 50, 20);

  dc.DrawEllipse(250, 250, 100, 50);
  dc.DrawLine(50, 230, 200, 230);
  dc.DrawText("This is a test string", 50, 230);

  wxPoint points[3];
  points[0].x = 200; points[0].y = 300;
  points[1].x = 100; points[1].y = 400;
  points[2].x = 300; points[2].y = 400;

  dc.DrawPolygon(3, points);
}

// This implements a tiny doodling program! Drag the mouse using the left
// button.
void MyCanvas::OnEvent(wxMouseEvent& event)
{
  wxClientDC dc(this);
  PrepareDC(dc);

  wxPoint pt(event.GetLogicalPosition(dc));

  static long xpos = -1;
  static long ypos = -1;

  if (xpos > -1 && ypos > -1 && event.Dragging())
  {
	dc.SetPen(*wxBLACK_PEN);
	dc.DrawLine(xpos, ypos, pt.x, pt.y);

	m_dirty = true;
  }

  xpos = pt.x;
  ypos = pt.y;
}

