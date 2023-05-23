#include "numericInputFrame.hpp"

NumericInputFrame::NumericInputFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : wxFrame(parent, id, title, pos, size, style), newWs(0), valueGiven(false)
{
    panel = new wxPanel(this);
    sizer = new wxBoxSizer(wxVERTICAL);

    // Add text field
    textField = new wxTextCtrl(panel, INPUTFIELD, wxEmptyString, wxPoint(50, 50), wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_RIGHT | wxTE_CENTRE);
    textField->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    sizer->Add(textField, wxSizerFlags().Center().Border(wxALL, 5));

    // Add button
    button = new wxButton(panel, BUTTON_OK, "Get Value", wxPoint(50, 200), wxDefaultSize);
    button->Bind(wxEVT_BUTTON, &NumericInputFrame::OnButtonClicked, this);
    sizer->Add(button, wxSizerFlags().Center().Border(wxALL, 5));

    label = nullptr;

    panel->SetSizer(sizer);
}

void NumericInputFrame::OnButtonClicked(wxCommandEvent &event)
{
    wxString value = textField->GetValue();
    if (!value.IsEmpty())
    {
        long numericValue;
        if (value.ToLong(&numericValue))
        {
            // Do something with numericValue
            std::cout << "got value: " << numericValue << std::endl;
            valueGiven = true;
            newWs = numericValue;

            textField->Destroy();
            button->Destroy();

            wxString text = "Set workstation to: " + std::to_string(newWs);
            if (label == nullptr)
            {
                std::cout << "label is nullptr" << std::endl;
                label = new wxStaticText(panel, TEXTFIELD, text, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
                sizer->Add(label, wxSizerFlags().Center().Border(wxALL, 5));
            }
            else
            {
                std::cout << "label isn't nullptr" << std::endl;
                label->SetLabel("TEST  ");
                std::cout << "set label" << std::endl;
            }
        }

        else
        {
            wxMessageBox("Invalid numeric value entered.", "Error", wxOK | wxICON_ERROR, this);
        }
    }
    else
    {
        wxMessageBox("No value entered.", "Error", wxOK | wxICON_ERROR, this);
    }

    // this->Close();
}

void NumericInputFrame::resetFrame()
{
    sizer->Clear();

    textField = new wxTextCtrl(panel, INPUTFIELD, wxEmptyString, wxPoint(50, 50), wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_RIGHT | wxTE_CENTRE);
    textField->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    sizer->Add(textField, wxSizerFlags().Center().Border(wxALL, 5));

    // Add button
    button = new wxButton(panel, BUTTON_OK, "Get Value", wxPoint(50, 200), wxDefaultSize);
    button->Bind(wxEVT_BUTTON, &NumericInputFrame::OnButtonClicked, this);
    sizer->Add(button, wxSizerFlags().Center().Border(wxALL, 5));

    label->Destroy();
    label = nullptr;

    panel->Layout();
}
