#define ForwardJoy1 A0
#define LeftRightJoy1 A1
#define BaseJoy2 A2
#define ShoulderJoy2 A3               
#define RoboElbowJoy3 A4
#define RoboWristRotJoy3 A5
#define WristUpDown  4
#define Gripper 7

#define MASTER_EN   8                 // connected to RS485 Enable pin



//Position variables
int ForwardPos = 0;
int LeftRightPos = 0;
int BasePos = 0;
int ShoulderPos = 0;
int ElbowPos = 0;
int WristRotPos = 0;
int WristUpDownBTN = 0;
int GripperBTN = 0;


//Mapping variables
int mapForward = 0;
int mapLeftRight = 0;
int mapBase = 0;
int mapShoulder = 0;
int mapElbow = 0;
int mapWristRot = 0;


  
void setup() {

  pinMode(MASTER_EN , OUTPUT);        // Declare Enable pin as output
  pinMode(ForwardJoy1, INPUT);
  pinMode(LeftRightJoy1, INPUT);
  pinMode(BaseJoy2, INPUT);
  pinMode(ShoulderJoy2, INPUT);
  pinMode(RoboElbowJoy3, INPUT);
  pinMode(RoboWristRotJoy3, INPUT);
  pinMode(WristUpDown , INPUT_PULLUP);
  pinMode(Gripper, INPUT_PULLUP);
  Serial.begin(9600);                 // set serial communication baudrate 
  digitalWrite(MASTER_EN , LOW);      // Make Enable pin low, Receiving mode ON
}

void loop() {

    Control();
}


void Control() {

  //Reading values
  ForwardPos = analogRead(ForwardJoy1);
  LeftRightPos = analogRead(LeftRightJoy1);
  BasePos = analogRead(BaseJoy2);
  ShoulderPos = analogRead(ShoulderJoy2);
  ElbowPos = analogRead(RoboElbowJoy3);
  WristRotPos = analogRead(RoboWristRotJoy3);
  WristUpDownBTN = digitalRead(WristUpDown),
  GripperBTN = digitalRead(Gripper);

  //Mapping Values
  mapForward = map(ForwardPos, 0, 1023, -512, 512);
  mapLeftRight = map(LeftRightPos, 0, 1023, -512, 512);
  mapBase = map(BasePos, 0, 1023, -512, 512);
  mapShoulder = map(ShoulderPos, 0, 1023, -512, 512);
  mapElbow = map(ElbowPos, 0, 1023, -512, 512);
  mapWristRot = map(WristRotPos, 0, 1023, -512, 512);
  
  digitalWrite(MASTER_EN , HIGH);     // Make Enable pin high to send Data
  delay(5);                           // required minimum delay of 5ms
  Serial.print(mapForward);
  Serial.print(", ");
  Serial.print(mapLeftRight);
  Serial.print(", ");
  Serial.print(mapBase);
  Serial.print(", ");
  Serial.print(mapShoulder);
  Serial.print(", ");
  Serial.print(mapElbow);
  Serial.print(", ");
  Serial.print(mapWristRot);
  Serial.print(", ");
  Serial.print(WristUpDownBTN);
  Serial.print(", ");
  Serial.print(GripperBTN);
  Serial.println("**");
  Serial.flush();                     // wait for transmission of data
  digitalWrite(MASTER_EN , LOW);      // Receiving mode ON


  delay(1000);

}
