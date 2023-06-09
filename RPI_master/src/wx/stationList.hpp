#ifndef STATION_LIST_HPP
#define STATION_LIST_HPP

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/gbsizer.h>
#include <memory>
#include <map>
#include <vector>

#include "numericInputFrame.hpp"

class stationList : public wxFrame
{
public:
    stationList(const wxString &title, std::vector<short> workstations);

    void SetCellValue(int row, int col, const wxString &value);
    const wxString getCellValue(int row, int col);
    void createButtons(int workstation);
    void removeButtons(int workstation);
    void showButtons(int workstation);
    void OnButtonYesClick(wxCommandEvent &event);
    void OnButtonNoClick(wxCommandEvent &event);

    struct buttonHolder
    {
        wxButton *button_OK;
        wxButton *button_CANCEL;
        std::shared_ptr<short> data;
    };

    enum DockingStatus
    {
        IDLE = 0,
        FINAL_MESSAGE_RECEIVED = 1,
        DOCKING_ACCEPTED_WX = 2,
        DOCKING_CANCELLED_WX = 3,
        DOCKED = 4
    };

    struct productStatus
    {
        std::string productName;
        DockingStatus dockingStatus;
    };

    std::map<short, productStatus> statusList;
    std::map<short, short> workstationToRow;
    std::vector<short> subscribedWorkstations;
    NumericInputFrame *inputFrame;

    static const short FRAME_ID = 10;

    const std::string cellvalueOnDocked = "DOCKED";
    const std::string cellvalueOnDockHandling = "HANDLING DOCKING";
    const std::string cellvalueOnDockCancelling = "CANCELLING DOCKING";
    const std::string cellvalueOnUndocked = "UNDOCKED";
    const std::string cellvalueOnDockRequest = "DOCK REQUEST";

    const short WORKSTATION_COLUMN = 0;
    const short STATUS_COLUMN = 1;
    const short PRODUCT_COLUMN = 2;
    const short BUTTON_COLUMN = 3;

private:
    wxGrid *grid;
    wxPanel *panel;
    wxBoxSizer *sizer;
    wxBoxSizer *buttonSizer;

    std::map<short, buttonHolder> workstationButtons;
    wxDECLARE_EVENT_TABLE();
};

#endif // STATION_LIST_HPP
