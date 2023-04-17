#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// sets speed of servos' delay between step's steps (more is slower)
#define SERVO_DELAY 250
#define SERVO_SUBSTEP_DELAY 100

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
  move_forward(5);

  delay(3000);

  turn(5, true);

  delay(3000);

  move_forward(5);

  delay(3000);

  turn(3, false);

  delay(3000);
}

void move_forward (uint8_t count) {
  for (uint8_t j = 0; j < count; j++) {
    // move every leg back at once

    for (uint8_t i = 0; i < 4; i++) {
      pwm.setPWM(i, 0, STOPPOS[i]);
    }

    delay(SERVO_DELAY);
    
    // move every leg forward one at at time

    for (uint8_t i = 0; i < 4; i++) {
      pwm.setPWM(i + 4, 0, STOPPOS[i + 4]);

      delay(SERVO_SUBSTEP_DELAY);

      pwm.setPWM(i, 0, STARTPOS[i]);

      delay(SERVO_SUBSTEP_DELAY);
      
      pwm.setPWM(i + 4, 0, STARTPOS[i + 4]);

      delay(SERVO_SUBSTEP_DELAY);
    }

    delay(SERVO_DELAY);
  }
}

void turn (uint8_t count, bool right) {
  for (uint8_t i = 0; i < count; i++) {
    if (right) {
      // FR tibia up
      pwm.setPWM(5, 0, STOPPOS[5]);

      delay(SERVO_DELAY);

      // FL & BL femur back
      pwm.setPWM(0, 0, STOPPOS[0]);
      pwm.setPWM(2, 0, STOPPOS[2]);

      delay(SERVO_DELAY);

      // FR tibia down
      pwm.setPWM(5, 0, STARTPOS[5]);

      delay(SERVO_DELAY);

      // BL leg to starting position
      pwm.setPWM(6, 0, STOPPOS[6]);

      delay(SERVO_SUBSTEP_DELAY);

      pwm.setPWM(2, 0, STARTPOS[2]);

      delay(SERVO_SUBSTEP_DELAY);

      pwm.setPWM(6, 0, STARTPOS[6]);

      delay(SERVO_DELAY);
      
      // FL leg to starting postition

      pwm.setPWM(4, 0, STOPPOS[4]);

      delay(SERVO_SUBSTEP_DELAY);

      pwm.setPWM(0, 0, STARTPOS[0]);

      delay(SERVO_SUBSTEP_DELAY);

      pwm.setPWM(4, 0, STARTPOS[4]);

      delay(SERVO_DELAY);
    } else {
      // FL tibia up
      pwm.setPWM(4, 0, STOPPOS[4]);

      delay(SERVO_DELAY);

      // FR & BR femur back
      pwm.setPWM(1, 0, STOPPOS[1]);
      pwm.setPWM(3, 0, STOPPOS[3]);

      delay(SERVO_DELAY);

      // FL tibia down
      pwm.setPWM(4, 0, STARTPOS[4]);

      delay(SERVO_DELAY);

      // BR leg to starting position
      pwm.setPWM(7, 0, STOPPOS[7]);

      delay(SERVO_SUBSTEP_DELAY);

      pwm.setPWM(3, 0, STARTPOS[2]);

      delay(SERVO_SUBSTEP_DELAY);

      pwm.setPWM(7, 0, STARTPOS[7]);

      delay(SERVO_DELAY);
      
      // FL leg to starting postition

      pwm.setPWM(5, 0, STOPPOS[5]);

      delay(SERVO_SUBSTEP_DELAY);

      pwm.setPWM(1, 0, STARTPOS[1]);

      delay(SERVO_SUBSTEP_DELAY);

      pwm.setPWM(5, 0, STARTPOS[5]);

      delay(SERVO_DELAY);
    }
  }
}
