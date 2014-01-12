/**
 * @file   canvas.h
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Thu Jan  9 16:38:39 2014
 * 
 * @brief  
 * 
 * 
 */
#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "wx/wx.h"
#include "compvis.h"

// class MyCanvas : public wxScrolledWindow
class MyCanvas : public wxWindow
{

  wxBitmap * pixmap;
  void OnResize(wxSizeEvent & evt)
  {
	//Refresh();
	evt.Skip();
  }

  void OnEvent(wxMouseEvent & event);

  wxString m_text;

  bool m_dirty;

  // DECLARE_EVENT_TABLE()

public:
  MyCanvas(wxWindow *parent, const wxPoint& pos, const wxSize& size);
  virtual void OnDraw(wxDC& dc);

  bool IsDirty() const { return m_dirty; }

  void SetText(const wxString& text) { m_text = text; Refresh(); }

  void Display(wxBitmap pixmap)
  {
	wxClientDC dc(this);
	PrepareDC(dc);
	wxSize winsize=GetSize();
	wxSize imgsize=pixmap.GetSize();
	if ( (winsize.GetWidth() <imgsize.GetWidth()) ||
		 (winsize.GetHeight()<imgsize.GetHeight()) )
	{
	  wxImage img=pixmap.ConvertToImage();
	  float xratio=float(imgsize.GetWidth())/float(winsize.GetWidth());
	  float yratio=float(imgsize.GetHeight())/float(winsize.GetHeight());
	  float ratio=1./MAX(xratio,yratio);
	  int w=cvFloor(imgsize.GetWidth()*ratio);
	  int h=cvFloor(imgsize.GetHeight()*ratio);
	  int xloc=cvFloor((winsize.GetWidth()-w)/2.);
	  int yloc=cvFloor((winsize.GetHeight()-h)/2.);
	  wxImage img_re=img.Scale(w,h);
	  dc.DrawBitmap(wxBitmap(img_re),wxPoint(xloc,yloc));
	}else{
	  wxImage img=pixmap.ConvertToImage();
	  int w=imgsize.GetWidth();
	  int h=imgsize.GetHeight();
	  int xloc=cvFloor((winsize.GetWidth()-w)/2.);
	  int yloc=cvFloor((winsize.GetHeight()-h)/2.);
	  wxImage img_re=img.Scale(w,h);
	  dc.Clear();
	  dc.DrawBitmap(wxBitmap(img_re),wxPoint(xloc,yloc));
	}
  }

};

#endif // __CANVAS_H__



