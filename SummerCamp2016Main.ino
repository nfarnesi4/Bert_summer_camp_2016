#include <RedBot.h>
#include "buttons.h"
RedBotMotors motors;

int button_id = 0;
int button_value = 0;
int previous_button_value = 0;
int left_speed = 0;
int right_speed = 0;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  
  if (previous_button_value != button_value) {
    if (button_value == '1') {
      switch (button_id) {
        case FORWARD:
          left_speed = 255;
          right_speed = 255;
          break;

        case BACKWARD:
          left_speed = -255;
          right_speed = -255;
          break;

        case LEFT:
          left_speed = -255;
          right_speed = 255;
          break;

        case RIGHT:
          left_speed = 255;
          right_speed = -255;
          break;

        case ONE:
          left_speed = 100;
          right_speed = 255;
          break;

        case TWO:
          left_speed = 255;
          right_speed = 100;
          break;

        case THREE:
          left_speed = 100;
          right_speed = 100;
          break;

        case FOUR:
          left_speed = 20;
          right_speed = 20;
          break;

      }
    }
    else {
      left_speed = right_speed = 0;
    }

    previous_button_value = button_value;

  }

  //set the motor speeds
  motors.leftMotor(left_speed);
  motors.rightMotor(right_speed);
  
}

void serialEvent() {
  while (Serial.available()>4) {
    if (Serial.read() == '!') {
      Serial.read();
      button_id = Serial.read();
      button_value = Serial.read();
      char CRC = Serial.read();
      //Serial.println(button_value);
      Serial.print(button_id);
      Serial.print(" : ");
      Serial.println(button_value);
    }
  }
}

