
#include "hardware_config.h"

volatile bool inputoutput_inited = false;

void setup() {
  // setup code
  delay(500);
  if (hardware_button_state()) {//if button is pressed on startup goto Bootloader
    NRF_POWER->GPREGRET = BOOTLOADER_ADDRESS;
    NVIC_SystemReset();
  }


}

void loop() {
  // put your main code here, to run repeatedly:

}


bool hardware_button_state() {
  //get the state of the button
  if (!inputoutput_inited)init_inputoutput();
  if (PUSH_BUTTON_OUT != -1) {
    pinMode(PUSH_BUTTON_OUT, OUTPUT);
    digitalWrite(PUSH_BUTTON_OUT, HIGH);
  }
  bool button_state = digitalRead(PUSH_BUTTON_IN);
  return button_state;
}
