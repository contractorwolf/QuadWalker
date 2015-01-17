
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
int torsoMaxMovement = 70;//220 max
int legMaxMovement = 130;//140 max

boolean isTorsoActive = true;
boolean isLegActive = true;

int torsoMovementDelay = 500;//360 max
int legMovementDelay = 600;//160;//280 max

int rearOffset = 70;


void setup()  {
  //Servo Control board
  Serial1.begin(2400);

  Serial.begin(9600);
  Serial.println("QUAD WALKER started");
  
  
  MoveServo(TORSOCHANNEL, 0);
  MoveServo(LEGCHANNEL, 0);
  
  MoveServo(TORSOCHANNEL2, 0);
  MoveServo(LEGCHANNEL2, 0);
  
 
  MoveServo(TORSOCHANNEL3, 0);
  MoveServo(LEGCHANNEL3, 0);
  
  
  MoveServo(TORSOCHANNEL4, 0);
  MoveServo(LEGCHANNEL4, 0);
  
  delay(5000);
}


void loop() {

  if(isTorsoActive){
      MoveServo(TORSOCHANNEL, -torsoMaxMovement);//-220
      MoveServo(TORSOCHANNEL2, torsoMaxMovement);//220   
      MoveServo(TORSOCHANNEL3, -torsoMaxMovement);//-220
      MoveServo(TORSOCHANNEL4, torsoMaxMovement);//-220
      
      delay(torsoMovementDelay);
  }    
      
  if(isLegActive){      
      MoveServo(LEGCHANNEL, legMaxMovement);//140
      MoveServo(LEGCHANNEL2, -legMaxMovement);//-140
      MoveServo(LEGCHANNEL3, -(legMaxMovement));//140    
      MoveServo(LEGCHANNEL4, legMaxMovement);//140      
      delay(legMovementDelay);
  }
  if(isTorsoActive){   
      MoveServo(TORSOCHANNEL, torsoMaxMovement);//220
      MoveServo(TORSOCHANNEL2, -torsoMaxMovement);//-220
      MoveServo(TORSOCHANNEL3, torsoMaxMovement);//220
      MoveServo(TORSOCHANNEL4, -torsoMaxMovement);//-220      
      delay(torsoMovementDelay);
  }
  
  if(isLegActive){      
      MoveServo(LEGCHANNEL, -legMaxMovement);//-140
      MoveServo(LEGCHANNEL2, legMaxMovement);//140
      MoveServo(LEGCHANNEL3, legMaxMovement);//-140      
      MoveServo(LEGCHANNEL4, -legMaxMovement);//-140     
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
    Serial.println(servo_channel);
       
    Serial.print("angle:");
    Serial.println(servo_angle);
}


