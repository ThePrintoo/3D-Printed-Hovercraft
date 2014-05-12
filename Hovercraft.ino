/**********************************************************************
* © 2014 YD Ynvisible, S.A.
*
* FileName:        Hovercraft.ino
* Dependencies:    SoftwareSerial.h
* Processor:       ATmega328
* IDE:             Arduino 1.0.5
*
* Description:
* Driving a 2 motors aquatic drone through a smartphone via Bluetooth 4.0
* We used the LightBlue Bluetooth 4.0 terminal for iPhone for control
**********************************************************************/

#include <SoftwareSerial.h> //Software Serial Port
#define RxD 6 //Bluetooth TX=Core RX
#define TxD 7 //Bluetooth RX=Core TX
#define FRONT 1
#define BACK 0
#define OFF 0
#define ON 1
SoftwareSerial blueToothSerial(RxD,TxD);

int motor1_pwm=9;
int motor1_dir=8;
int motor2_pwm=11;
int motor2_dir=12;
char X[3], Y[3], A, B;
int X1_num;
int i=1;
int X_num,Y_num, A_num, B_num;
int X_numf,Y_numf, A_numf, B_numf;
int motor1_way,motor2_way;
char recvChar;

void setup()
{
  Serial.begin(9600);
  //pinMode(BUTTON, INPUT);  
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(motor1_pwm, OUTPUT); //Motor1 PWM
  pinMode(motor1_dir, OUTPUT); //Motor1
  pinMode(motor2_pwm, OUTPUT); //Motor2 PWM
  pinMode(motor2_dir, OUTPUT); //Motor3
  digitalWrite(motor1_pwm,LOW);
  digitalWrite(motor1_dir,LOW);
  digitalWrite(motor2_pwm,LOW);
  digitalWrite(motor2_dir,LOW);
  setupBlueToothConnection();
}
void loop()
{
  if(blueToothSerial.available()){   //check if the pipe is free
    recvChar = blueToothSerial.read();
    switch (recvChar){
      case '#':                          //go forward
        analogWrite(motor1_pwm,150);
        digitalWrite(motor1_dir,LOW);
        analogWrite(motor2_pwm,150); 
        digitalWrite(motor2_dir,LOW);
        delay(250); 
        analogWrite(motor1_pwm,180);
        digitalWrite(motor1_dir,LOW);
        analogWrite(motor2_pwm,180); 
        digitalWrite(motor2_dir,LOW);
        delay(250);   
        break;      
      case 'r':                          //go right
        analogWrite(motor1_pwm,150);
        digitalWrite(motor1_dir,LOW);
        analogWrite(motor2_pwm,0); 
        digitalWrite(motor2_dir,LOW);
        delay(250); 
        analogWrite(motor1_pwm,180);
        digitalWrite(motor1_dir,LOW);
        analogWrite(motor2_pwm,0); 
        digitalWrite(motor2_dir,LOW);
        delay(250); 
        break;
      case 'l':                           //go left
        analogWrite(motor1_pwm,0);
        digitalWrite(motor1_dir,LOW);
        analogWrite(motor2_pwm,150); 
        digitalWrite(motor2_dir,LOW);
        delay(250); 
        analogWrite(motor1_pwm,0);
        digitalWrite(motor1_dir,LOW);
        analogWrite(motor2_pwm,180); 
        digitalWrite(motor2_dir,LOW);
        delay(250); 
        break;
      case 's':                          //stop
        analogWrite(motor1_pwm,0);
        digitalWrite(motor1_dir,LOW);
        analogWrite(motor2_pwm,0); 
        digitalWrite(motor2_dir,LOW);
        delay(250); 
        analogWrite(motor1_pwm,0);
        digitalWrite(motor1_dir,LOW);
        analogWrite(motor2_pwm,0); 
        digitalWrite(motor2_dir,LOW);
        delay(250); 
        break;
      default: break;
    }
  }
}  
  
void setupBlueToothConnection(){
  blueToothSerial.begin(9600); //Set BluetoothBee BaudRate to default baud rate 9600
  delay(10); // This delay is required.
  blueToothSerial.print("AT+RENEW"); //Restore all setup value to factory setup
  delay(10);  // This delay is required.
  blueToothSerial.print("AT+ROLE0"); //make it a slave   
  delay(10);  // This delay is required.
}
