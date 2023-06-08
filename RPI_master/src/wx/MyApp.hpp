#ifndef MYAPP_HPP_
#define MYAPP_HPP_

// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <bcm2835.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <thread>

#include "context.hpp"
#include "state.hpp"
#include "idleState.hpp"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();

private:
    void OnTimer(wxTimerEvent &event);

    wxTimer m_timer;
    Context *m_context;
};

wxIMPLEMENT_APP(MyApp);

#endif /* MYAPP_HPP_ */