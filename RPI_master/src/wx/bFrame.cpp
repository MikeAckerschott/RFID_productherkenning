#include "bFrame.hpp"
#include "procesStatus.hpp"

bFrame::bFrame(const short workspace)
    : wxFrame(NULL, wxID_ANY, "Workspace: " + std::to_string(workspace), wxPoint(0, 4 * 200), wxSize(400, 200)), workspace(workspace)
{
    panel = new wxPanel(this);
    sizer = new wxBoxSizer(wxVERTICAL);

    // Add text field
    wxString text = "Workstation " + std::to_string(workspace) + ": EMPTY";
    wxStaticText *label = new wxStaticText(panel, TEXTFIELD, text, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    sizer->Add(label, wxSizerFlags().Center().Border(wxALL, 5));

    panel->SetSizer(sizer);
}

void bFrame::removeButtons()
{
    wxButton *button_ok = wxDynamicCast(this->FindWindow(bFrame::BUTTON_OK), wxButton);
                            
    wxButton *button_cancel = wxDynamicCast(this->FindWindow(bFrame::BUTTON_CANCEL), wxButton);

    if (button_ok != NULL)
    {
        button_ok->Destroy();
    }
    if (button_cancel != NULL)
    {
        button_cancel->Destroy();
    }
}

void bFrame::setDockingText()
{
    wxStaticText *text = wxDynamicCast(this->FindWindow(bFrame::TEXTFIELD), wxStaticText);

    if (text != NULL)
    {
        // text->SetLabel("Product: " + //procesStatus::GetInstance()->status[workspace].productName + " is docked");
        // sizer->Fit(this);
        // "Dock "+//procesStatus::GetInstance()->status[workspace].productName+"on workstation: "+std::to_string(workspace);
    }
}

void bFrame::setDockingRequestText()
{
    wxStaticText *text = wxDynamicCast(this->FindWindow(bFrame::TEXTFIELD), wxStaticText);

    if (text != NULL)
    {
        // text->SetLabel("Product: " + //procesStatus::GetInstance()->status[workspace].productName + " is docked");
        // text->SetLabel("Dock product: "+ //procesStatus::GetInstance()->status[workspace].productName);
        // sizer->Fit(this);
        // "Dock "+//procesStatus::GetInstance()->status[workspace].productName+"on workstation: "+std::to_string(workspace);
    }
}

void bFrame::setUndockingText()
{
    wxStaticText *text = wxDynamicCast(this->FindWindow(bFrame::TEXTFIELD), wxStaticText);

    if (text != NULL)
    {
        // text->SetLabel("Workstation " + std::to_string(workspace) + ": EMPTY");
        // sizer->Fit(this);
        // "Dock "+//procesStatus::GetInstance()->status[workspace].productName+"on workstation: "+std::to_string(workspace);
    }
}

void bFrame::OnButtonYesClick(wxCommandEvent &event)
{
    std::cout << "Clicked yes for workspace: " << workspace << std::endl;
    // //procesStatus::GetInstance()->status[workspace].dockingStatus = //procesStatus::DOCKING_ACCEPTED_WX;
    // removeButtons(workspace);
    // setDockingText();
    // sizer->Fit();

    // Close();
    // wxTheApp->ExitMainLoop(); // exit the event loop
}

void bFrame::OnButtonNoClick(wxCommandEvent &event)
{
    std::cout << "Clicked no!" << std::endl;
    //procesStatus::GetInstance()->status[workspace].dockingStatus = //procesStatus::DOCKING_CANCELLED_WX;
    // removeButtons();
    // setUndockingText();
    // sizer->Fit();
    // Close();
    // wxTheApp->ExitMainLoop(); // exit the event loop
}