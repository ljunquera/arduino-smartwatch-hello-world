
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

bool is_vibrate_mode = true;


void setup() {

  pinMode(VIBRATOR_OUT, OUTPUT);
  pinMode(PUSH_BUTTON_IN, INPUT);

}

void loop() {

  is_vibrate_mode = digitalRead(PUSH_BUTTON_IN);
  if (is_vibrate_mode) {
    digitalWrite(VIBRATOR_OUT, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(VIBRATOR_OUT, LOW);   // turn the LED off by making the voltage LOW    
  }

  delay(1000);                      // wait for a second

}
