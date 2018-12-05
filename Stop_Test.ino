#include <Servo.h>
#include <WemosInit.h>

/*Pin Definitions: 
 * Echo/Trig belong to the ultrasonic sensor
 * m1 and m2 belong to motor 1 (left) and motor 2 (right) respectively
 */
#define Echo D5 
#define Trig D4
#define m2   D2
#define m1   D3

//initialize the motor objects
Servo motor1;
Servo motor2;


int state = 0; //0 = forward, 1 = turning
bool debug = true; //if true: prints states to the serial monitor
int lStop = 82; //"stops" trimmed for drift so the bot drives straight
int rStop = 91;
int throttle = 29;

/*Initialization procedure:
 * Setup motors, stop the bot from moving, connect any sensors, setup debugging
 */
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
  if(ultrasonicPing(Trig,Echo) < 600){ //if a wall is a foot away stop, otherwise keep going
    state = 1;
  }
  else{
    state = 0;
  }
  if (state == 1) { //stop the bot
    motor1.write(90);
    motor2.write(90);
    if(debug){Serial.println("stopped");}
  }
  else if(state == 0){ // go straight
    motor1.write(rStop - throttle);
    motor2.write(lStop + throttle);
    if(debug){Serial.println("moving forward");}
  }
  if(debug){Serial.println(ultrasonicPing(Trig,Echo));}
}
