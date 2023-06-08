#include "stationList.hpp"

stationList::stationList(const wxString &title, std::vector<short> workstations)
    : wxFrame(NULL, FRAME_ID, title, wxDefaultPosition, wxSize(800, 400)), subscribedWorkstations(workstations)
{
    panel = new wxPanel(this);
    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);
    wxGridBagSizer *gridSizer = new wxGridBagSizer(10, 10);

    // Create the grid control
    grid = new wxGrid(panel, wxID_ANY);
    grid->CreateGrid(workstations.size(), 4); // Set the number of rows and columns

    // Set column labels
    grid->SetColLabelValue(WORKSTATION_COLUMN, "Workstation Number");
    grid->SetColLabelValue(STATUS_COLUMN, "Status");
    grid->SetColLabelValue(PRODUCT_COLUMN, "Productname");
    grid->SetColLabelValue(BUTTON_COLUMN, "Dock?");

    // Set column widths
    grid->SetColSize(WORKSTATION_COLUMN, 150);
    grid->SetColSize(STATUS_COLUMN, 150);
    grid->SetColSize(PRODUCT_COLUMN, 200);
    grid->SetColSize(BUTTON_COLUMN, 150);

    // Disable cell editing
    grid->EnableEditing(false);

    // Add grid to grid sizer
    gridSizer->Add(grid, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND | wxALL, 10);

    // Set initial text in the columns
    for (int i = 0; i < workstations.size(); ++i)
    {
        SetCellValue(i, WORKSTATION_COLUMN, std::to_string(workstations.at(i)));
        SetCellValue(i, STATUS_COLUMN, cellvalueOnUndocked);
        SetCellValue(i, PRODUCT_COLUMN, "");

        workstationToRow[workstations.at(i)] = i;

        productStatus status;
        status.dockingStatus = IDLE;
        status.productName = "";

        statusList[workstations.at(i)] = status;

        createButtons(workstations.at(i));
    }
    // Hide row labels
    grid->HideRowLabels();

    // Add grid sizer to panel sizer
    panelSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 10);

    // Set sizer for the panel
    panel->SetSizer(panelSizer);
    panelSizer->Fit(this);
    Layout();
}

void stationList::SetCellValue(int row, int col, const wxString &value)
{
    if (row >= 0 && row < grid->GetNumberRows() && col >= 0 && col < grid->GetNumberCols())
        grid->SetCellValue(row, col, value);
}

const wxString stationList::getCellValue(int row, int col)
{
    if (row >= 0 && row < grid->GetNumberRows() && col >= 0 && col < grid->GetNumberCols())
    {
        return grid->GetCellValue(row, col);
    }
    return "OUT OF BOUNDS";
}

void stationList::createButtons(int workstation)
{
    int row = workstationToRow[workstation];
    wxButton *lbutton = new wxButton(panel, wxID_ANY, "No", wxPoint(550, 50 + (25 * row)), wxSize(40, 25));
    wxButton *rbutton = new wxButton(panel, wxID_ANY, "Yes", wxPoint(600, 50 + (25 * row)), wxSize(40, 25));

    buttonHolder holder;
    holder.button_OK = rbutton;
    holder.button_CANCEL = lbutton;
    holder.data = std::make_shared<short>(workstation);

    workstationButtons[workstation] = holder;

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(rbutton, 0, wxALL, 5);
    buttonSizer->Add(lbutton, 0, wxALL, 5);

    lbutton->Bind(wxEVT_BUTTON, &stationList::OnButtonNoClick, this);
    rbutton->Bind(wxEVT_BUTTON, &stationList::OnButtonYesClick, this);

    lbutton->SetClientData(static_cast<void *>(holder.data.get()));
    rbutton->SetClientData(static_cast<void *>(holder.data.get()));

    removeButtons(workstation);
}

void stationList::removeButtons(int workstation)
{
    std::cout << "removing buttons for workstation: " << workstation << " on row: " << workstationToRow[workstation] << std::endl;

    workstationButtons[workstation].button_OK->Enable(false);
    workstationButtons[workstation].button_OK->Show(false);

    workstationButtons[workstation].button_CANCEL->Enable(false);
    workstationButtons[workstation].button_CANCEL->Show(false);
}

void stationList::showButtons(int workstation)
{
    workstationButtons[workstation].button_OK->Enable(true);
    workstationButtons[workstation].button_OK->Show(true);

    workstationButtons[workstation].button_CANCEL->Enable(true);
    workstationButtons[workstation].button_CANCEL->Show(true);
}

void stationList::OnButtonYesClick(wxCommandEvent &event)
{
    // Retrieve the client data
    wxButton *button = static_cast<wxButton *>(event.GetEventObject());
    void *clientData = button->GetClientData();

    std::shared_ptr<short> data(
        static_cast<short *>(clientData),
        [](short *ptr) {});

    SetCellValue(workstationToRow[*data], STATUS_COLUMN, cellvalueOnDockHandling);

    removeButtons(*data);
}

void stationList::OnButtonNoClick(wxCommandEvent &event)
{
    // Retrieve the client data
    wxButton *button = static_cast<wxButton *>(event.GetEventObject());
    void *clientData = button->GetClientData();

    std::shared_ptr<short> data(
        static_cast<short *>(clientData),
        [](short *ptr) {});

    SetCellValue(workstationToRow[*data], STATUS_COLUMN, cellvalueOnDockCancelling);
    SetCellValue(workstationToRow[*data], PRODUCT_COLUMN, "");

    removeButtons(*data);
}

wxBEGIN_EVENT_TABLE(stationList, wxFrame)
    wxEND_EVENT_TABLE();
