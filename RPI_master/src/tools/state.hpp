#ifndef STATE_HPP_
#define STATE_HPP_

#include <vector>
#include "context.hpp"
#include "can.h"

// Forward declaration of Context class
class Context;

class State
{
  /**
   * @var Context
   */
protected:
  Context *context_;

public:
  virtual ~State();

  void set_context(Context *context);

  virtual bool checkAllTriggers() = 0;

  virtual void f_entry() = 0;
  virtual void f_do() = 0;
  virtual void f_exit() = 0;

  struct can_frame canMsg;

private:

};

#endif /* BUTTON_HPP_ */