#include "validateIncomingMessageState.hpp"
#include <climits>
#include <sstream>
#include "readMessageState.hpp"
#include "canTranslator.hpp"
#include "bFrame.hpp"
#include "procesStatus.hpp"

void validateIncomingMessageState::f_entry()
{
    // workspace = this->context_->canbus.getStoredWorkspace();
    // std::cout << "Product: " << procesStatus::GetInstance()->status[workspace].productName << " detected at workstation: " << workspace << ". Do you want to dock this product?" << std::endl;

    // bFrame *temp = new bFrame("Dock product: " + this->context_->canbus.productInformation[workspace] + " At workspace: " + std::to_string(workspace), "Yes", "No", &context_->handler);
    // context_->wxFrameBuffer.push_back(temp);
}

validateIncomingMessageState::validateIncomingMessageState()
{
}

// validateIncomingMessageState::validateIncomingMessageState(short workspaceNr):workspaceNr(workspaceNr)
// {
// }

void validateIncomingMessageState::f_do()
{
    // // await button press
    // can_frame msg;
    // if (context_->canbus.mcp2515.readMessage(&msg) == MCP2515::ERROR_OK)
    // {
    //     std::cout << "pushed" << std::endl;
    //     context_->msgBuffer.push_back(msg);
    // }
}

void validateIncomingMessageState::f_exit()
{
    // this->context_->canbus.clearMsgBuffer();
}

bool validateIncomingMessageState::checkAllTriggers()
{
    // if (triggerButtonOkPressed())
    // {
    //     return true;
    // }
    // else if (triggerButtonCancelPressed())
    // {
    //     return true;
    // }
    return false;
}

bool validateIncomingMessageState::triggerButtonOkPressed()
{
    // if (this->context_->button_ok.isButtonPressed())
    // {
    //     // std::vector<uint8_t> data = {workspace};

    //     std::vector<uint8_t> data;
    //     data.push_back(workspace);
    //     context_->canbus.sendMessage(0, canTranslator::MSG_DOCKING_SUCCESFUL, data);
    //     std::cout << "Product: " << procesStatus::GetInstance()->status[workspace].productName << " Succesfully docked on: " << workspace << std::endl;

    //     this->context_->TransitionTo(new readMessageState);

    //     // TODO add extra state that handles the acknowledging and sends information to server?

    //     return true;
    // }
    // return false;
}

bool validateIncomingMessageState::triggerButtonCancelPressed()
{
    // if (this->context_->button_cancel.isButtonPressed())
    // {
    //     std::vector<uint8_t> data;
    //     data.push_back(workspace);
    //     context_->canbus.sendMessage(0, canTranslator::MSG_DOCKING_CANCELLED, data);
    //     procesStatus::GetInstance()->status[workspace].productName = "";
    //     this->context_->TransitionTo(new readMessageState);
    //     std::cout << "Cancelled dock" << std::endl;

    //     // TODO add extra state that handles the acknowledging and sends information to server?

    //     return true;
    // }
    return false;
}