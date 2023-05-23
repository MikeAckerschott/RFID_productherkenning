#include "procesStatus.hpp"

procesStatus* procesStatus::procesStatus_ = nullptr;

procesStatus::procesStatus()
{
}


/**
 * Static methods should be defined outside the class.
 */
procesStatus *procesStatus::GetInstance()
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (procesStatus_ == nullptr)
    {
        procesStatus_ = new procesStatus();
    }
    return procesStatus_;
}
