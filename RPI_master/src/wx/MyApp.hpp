#ifndef MYAPP_HPP_
#define MYAPP_HPP_

// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "context.hpp"
#include "state.hpp"
#include "idleState.hpp"

#include <bcm2835.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <thread>

#include "bFrame.hpp"
#include "context.hpp"
#include "idleState.hpp"
#include "numericInputFrame.hpp"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();

private:
    void OnTimer(wxTimerEvent &event);
    void OnButtonClick(wxCommandEvent &event);

    wxTimer m_timer;
    Context *m_context;
};

wxBEGIN_EVENT_TABLE(bFrame, wxFrame)
    EVT_BUTTON(wxID_ANY, bFrame::OnButtonYesClick)
        EVT_BUTTON(wxID_ANY, bFrame::OnButtonNoClick)
            wxEND_EVENT_TABLE();

wxIMPLEMENT_APP(MyApp);

#endif /* MYAPP_HPP_ */