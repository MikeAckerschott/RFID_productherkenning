#ifndef NUMERIC_INPUT_FRAME_HPP_
#define NUMERIC_INPUT_FRAME_HPP_

#include <wx/wx.h>

class NumericInputFrame : public wxFrame
{
public:
    NumericInputFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style);
    void OnButtonClicked(wxCommandEvent &event);
    void resetFrame();

    static const short FRAME_ID = 11;

    enum wxFields
    {
        INPUTFIELD = 1,
        BUTTON_OK = 2,
        TEXTFIELD = 3
    };

    bool isValueGiven();
    void setValueGiven(bool newValue);
    long getNewWs();
    void setNewWs(long newValue);


private:
    wxPanel *panel;
    wxBoxSizer *sizer;
    wxTextCtrl *textField;
    wxButton *button;
    wxStaticText *label;

    bool valueGiven;
    long newWs;
};

#endif /* NUMERIC_INPUT_FRAME_HPP_ */
