/* 
 * Project Cat Toy and Deterrent Dog Collar
 * Author: Emily Silva
 * Date: 22-OCT-2023
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include HC-SR04.h"
#include "IoTClassroom_CNM.h"

const int trigPin = D9;
const int echoPin = D10;
const int HUEBULB;
int ledPin = D6;
int color;
float duration;
float distance;
bool onOff;
String ONOFF;

SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
//SYSTEM_THREAD(ENABLED);

void setup() {
pinMode (trigPin,OUTPUT);
pinMode (echoPin, INPUT);
pinMode (ledPin, OUTPUT);
pinMode (HUEBULB, OUTPUT);
  Serial.begin(9600);
  waitFor(Serial.isConnected,15000);
  onOff = false;

  WiFi.on();
  WiFi.setCredentials("IoTNetwork");
  WiFi.connect();

  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");
}

void loop() {

//Set the trigPin low for 2 seconds to make sure pin is low. 
//Then, set high for 10 seconds, which sends out an 8 cycle sonic burst from the transmitter, which then bounces of an object and hits the receiver(Which is connected to the Echo Pin).
digitalWrite (trigPin, LOW);
delay (2000);
digitalWrite (trigPin, HIGH);
delay (1000);
digitalWrite (trigPin, LOW);

if (distance <=1){
  Serial.println ("object detected");
  digitalWrite (trigPin, HIGH);//or should this be echoPin?
  delay (3000);
  digitalWrite (ledPin, HIGH);//red LED eyes on the mouse
}
if (distance <=1) { //meaning if dog tag distance remains near cat toy
  setHue(HUEBULB. onOff, HueRed, 55,255);
}
if (distance >1){
  Serial.println ("no object detected");
  digitalWrite (trigPin, LOW);//or should this be echoPin?

  //add in While loop for vibrating component to be set on timer 
  //also add vibrating componet to be manually turned on with movement
}
