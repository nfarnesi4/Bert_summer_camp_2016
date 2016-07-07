/*
Program that will set the vals for the bluetooth device.
NOTE: fill in the correct information below.
NOTE: make sure everything is wired correctly and
the switch on the robot is in the "xbee hardware serial"
posistion.
NOTE: the swtich on the bluetooth device must be set to
"UART" mode
*/
#define DEVICE_NAME "DEVICE NAME HERE"
#define DEVICE_POWER_LEVEL "0" //change to the correct device power

void setup() {
  //setup serial
  Serial.begin(9600);
  //set device to command mode
  Serial.println("+++");
  //set device name
  Serial.println("AT+GAPDEVNAME=" DEVICE_NAME);
  //set power level
  Serial.println("AT+BLEPOWERLEVEL=" DEVICE_POWER_LEVEL);
  //reset the bluetooth device for changes to take place
  Serial.println("ATZ");
  //set device back to normal mode
  Serial.println("+++");
}

void loop() {  
  //this program does all the work in the setup
}
