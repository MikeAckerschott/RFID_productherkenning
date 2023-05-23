#ifndef PROCESSTATUS_HPP_
#define PROCESSTATUS_HPP_

#include <map>
#include <iostream>
#include <vector>
#include "numericInputFrame.hpp"

class bFrame;

/**
 * The procesStatus class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class procesStatus
{

    /**
     * The procesStatus's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */

protected:
    procesStatus();

    static procesStatus *procesStatus_;

public:
    /**
     * procesStatuss should not be cloneable.
     */
    procesStatus(procesStatus &other) = delete;
    /**
     * procesStatuss should not be assignable.
     */
    void operator=(const procesStatus &) = delete;
    /**
     * This is the static method that controls the access to the procesStatus
     * instance. On the first run, it creates a procesStatus object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static procesStatus *GetInstance();
    /**
     * Finally, any procesStatus should define some business logic, which can be
     * executed on its instance.
     */


};

#endif /*PROCESSTATUS_HPP_*/