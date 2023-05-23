#include "setWorkspaceState.hpp"
#include "canTranslator.hpp"
#include "numericInputFrame.hpp"
#include "idleState.hpp"
#include "procesStatus.hpp"

#include <thread>
#include <chrono>

void setWorkspaceState::f_entry()
{
    std::cout << "Entered set workspace state" << std::endl;

    frame = dynamic_cast<NumericInputFrame *>(wxWindow::FindWindowById(NumericInputFrame::FRAME_ID));

    if (frame == nullptr)
    {
        wxPoint framePos(100, 100); // position of the frame
        wxSize frameSize(300, 150); // size of the frame
        frame = new NumericInputFrame(NULL, NumericInputFrame::FRAME_ID, "Numeric Input Frame", framePos, frameSize, wxDEFAULT_FRAME_STYLE);
        frame->Show();
    }
    else
    {
        frame->resetFrame();
    }
}

setWorkspaceState::setWorkspaceState()
{
}

void setWorkspaceState::f_do()
{
}

void setWorkspaceState::f_exit()
{
    newWs = frame->newWs;
    std::cout << "set workspace to " << newWs << std::endl;
    std::vector<uint8_t> data;
    data.push_back(newWs);

    this->context_->canbus.sendMessage(0, canTranslator::MSG_WS_RESPONSE, data);
    frame->valueGiven = false;
    frame->newWs = 0;
}

bool setWorkspaceState::checkAllTriggers()
{

    if (triggerIntegerReceived())
    {
        return true;
    }

    return false;
}

bool setWorkspaceState::triggerIntegerReceived()
{

    if (frame->valueGiven)
    {
        this->context_->TransitionTo(new idleState);
        return true;
    }

    return false;
}
