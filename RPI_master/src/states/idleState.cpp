#include "idleState.hpp"
#include "setWorkspaceState.hpp"
#include "awaitStartupResponseState.hpp"

void idleState::f_entry()
{
    std::cout << "Entered idlestate" << std::endl;


}

idleState::idleState()
{
}

void idleState::f_do()
{
}

void idleState::f_exit()
{
}

bool idleState::checkAllTriggers()
{
    if (triggerButtonPressed())
    {
        return true;
    }

    if (triggerWorkspaceRequestReceived())
    {
        return true;
    }
    return false;
}

bool idleState::triggerWorkspaceRequestReceived()
{
    // read canframe and store it in the context object as a buffer for next states
    if (this->context_->canbus.workspaceRequestReceived(&canMsg))
    {
        this->context_->TransitionTo(new setWorkspaceState);
        return true;
    }
    return false;
}

bool idleState::triggerButtonPressed()
{
    if (this->context_->button_ok.isButtonPressed())
    {
        this->context_->TransitionTo(new awaitStartupResponseState);
        return true;
    }
    return false;
}