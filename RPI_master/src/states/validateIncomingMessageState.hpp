#ifndef VALIDATEINCOMINGMESSAGESTATE_HPP_
#define VALIDATEINCOMINGMESSAGESTATE_HPP_

#include "state.hpp"

class validateIncomingMessageState : public State
{
public:
    validateIncomingMessageState();
    // validateIncomingMessageState(short workspaceNr);

    void f_entry() override;
    void f_do() override;
    void f_exit() override;

    bool checkAllTriggers() override;

private:
    short workspace;

    bool triggerButtonOkPressed();
    bool triggerButtonCancelPressed();

    // std::vector<can_frame> msgBuffer;
};

#endif /*VALIDATEINCOMINGMESSAGESTATE_HPP_*/