#ifndef IDLESTATE_HPP_
#define IDLESTATE_HPP_

#include "state.hpp"

class idleState : public State
{
public:
    idleState();

    void f_entry() override;
    void f_do() override;
    void f_exit() override;

    bool checkAllTriggers() override;

    bool triggerButtonPressed();

    bool triggerWorkspaceRequestReceived();

private:
};

#endif /*IDLESTATE_HPP_*/