#include "MyApp.hpp"

bool MyApp::OnInit()
{
    if (!bcm2835_init())
        return false;

    m_context = new Context(new idleState);

    m_timer.Bind(wxEVT_TIMER, &MyApp::OnTimer, this);
    m_timer.Start(1); // 1 milisecond interval



    return true;
}

int MyApp::OnExit()
{
    m_timer.Stop();
    delete m_context;
    return wxApp::OnExit();
}

void MyApp::OnTimer(wxTimerEvent &event)
{
    m_context->f_do();
    m_context->checkAllTriggers();
}