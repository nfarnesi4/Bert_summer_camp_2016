#include <buttons.h>

#include <RedBot.h>

enum RobotMode {
  RC_MODE,
  LINE_FOLLOWING,
};

RobotMode current_robot_mode = RC_MODE;

RedBotMotors motors;

//vars for line following
RedBotSensor left = RedBotSensor(A3);   // initialize a left sensor object on A3
RedBotSensor center = RedBotSensor(A6); // initialize a center sensor object on A6
RedBotSensor right = RedBotSensor(A7);  // initialize a right sensor object on A7
const int KIRSensorThreshold = 800;
const int KForwardSpeed = 100;
const int KTurnSpeed = 200;

//vars for rc mode
int button_id = 0;
int button_value = 0;
int previous_button_value = 0;
int left_speed = 0;
int right_speed = 0;


void setup() {
  Serial.begin(9600);
}

void loop() { 

  rcDriveUpdate();

  if (current_robot_mode == LINE_FOLLOWING) {
    lineFollow();
  }

  //set the motor speeds
  motors.leftMotor(left_speed);
  motors.rightMotor(right_speed);

}

void rcDriveUpdate(){

  //check to see if a button was pressed or let go
  if (previous_button_value != button_value) {
    //if the button is pressed (it has a value of 1)
    //then check to see which one it is and drive
    //in the new direction
    if (button_value == '1') {

      //this switch statement checks to see which button is pressed
      switch (button_id) {

        //set the speeds of the motors when each of the buttons is pressed

        case FORWARD_ARROW:
          left_speed = 255;
          right_speed = 255;
          break;

        case BACKWARD_ARROW:
          left_speed = -255;
          right_speed = -255;
          break;

        case LEFT_ARROW:
          left_speed = -255;
          right_speed = 255;
          break;

        case RIGHT_ARROW:
          left_speed = 255;
          right_speed = -255;
          break;

        case BUTTON_ONE:
          left_speed = 100;
          right_speed = 255;
          break;

        case BUTTON_TWO:
          left_speed = 255;
          right_speed = 100;
          break;

        case BUTTON_THREE:
          left_speed = 100;
          right_speed = 100;
          break;

        case BUTTON_FOUR:
          switch(current_robot_mode) {
            case LINE_FOLLOWING:
              current_robot_mode = RC_MODE;
              break;
            case RC_MODE:
              current_robot_mode = LINE_FOLLOWING;
              break;
          } //swtich robot mode
          break;

      }//swtich button id 

    }
    //when the button value is a zero 
    //set the motors to a zero
    else {
      if (current_robot_mode == RC_MODE) {
        left_speed = right_speed = 0;
      }
    }

    previous_button_value = button_value;

  }
}

void lineFollow() {
  if (center.read() > KIRSensorThreshold) {
    left_speed = KForwardSpeed;
    right_speed = KForwardSpeed;
  }
  else if (right.read() > KIRSensorThreshold) {
    left_speed = KTurnSpeed;
    right_speed = -KTurnSpeed;
  }
  else if (left.read() > KIRSensorThreshold) {
    left_speed = -KTurnSpeed;
    right_speed = KTurnSpeed;
  }
  else {
    left_speed = 0;
    right_speed = 0;
  }
}

//handles coms with the bluetooth module
void serialEvent() {
  //wait until there is at least 5 bytes to read
  while (Serial.available()>4) {
    //check for the start of a new packet
    if (Serial.read() == '!') {
      Serial.read(); // read and discard the next byte
      button_id = Serial.read(); //first byte is the id
      button_value = Serial.read(); //second byte is the id
      char CRC = Serial.read(); //checksum 
      //Serial.println(button_value);
      //print out the data for debuging:
      Serial.print(button_id); 
      Serial.print(" : ");
      Serial.println(button_value);
    }
  }
}

