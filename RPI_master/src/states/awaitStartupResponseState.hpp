#ifndef AWAITSTARTUPRESPONSESTATE_HPP_
#define AWAITSTARTUPRESPONSESTATE_HPP_

#include <chrono>
#include "state.hpp"
#include <vector>

class awaitStartupResponseState : public State
{
public:
    awaitStartupResponseState();

    void f_entry() override;
    void f_do() override;
    void f_exit() override;

    bool checkAllTriggers() override;

private:
    std::chrono::milliseconds ms;
    std::vector<short> subscribedWorkstations;
    std::vector<short> duplicateWorkstations;
};

#endif /*AWAITSTARTUPRESPONSESTATE_HPP_*/