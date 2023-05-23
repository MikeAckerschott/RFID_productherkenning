#ifndef SETWORKSPACESTATE_HPP_
#define SETWORKSPACESTATE_HPP_

#include "state.hpp"
#include "numericInputFrame.hpp"

class setWorkspaceState : public State
{
public:
    setWorkspaceState();

    void f_entry() override;
    void f_do() override;
    void f_exit() override;

    bool checkAllTriggers() override;
    bool triggerIntegerReceived();

private:
    uint8_t newWs;
    NumericInputFrame *frame;
};

#endif /*SETWORKSPACESTATE_HPP_*/