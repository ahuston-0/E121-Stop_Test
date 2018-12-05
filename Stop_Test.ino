#include <Servo.h>
#include <WemosInit.h>

#define Echo D5 //pin that both motor1 and the echo function of the ultrasonic sensor connect to
#define Trig D4 //pin that both motor 2 and the trigger function of the ultrasonic sesor connect to
#define m2   D2
#define m1   D3
Servo motor1;
Servo motor2;
int state = 0; // 0 = forward, 1 = turning
bool debug = true;
int lStop = 82;
int rStop = 91;
int throttle = 29;

void setup() {
  motor1.attach(m1);
  motor2.attach(m2);
  motor1.write(90);
  motor2.write(90);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  if(debug){Serial.begin(9600);}
}

void loop() {
  if(ultrasonicPing(Trig,Echo) < 600){
    state = 1;
  }
  else{
    state = 0;
  }
  //delay(1);
  if (state == 1) {
    motor1.write(90);
    motor2.write(90);
    if(debug){Serial.println("stopped");}
  }
  else if(state == 0){
    motor1.write(rStop - throttle);
    motor2.write(lStop + throttle);
    if(debug){Serial.println("moving forward");}
  }
  if(debug){Serial.println(ultrasonicPing(Trig,Echo));}
}


