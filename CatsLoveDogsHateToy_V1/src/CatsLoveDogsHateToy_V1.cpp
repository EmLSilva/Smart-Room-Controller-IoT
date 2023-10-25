/* 
 * Project Cat Toy and Deterrent Dog Collar
 * Author: Emily Silva
 * Date: 22-OCT-2023
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
//#include "HC-SR04.h"
#include "IoTClassroom_CNM.h"
#include "Button.h"
#include "Adafruit_SSD1306.h"
#include "Grove-Ultrasonic-Ranger.h"

const int sigPin = D16;
//const int echoPin = D16; //removed when previous (2) ultrasonics did not function
const int HUEBULB = 2;
const int BUZZER = D15; 
const int pressed = D10; 
const int MYWEMO=1;
int ledPin = D6; 
int color;
int soundBuzzer = 1500;
float distance ;
bool onOff;
String ONOFF;
Button BUTTON(pressed);
//HC_SR04 rangefinder = HC_SR04(trigPin);
long duration;
int distanceInch;
float inch;
unsigned long currentTime;
unsigned long lastSecond;
long rangeInInches;

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);
Ultrasonic ultrasonic(sigPin);
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
//SYSTEM_THREAD(ENABLED);

void setup() {
//pinMode (sigPin,OUTPUT);
//pinMode (echoPin, INPUT);
pinMode (ledPin, OUTPUT);
pinMode (HUEBULB, OUTPUT);
pinMode (BUZZER, OUTPUT);

Serial.begin(9600);
waitFor(Serial.isConnected,15000);
onOff = false;
//rangefinder.init();

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.setTextSize(1.5);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.display(); 
delay(5000);
display.clearDisplay();
display.display();

WiFi.on();
WiFi.setCredentials("IoTNetwork");
WiFi.connect();

while(WiFi.connecting()) {
  Serial.printf("Connecting, Please Wait.");//added from (.)
}
  Serial.printf("\n\n");
}

void loop() {
  //currentTime = millis();

	rangeInInches = ultrasonic.MeasureInInches();
  Serial.printf("Distance:%d\n", rangeInInches);
	//delay(150);
	//Serial.printf("The distance:%d\n",);

//Set the trigPin low for 2 seconds to make sure pin is low. 
//Then, set high for 10 seconds, which sends out an 8 cycle sonic burst from the transmitter, which then bounces of an object and hits the receiver(Which is connected to the Echo Pin).
//digitalWrite (sigPin, LOW);
//delayMicroseconds (2);
//digitalWrite (sigPin, HIGH);
//delayMicroseconds (10);
//digitalWrite (sigPin, LOW);
//duration = pulseIn(sigPin, HIGH);
//distanceInch = duration*0.0133/2.0;
//inch =  rangefinder.distInch();
//Serial.printf("inch=%f\n",inch);

if ((rangeInInches<5)&&(rangeInInches>0)){
  display.clearDisplay();
    Serial.printf ("dog detected");
   //digitalWrite (sigPin, HIGH);
   //delay (3000);
   digitalWrite (ledPin, HIGH); //red LED eyes on the mouse
   Serial.print(rangeInInches);
   //Serial.printf ("cm"); //removed 25-oct
   //digitalWrite(D15, HIGH);
   tone(BUZZER, soundBuzzer);
   display.printf("BAD DOG <-- <-- <-- cat override button)");
   display.display();
   //display.clearDisplay();
   Serial.printf("Turning on Wemo# %i\n",MYWEMO);//start of fan turning on
   //wemoWrite(MYWEMO,HIGH);
   if ((currentTime-lastSecond)>=10000) {
    if ((rangeInInches<5)&&(rangeInInches>0)) {
      setHue(HUEBULB, true, HueRed, 55,255);
 }
}
}


 if (rangeInInches >5){
   Serial.println ("no dog detected");
   //digitalWrite (sigPin, LOW);//or should this be echoPin?
   noTone(BUZZER);
   digitalWrite (ledPin, LOW); //turn off red LED eyes on the mouse
   display.clearDisplay();
   display.printf("GOOD DOG");
   display.display();
   //delay(2000);
   
   Serial.printf("Turning off Wemo# %i\n",MYWEMO);
   wemoWrite(MYWEMO,LOW);
   //delay(5000);
   }
  if (BUTTON.isClicked()) { //this may need a location ie D6
        onOff = !onOff; 
        }
        setHue(HUEBULB, onOff, HueRed, 55, 255); //this turns bulb on and off
        
if (BUTTON.isClicked()) { //this may need a location ie D6
        onOff = !onOff; 
        }
        setHue(HUEBULB, onOff, HueRed, 55, 255); //this turns bulb on and off
        
        
}

  //add in While loop for vibrating component to be set on timer 
  //also add vibrating componet to be manually turned on with movement
