#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include "state.hpp"
#include "button.hpp"
#include "canTranslator.hpp"
#include "stationList.hpp"
#include <deque>

class State;

class Context
{

    /**
     * The Context defines the interface of interest to clients. It also maintains a
     * reference to an instance of a State subclass, which represents the current
     * state of the Context.
     */
    /**
     * @var State A reference to the current state of the Context.
     */
private:
    State *state_;
    stationList *stations = nullptr;

public:
    Context(State *state);
    ~Context();
    /**
     * The Context allows changing the State object at runtime.
     */
    void TransitionTo(State *state);
    void setStations(stationList *stations);
    stationList* getStations();
    /**
     * The Context delegates part of its behavior to the current State object.
     */
    void f_entry();
    void f_do();
    void f_exit();

    bool checkAllTriggers();

    const uint8_t BUTTON_OK_PIN = 27;     // connected to GPIO 27 on a raspberry pi 4B
    const uint8_t BUTTON_CANCEL_PIN = 25; // connected to GPIO 25 on a raspberry pi 4B
    const uint8_t MCP2515_CS_PIN = 17;    // connected to GPIO 17 on raspberry pi 4B

    Button button_ok;
    Button button_cancel;
    canTranslator canbus;
    std::deque<can_frame> msgBuffer;
};

#endif /* CONTEXT_HPP_ */