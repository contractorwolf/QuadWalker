
#include <SoftwareSerial.h>




#define TORSOCHANNEL 0
#define LEGCHANNEL 2

#define TORSOCHANNEL2 4
#define LEGCHANNEL2 6

#define TORSOCHANNEL3 8
#define LEGCHANNEL3 10


#define TORSOCHANNEL4 12
#define LEGCHANNEL4 14



//serial connection diagram for Parallax Rev B servo controller
//http://forums.parallax.com/showthread.php/153990-Parallax-Servo-Controller-%E2%80%93-USB-(-28823)-Rev-B


int servoCenter = 700;
int torsoMaxMovement = 45;//220 max
int legMaxMovement = 75;//140 max

boolean isTorsoActive = true;
boolean isLegActive = true;

int torsoMovementDelay = 500;//360 max
int legMovementDelay = 600;//160;//280 max

int rearOffset = 70;

SoftwareSerial mySerial(10, 11); // RX, TX




void setup()  {
  //Servo Control board
  //Serial1.begin(2400);
  
  mySerial.begin(2400);
  
  

  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.println("QUAD WALKER started");
  
  
  AltMoveServo(TORSOCHANNEL, 0);
  AltMoveServo(LEGCHANNEL, 0);
  
  AltMoveServo(TORSOCHANNEL2, 0);
  AltMoveServo(LEGCHANNEL2, 0);
  
 
  AltMoveServo(TORSOCHANNEL3, 0);
  AltMoveServo(LEGCHANNEL3, 0);
  
  
  AltMoveServo(TORSOCHANNEL4, 0);
  AltMoveServo(LEGCHANNEL4, 0);
  
  delay(5000);
}

bool direction = false;
void loop() {
  

  
  
  

  if(isTorsoActive){
      AltMoveServo(TORSOCHANNEL, -torsoMaxMovement);//-220
      AltMoveServo(TORSOCHANNEL2, torsoMaxMovement);//220   
      
      AltMoveServo(TORSOCHANNEL3, -torsoMaxMovement);//-220
      AltMoveServo(TORSOCHANNEL4, torsoMaxMovement);//-220
      
      delay(torsoMovementDelay);
  }    
      
  if(isLegActive){      
      AltMoveServo(LEGCHANNEL, legMaxMovement);//140
      AltMoveServo(LEGCHANNEL2, -legMaxMovement);//-140
      
      AltMoveServo(LEGCHANNEL3, -legMaxMovement);//140    
      AltMoveServo(LEGCHANNEL4, legMaxMovement);//140      
      delay(legMovementDelay);
  }
  if(isTorsoActive){   
      AltMoveServo(TORSOCHANNEL, torsoMaxMovement);//220
      AltMoveServo(TORSOCHANNEL2, -torsoMaxMovement);//-220
      
      AltMoveServo(TORSOCHANNEL3, torsoMaxMovement);//220
      AltMoveServo(TORSOCHANNEL4, -torsoMaxMovement);//-220      
      delay(torsoMovementDelay);
  }
  
  if(isLegActive){      
      AltMoveServo(LEGCHANNEL, -legMaxMovement);//-140
      AltMoveServo(LEGCHANNEL2, legMaxMovement);//140
      
      AltMoveServo(LEGCHANNEL3, legMaxMovement);//-140      
      AltMoveServo(LEGCHANNEL4, -legMaxMovement);//-140     
      delay(legMovementDelay);
  }    

}



void MoveServo(int servo_channel, int movement){

  
    int servo_angle = servoCenter + movement;
  
  
    byte lsb = servo_angle;
    byte msb =  servo_angle >> 8;
    int ramp = 0;
  
  
    Serial1.write(33);  //!
    Serial1.write(83);  //S
    Serial1.write(67);  //C
    Serial1.write(servo_channel);  //channel
    Serial1.write(ramp);  //rampspeed
    Serial1.write(lsb);  //LSB
    Serial1.write(msb);  //MSB
    Serial1.write(13);
    
    
    Serial.print("channel:");
    Serial.print(servo_channel);
       
    Serial.print(" angle:");
    Serial.println(servo_angle);
}


void AltMoveServo(int servo_channel, int movement){

  
    int servo_angle = servoCenter + movement;
  
  
    byte lsb = servo_angle;
    byte msb =  servo_angle >> 8;
    int ramp = 0;
  
  
    mySerial.write(33);  //!
    mySerial.write(83);  //S
    mySerial.write(67);  //C
    mySerial.write(servo_channel);  //channel
    mySerial.write(ramp);  //rampspeed
    mySerial.write(lsb);  //LSB
    mySerial.write(msb);  //MSB
    mySerial.write(13);
    
    
    Serial.print("channel:");
    Serial.print(servo_channel);
       
    Serial.print(" angle:");
    Serial.println(servo_angle);
}

