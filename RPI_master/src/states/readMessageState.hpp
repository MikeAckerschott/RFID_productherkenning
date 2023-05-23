#ifndef READMESSAGESTATE_HPP_
#define READMESSAGESTATE_HPP_

#include "state.hpp"

class readMessageState : public State
{
public:
    readMessageState();

    void f_entry() override;
    void f_do() override;
    void f_exit() override;

    bool checkAllTriggers() override;

    bool triggerProductDocked();

    // std::vector<can_frame> msgBuffer;

private:
    stationList *frame;
};

#endif /*READMESSAGESTATE_HPP_*/