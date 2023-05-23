#include "awaitStartupResponseState.hpp"
#include "readMessageState.hpp"
#include "setWorkspaceState.hpp"
#include "canTranslator.hpp"
#include "procesStatus.hpp"
#include "bFrame.hpp"
#include "stationList.hpp"
#include "numericInputFrame.hpp"

// TODO remove after testing
#include <bcm2835.h>
#include <thread>
#include <algorithm> // for std::find
#include <iterator>  // for std::begin, std::end

void awaitStartupResponseState::f_entry()
{
    std::cout << "Entered awaitStartupResponseState" << std::endl;
    context_->canbus.sendMessage(0, canTranslator::MSG_START);

    // using namespace std::chrono;
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

awaitStartupResponseState::awaitStartupResponseState()
{
}

void awaitStartupResponseState::f_do()
{
    short workspace = 0;
    

    if (context_->canbus.awaitStartupMessage(&workspace))
    {
        std::cout<<"subscribed: "<<workspace<<std::endl;
        if (subscribedWorkstations.size() == 0)
        {
            // std::cout << "empty but added" << *workspace << std::endl;
            subscribedWorkstations.push_back(workspace);
        }
        else if (std::find(std::begin(subscribedWorkstations), std::end(subscribedWorkstations), workspace) == std::end(subscribedWorkstations))
        {
            // std::cout << "added" << *workspace << std::endl;
            subscribedWorkstations.push_back(workspace);
        }
        else
        {
            std::cout << "DUPLICATE" << std::endl;
        }
    }
}

void awaitStartupResponseState::f_exit()
{
    // std::cout << procesStatus::GetInstance()->subscribedWorkstations.size() << std::endl;

    // for (int i = 0; i < procesStatus::GetInstance()->subscribedWorkstations.size(); ++i)
    // {
    //     std::cout<<"creating new frame with workstation: "<<procesStatus::GetInstance()->subscribedWorkstations.at(i)<<std::endl;
    //     bFrame *frame = new bFrame(procesStatus::GetInstance()->subscribedWorkstations.at(i));
    //     frame->Show();
    //     procesStatus::GetInstance()->workstationButtons[procesStatus::GetInstance()->subscribedWorkstations.at(i)] = frame;
    // }

    stationList *frame = new stationList("TEST", subscribedWorkstations);
    // frame->setButtons(1);
    frame->Show();

    NumericInputFrame *setWorkstationFrame = dynamic_cast<NumericInputFrame *>(wxWindow::FindWindowById(NumericInputFrame::FRAME_ID));
    if(setWorkstationFrame != nullptr){
        setWorkstationFrame->Destroy();
    }
}

bool awaitStartupResponseState::checkAllTriggers()
{
    // this->context_->TransitionTo(new readMessageState);
    // return true;
    std::chrono::milliseconds currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - ms);
    if (duration_ms.count() > 3000)
    {
        this->context_->TransitionTo(new readMessageState);
        return true;
    }
    return false;
}
