#include "readMessageState.hpp"
#include "stationList.hpp"

// TODO remove after testing
#include <bcm2835.h>
#include <thread>
#include <chrono>

void readMessageState::f_entry()
{
    std::cout << "Entered read message state" << std::endl;
    frame = dynamic_cast<stationList *>(wxWindow::FindWindowById(stationList::FRAME_ID));
}

readMessageState::readMessageState() : frame(nullptr)
{
}

void readMessageState::f_do()
{
    canTranslator::MSG_TYPE type;
    short workspace = 0;
    if (context_->canbus.getIncomingMessageInfo(&type, &workspace))
    {
        std::cout << type << std::endl;
        short row = frame->workstationToRow[workspace];
        switch (type)
        {
        case canTranslator::MSG_DOCKED_SENDING:
        {
            frame->SetCellValue(row, frame->PRODUCT_COLUMN, frame->getCellValue(row, frame->PRODUCT_COLUMN) + context_->canbus.canframeToProductInfo(context_->canbus.getStoredMessage()));
            break;
        }
        case canTranslator::MSG_DOCKED_DONE:

        {
            frame->SetCellValue(row, frame->PRODUCT_COLUMN, frame->getCellValue(row, frame->PRODUCT_COLUMN) + context_->canbus.canframeToProductInfo(context_->canbus.getStoredMessage()));
            frame->SetCellValue(row, frame->STATUS_COLUMN, frame->cellvalueOnDockRequest);
            frame->showButtons(workspace);

            break;
        }

        case canTranslator::MSG_UNDOCKED:
        {
            frame->SetCellValue(row, frame->PRODUCT_COLUMN, "");
            frame->SetCellValue(row, frame->STATUS_COLUMN, frame->cellvalueOnUndocked);
            break;
        }
        }
    }

    bool buttonOkPressed = context_->button_ok.isButtonPressed();
    bool buttonCancelPressed = context_->button_cancel.isButtonPressed();

    for (int i = 0; i < frame->subscribedWorkstations.size(); ++i)
    {
        short row = frame->workstationToRow[frame->subscribedWorkstations.at(i)];

        if ((frame->getCellValue(row, frame->STATUS_COLUMN) == frame->cellvalueOnDockRequest && buttonOkPressed) || frame->getCellValue(row, frame->STATUS_COLUMN) == frame->cellvalueOnDockHandling)
        {
            std::cout << "DOCK" << std::endl;

            frame->SetCellValue(row, frame->STATUS_COLUMN, frame->cellvalueOnDocked);
            frame->removeButtons(frame->subscribedWorkstations.at(i));

            std::cout << "remove buttons from row: " << frame->subscribedWorkstations.at(i) << std::endl;

            std::vector<uint8_t> data;
            data.push_back(frame->subscribedWorkstations.at(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            context_->canbus.sendMessage(0, canTranslator::MSG_DOCKING_SUCCESFUL, data);
        }
        else if ((frame->getCellValue(row, frame->STATUS_COLUMN) == frame->cellvalueOnDockRequest && buttonCancelPressed) || frame->getCellValue(row, frame->STATUS_COLUMN) == frame->cellvalueOnDockCancelling)
        {
            std::cout << "CANCEL DOCK" << std::endl;

            frame->SetCellValue(row, frame->STATUS_COLUMN, frame->cellvalueOnUndocked);
            frame->SetCellValue(row, frame->PRODUCT_COLUMN, "");
            frame->removeButtons(frame->subscribedWorkstations.at(i));

            std::cout << "remove buttons from row: " << row << std::endl;
            std::vector<uint8_t> data;
            data.push_back(frame->subscribedWorkstations.at(i));
            context_->canbus.sendMessage(0, canTranslator::MSG_DOCKING_CANCELLED, data);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

// detect if any of the prompts have been pressed and handle the presses?

void readMessageState::f_exit()
{
}

bool readMessageState::checkAllTriggers()
{
    return false;
}
