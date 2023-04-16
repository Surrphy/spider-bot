#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Array.h>

// sets speed of servos' movement (more is slower)
#define SERVO_DELAY 4

#define SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// there are 8 servos, 0-3: femur | 4-7: tibia

// this are minimal values for femurs and tibias to be working
int STARTPOS[8] = {
  200,
  550,
  180,
  420,
  230,
  400,
  60,
  420
};

// this are maximal values
int STOPPOS[8] {
  510,
  250,
  420,
  200,
  400,
  550,
  180,
  590
};

void setup() {
  Serial.begin(115200);
  Serial.println("Servo test");

  pwm.begin();

  // don't know what this does B^)
  pwm.setOscillatorFrequency(27000000);

  pwm.setPWMFreq(SERVO_FREQ);

  // set every servo in it's starting position
  for (uint8_t i = 0; i < 8; i++) {
    pwm.setPWM(i, 0, STARTPOS[i]);
  }
}

void loop() {
  for (uint8_t i = 0; i < 4; i++) {
    pwm.setPWM(i, 0, STOPPOS[i]);
  }

  delay(500);

  for (uint8_t i = 4; i < 8; i++) {
    pwm.setPWM(i, 0, STOPPOS[i]);
  }

  delay(500);

  for (uint8_t i = 0; i < 4; i++) {
    pwm.setPWM(i, 0, STARTPOS[i]);
  }

  delay(500);

  for (uint8_t i = 4; i < 8; i++) {
    pwm.setPWM(i, 0, STARTPOS[i]);
  }

  delay(500);
}
