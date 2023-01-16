
#define PUSH_BUTTON_IN      17
#define PUSH_BUTTON_OUT     -1

#define BOOTLOADER_ADDRESS       0x01

#define STATUS_LED        27
#define VIBRATOR_OUT      16

#define LF_FREQUENCY 32768UL
#define SECONDS(x) ((uint32_t)((LF_FREQUENCY * x) + 0.5))
#define wakeUpSeconds 0.040

const int BLINKING_LIMIT = 5;
int blinkCount = 0;


void setup() {


  bool inputoutput_inited = false;
  bool button_state = digitalRead(PUSH_BUTTON_IN);

  delay(5000);
   
  if (!inputoutput_inited) {
    
      pinMode(STATUS_LED, OUTPUT);
      pinMode(VIBRATOR_OUT, OUTPUT);
      pinMode(PUSH_BUTTON_IN, INPUT);
      
      if (PUSH_BUTTON_OUT != -1) {
        pinMode(PUSH_BUTTON_OUT, OUTPUT);
        digitalWrite(PUSH_BUTTON_OUT, HIGH);
      }
    
      digitalWrite(STATUS_LED, LOW);
      digitalWrite(VIBRATOR_OUT, HIGH);
      inputoutput_inited = true;
  }

  
  if (PUSH_BUTTON_OUT != -1) {
    pinMode(PUSH_BUTTON_OUT, OUTPUT);
    digitalWrite(PUSH_BUTTON_OUT, HIGH);
  }
  

  if (button_state) {
    NRF_POWER->GPREGRET = BOOTLOADER_ADDRESS;
    NVIC_SystemReset();
  }
  
  NVIC_ClearPendingIRQ(RTC2_IRQn);
  NVIC_SetPriority(RTC2_IRQn, 15);
  NVIC_EnableIRQ(RTC2_IRQn);

  NRF_RTC2->PRESCALER = 0;
  NRF_RTC2->CC[0] = SECONDS(wakeUpSeconds);
  NRF_RTC2->INTENSET = RTC_EVTENSET_COMPARE0_Enabled << RTC_EVTENSET_COMPARE0_Pos;
  NRF_RTC2->EVTENSET = RTC_INTENSET_COMPARE0_Enabled << RTC_INTENSET_COMPARE0_Pos;
  NRF_RTC2->TASKS_START = 1;

}

void loop() {

    blinkCount++;
    if (blinkCount < BLINKING_LIMIT) {
        digitalWrite(VIBRATOR_OUT, HIGH);
        delay(500);
        digitalWrite(VIBRATOR_OUT, LOW);
    }
    delay(500);

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
