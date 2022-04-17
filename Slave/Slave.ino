#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define SLAVE_EN  8
#define LED       13
#define USMIN  550 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2555 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

String recInput;                                // Variable to store Receive string 
int Forward, Left_Right, RoboBase, RoboShoulder, RoboElbow, RoboWristRot, RoboWristUpDownBTN, RoboGripper;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void setup() {
  pinMode(LED , OUTPUT);                        // Declare LED pin as output
  pinMode(SLAVE_EN , OUTPUT);                   // Declare Enable pin as output
  Serial.begin(9600);                           // set serial communication baudrate 
  digitalWrite(SLAVE_EN , LOW);                 // Make Enable pin low, Receiving mode ON 
  pwm.begin();

  pwm.setOscillatorFrequency(27000000);

  pwm.setPWMFreq(SERVO_FREQ);  
  delay(10);
  
}

void loop() {
  while(Serial.available())                     // If serial data is available then enter into while loop
  {
    recInput = Serial.readStringUntil('*');     // Receive Serial data in Variable
   
    split();
    controls();
  }
}


void controls() {

  pwm.writeMicroseconds();
}

void split()  {

  sscanf(recInput.c_str(), "%d,%d,%d,%d,%d,%d,d,d", &Forward, &Left_Right, 
                                                    &RoboBase, &RoboShoulder,
                                                    &RoboElbow, &RoboWristRot,
                                                    &RoboWristUpDownBTN,
                                                    &RoboGripper);
  Serial.print(Forward);
  Serial.print("   ");
  Serial.print(Left_Right);
  Serial.print("   ");
  Serial.print(RoboBase);
  Serial.print("   ");
  Serial.print(RoboShoulder);
  Serial.print("   ");
  Serial.print(RoboElbow);
  Serial.print("   ");
  Serial.print(RoboWristRot);
  Serial.print("   ");
  Serial.print(RoboWristUpDownBTN);
  Serial.print("   ");
  Serial.print(RoboGripper);
  Serial.println("   ");
}
