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

// class MyCanvas : public wxScrolledWindow
class MyCanvas : public wxWindow
{
public:
    MyCanvas(wxWindow *parent, const wxPoint& pos, const wxSize& size);
    virtual void OnDraw(wxDC& dc);

    bool IsDirty() const { return m_dirty; }

    void SetText(const wxString& text) { m_text = text; Refresh(); }

private:
    void OnEvent(wxMouseEvent& event);

    wxString m_text;

    bool m_dirty;

    DECLARE_EVENT_TABLE()
};

#endif // __CANVAS_H__



