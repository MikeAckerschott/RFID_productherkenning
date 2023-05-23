#ifndef BUTTON_HPP_
#define BUTTON_HPP_

class Button
{
public:
  Button(int pin);

  ~Button();

  bool isButtonPressed();

private:
  int pin;
  bool lastButtonState;
};

#endif /* BUTTON_HPP_ */