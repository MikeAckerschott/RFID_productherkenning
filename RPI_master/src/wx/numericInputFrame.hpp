#ifndef NUMERIC_INPUT_FRAME_HPP_
#define NUMERIC_INPUT_FRAME_HPP_

#include <wx/wx.h>

class NumericInputFrame : public wxFrame
{
public:
    NumericInputFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style);
    void OnButtonClicked(wxCommandEvent &event);
    void resetFrame();

    bool valueGiven;
    long newWs;

    static const short FRAME_ID = 11;

    enum wxFields
    {
        INPUTFIELD = 1,
        BUTTON_OK = 2,
        TEXTFIELD = 3
    };

private:
    wxPanel *panel;
    wxBoxSizer *sizer;
    wxTextCtrl *textField;
    wxButton *button;
    wxStaticText *label;
};

#endif /* NUMERIC_INPUT_FRAME_HPP_ */
