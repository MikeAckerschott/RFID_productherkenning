#ifndef BFRAME_HPP_
#define BFRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class procesStatus;

class bFrame : public wxFrame
{
public:
    bFrame(const short workspace);

    void OnButtonYesClick(wxCommandEvent &event);
    void OnButtonNoClick(wxCommandEvent &event);
    void removeButtons();
    void setDockingText();
    void setUndockingText();
    void setDockingRequestText();

    wxBoxSizer *sizer;
    wxPanel *panel;

    enum wxFields{
        BUTTON_OK = 1,
        BUTTON_CANCEL = 2,
        TEXTFIELD = 3,
        INPUTFIELD = 4
    };  

private:
    // Declare the event table for the class
    wxDECLARE_EVENT_TABLE();
    const short workspace;
    const wxString product;
    
};

#endif /*BFRAME_HPP_*/