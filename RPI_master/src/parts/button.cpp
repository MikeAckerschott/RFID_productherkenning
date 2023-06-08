#include "button.hpp"
#include <iostream>
#include <vector>
#include <bcm2835.h>

Button::Button(int bPin):pin(bPin){
    // Set the button pin as an input with a pull-down resistor
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_DOWN);

    bcm2835_delay(10);

    lastButtonState = false;
};

//default destructor
Button::~Button(){};

bool Button::isButtonPressed(){
  bool buttonState = bcm2835_gpio_lev(pin);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    return (buttonState == LOW);
  }
  return false;
}