/***** ShuttlecockLauncherBeta.ino
Written by Luis Sanchez 03 Mars 2018 *****/
#include <Servo.h> // 40 - 30
Servo feeder1;
Servo feeder2;

int shootZone4 = 58 ;
int shootZone3 = 45;
int goForwardSpeed = 200;

int pinFeeder1 = 7;
int pinFeeder2 = 6;

int leftWheelSpeed = 5;                                                      // ENA
int leftWheelDirection1 = 27;     // Choosing Pins for H-bridge goForward    // IN1
int leftWheelDirection2 = 26;                                                // IN2
int rightWheelDirection1 = 28;                                               // IN3
int rightWheelDirection2 = 29;                                               // IN4
int rightWheelSpeed = 4;                                                     // ENB

int leftLauncherDirection = 24;   //Choosing Pins for Launcher
int rightLauncherDirection = 25; 
int leftLauncherSpeed = 11;
int rightLauncherSpeed = 10;

int encoderReaderA = 2;           // Choosing Pins for encoder
int encoderReaderB = 3;
int encoderValueA;                // Storing variables for encoder
int encoderValueB; 
int angle = 0;
float distanceTravelled = 0;
const float pi = 3.141592654;



void setup(){
  feeder1.attach(pinFeeder1);
  feeder2.attach(pinFeeder2);
  
  feeder2.write(0);
  feeder1.write(41);

  
  pinMode(leftLauncherDirection,OUTPUT);    // Launcher initialization 
  pinMode(rightLauncherDirection,OUTPUT);
  pinMode(leftLauncherSpeed,OUTPUT);
  pinMode(rightLauncherSpeed,OUTPUT);
  
  pinMode(leftWheelSpeed,OUTPUT);          // Displacement intialization
  pinMode(leftWheelDirection1,OUTPUT);     
  pinMode(leftWheelDirection2,OUTPUT);
  pinMode(rightWheelDirection1,OUTPUT);
  pinMode(rightWheelDirection2,OUTPUT);
  pinMode(rightWheelSpeed,OUTPUT);
 
  
  pinMode(encoderReaderA,INPUT);            // Encoder initialization
  pinMode(encoderReaderB,INPUT);          
 
  Serial.begin(9600);                       // Communication initialization for debugging 
  
  goForward(goForwardSpeed);
 
  
  launch (shootZone4);             
  delay(2000);
  feedBirdie1(41,69,40);   // First Birdie Second Shoot
  delay(1000);
  
  launch(shootZone3);               
  delay(2000);
  feedBirdie1(69,95,40);   // Second Birdie
  delay(1000); 
  
  launch(0);
  goForward(goForwardSpeed);
  
 
  launch (shootZone4);             
  delay(2000);
  feedBirdie1(95,121,40);   // Third Birdie 
  delay(1000);
  
  launch(shootZone3);              
  delay(2000);
  feedBirdie2(30,55,40);    // Fourth Birdie
  delay(1000);

  launch(0);
  goForward(goForwardSpeed);
  

  launch (shootZone4);             
  delay(2000);
  feedBirdie2(60,76,40);    // Fifth Birdie
  delay(1000);
  
  launch(shootZone3);              
  delay(2000);
  feedBirdie2(76,100,40);   // Sixth Birdie
  delay(10000);

  launch(0);

  feeder1.write(41);
  feeder2.write(0);
  Serial.println("End Final");

  }
void loop() {
  
}

void launch (int launcherSpeed) {
  Serial.print("LauncherSpeed Value: "); Serial.print(launcherSpeed); // Print the PWM value
  digitalWrite(leftLauncherDirection ,LOW);                           // Makes the motor turn 
  digitalWrite(rightLauncherDirection ,HIGH);                          // to the speed desired from 0 to 255
  analogWrite(leftLauncherSpeed,launcherSpeed);
  analogWrite(rightLauncherSpeed,launcherSpeed);
}

void goForward (int velocity) {
  Serial.print("Go Forward at");
  Serial.println(100);
  analogWrite(leftWheelSpeed,180);    //180            // Directions need to have opposite polarity for the motor to turn
  digitalWrite(leftWheelDirection1,LOW);                      
  digitalWrite(leftWheelDirection2,HIGH);
  digitalWrite(rightWheelDirection1,LOW);                            
  digitalWrite(rightWheelDirection2,HIGH);
  analogWrite(rightWheelSpeed,230 );    //230        
  
  while (distanceTravelled <= 70){ 
    encoder();
  }
  
  analogWrite(leftWheelSpeed,0);              // Make motor stop  
  digitalWrite(leftWheelDirection1,LOW);                    
  digitalWrite(leftWheelDirection2,LOW);
  digitalWrite(rightWheelDirection1,LOW);                            
  digitalWrite(rightWheelDirection2,LOW);
  analogWrite(rightWheelSpeed,0);    
  Serial.println("Motor stop");
  distanceTravelled = 0;
  angle = 0;
}

void feedBirdie1(int from, int to, int feedDelay){
for (int pos = from; pos <= to; pos += 1){
  feeder1.write(pos);
  delay(feedDelay);
}

}

void feedBirdie2(int from, int to,int feedDelay){
  for (int pos = from; pos <= to; pos += 1){
    feeder2.write(pos);
    delay(feedDelay);
}
}

void encoder (){
   encoderValueA = digitalRead(encoderReaderA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   
   if (encoderValueA != encoderValueB)       // If the outputB state is different to the outputA state, that means the encoder is turning
     {   
      if (digitalRead(encoderReaderB) != encoderValueA) { 
       angle ++;                            // The encoder is rotating clockwise
     } else {
       angle --;                            // The encoder is rotating counter clockwise
     }
     encoderValueB = encoderValueA;
     distanceTravelled = angle*3.3*(pi/20);          // Calculate the distance travelled by the encoder in (cm)
     Serial.print("Distance: ");      
     Serial.print(distanceTravelled);
     Serial.println("cm");
   }
  
}

  /*feedBirdie1(43,69,150);   // First Birdie
  delay(1000);
  feedBirdie1(69,95,150);     // Second Birdie
  delay(1000);
  feedBirdie1(95,121,150);3   // Third Birdie
  delay(1000);
  feedBirdie2(30,60,150);4    // Fourth Birdie
  delay(1000);
  feedBirdie2(60,78,150);5    // Fifth Birdie
  delay(1000);
  feedBirdie2(78,100,150);6   // Sixth Birdie
  delay(1000);*/

