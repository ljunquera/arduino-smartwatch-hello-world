
#include "hardware_config.h"
#include <lvgl.h>

#define LF_FREQUENCY 32768UL
#define SECONDS(x) ((uint32_t)((LF_FREQUENCY * x) + 0.5))
#define wakeUpSeconds 0.040




/*Change to your screen resolution*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];



void setup() {


  bool inputoutput_inited = false;
  bool button_state = digitalRead(PUSH_BUTTON_IN);

  delay(5000);
   
  //get the state of the button
  if (!inputoutput_inited) {
    
      pinMode(STATUS_LED, OUTPUT);
      pinMode(VIBRATOR_OUT, OUTPUT);
      pinMode(PUSH_BUTTON_IN, INPUT);
      
      if (PUSH_BUTTON_OUT != -1) {
        pinMode(PUSH_BUTTON_OUT, OUTPUT);
        digitalWrite(PUSH_BUTTON_OUT, HIGH);
      }
    
      set_led(0);
      set_motor(0);
      inputoutput_inited = true;
  }

  
  if (PUSH_BUTTON_OUT != -1) {
    pinMode(PUSH_BUTTON_OUT, OUTPUT);
    digitalWrite(PUSH_BUTTON_OUT, HIGH);
  }
  

  if (button_state) {//if button is pressed on startup goto Bootloader
    reset_to_bootloader();
  }
  
  //rtc_init();
  //lv_init();
  //display_label();

}

void loop() {
  // put your main code here, to run repeatedly:
  //lv_timer_handler(); /* let the GUI do its work */ 
  delay( 100000 );
  reset_to_bootloader();
  

}

void reset_to_bootloader() {
    NRF_POWER->GPREGRET = BOOTLOADER_ADDRESS;
    NVIC_SystemReset();
}




void set_led(bool state) {
  if (state)
    digitalWrite(STATUS_LED, HIGH);
  else
    digitalWrite(STATUS_LED, LOW);
}

void set_motor(bool state) {
  if (state)
    digitalWrite(VIBRATOR_OUT, LOW);
  else
    digitalWrite(VIBRATOR_OUT, HIGH);
}

void display_label() {

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  
      /* Create simple label */
    lv_obj_t *label = lv_label_create( lv_scr_act() );
    lv_label_set_text( label, LVGL_Arduino.c_str() );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
}

void rtc_init() {

  NVIC_ClearPendingIRQ(RTC2_IRQn);
  NVIC_SetPriority(RTC2_IRQn, 15);
  NVIC_EnableIRQ(RTC2_IRQn);

  NRF_RTC2->PRESCALER = 0;
  NRF_RTC2->CC[0] = SECONDS(wakeUpSeconds);
  NRF_RTC2->INTENSET = RTC_EVTENSET_COMPARE0_Enabled << RTC_EVTENSET_COMPARE0_Pos;
  NRF_RTC2->EVTENSET = RTC_INTENSET_COMPARE0_Enabled << RTC_INTENSET_COMPARE0_Pos;
  NRF_RTC2->TASKS_START = 1;
}
