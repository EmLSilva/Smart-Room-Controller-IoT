/* 
 * Project Cat Toy and Deterrent Dog Collar
 * Author: Emily Silva
 * Date: 22-OCT-2023
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "Button.h"
#include "Adafruit_SSD1306.h"
#include "Grove-Ultrasonic-Ranger.h"

const int sigPin = D16;
const int HUEBULB = 2;
const int BUZZER = D15; 
const int CATBUTTON = D10; 
const int MYWEMO=1;
int ledPin = D6; 
int color;
int soundBuzzer = 1500;
float distance ;
bool onOff;
String ONOFF;
Button catButton(CATBUTTON);
long duration;
int distanceInch;
float inch;
long rangeInInches;

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);
Ultrasonic ultrasonic(sigPin);
SYSTEM_MODE(SEMI_AUTOMATIC);


void setup() {
pinMode (ledPin, OUTPUT);
pinMode (HUEBULB, OUTPUT);
pinMode (BUZZER, OUTPUT);
pinMode (CATBUTTON, INPUT); //added 10.26
onOff = false; //new 10.26

Serial.begin(9600);
waitFor(Serial.isConnected,15000);
onOff = false;
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.display(); 
delay(1000);
//display.clearDisplay();
//display.display();

WiFi.on();
WiFi.setCredentials("IoTNetwork");
WiFi.connect();

while(WiFi.connecting()) {
  Serial.printf("Connecting, Please Wait.");
}
  Serial.printf("\n\n");
}

void loop() {
  
	rangeInInches = ultrasonic.MeasureInInches();
  Serial.printf("Distance:%d\n", rangeInInches);
	
if ((rangeInInches<5)&&(rangeInInches>0)){
   Serial.printf ("dog detected");
   digitalWrite (ledPin, HIGH); //red LED eyes on the mouse
   tone(BUZZER, soundBuzzer);
   display.clearDisplay();
   display.setCursor(40,10);
   display.printf("BAD DOG \n \n <-- <-- <-- <-- <--\n \n CAT OVERRIDE BUTTON \n <-- <-- <-- <-- <--");
   display.display();
   Serial.printf("Turning on Wemo# %i\n",MYWEMO);//start of fan turning on
   wemoWrite(MYWEMO,HIGH);
   setHue(HUEBULB, true, HueRed, 55,255);
   setHue(HUEBULB, true, HueRed, 255);

 }


 if ((rangeInInches >5)||(rangeInInches==0)) {
  setHue(HUEBULB, true, HueBlue, 55,255);
   Serial.println ("no dog detected");
   noTone(BUZZER);
   digitalWrite (ledPin, LOW); //turn off red LED eyes on the mouse
   display.clearDisplay();
   display.setCursor(40,10);
   display.printf("GOOD DOG");
   display.display();
   Serial.printf("Turning off Wemo# %i\n",MYWEMO);
   wemoWrite(MYWEMO,LOW);
  
   }

  if (catButton.isClicked()) { 
        onOff = !onOff; 
        ONOFF = String (onOff);
        Serial.println ("cat override");
        setHue(HUEBULB, true, HueBlue, 55,255);
        noTone(BUZZER);
        digitalWrite (ledPin, LOW); //turn off red LED eyes on the mouse
        display.clearDisplay();
        display.setCursor(40,10);
        display.printf("CATS RULE");
        display.display();
        Serial.printf("Turning off Wemo# %i\n",MYWEMO);
        wemoWrite(MYWEMO,LOW);
        delay (10000);
  }
}

  //add in While loop for vibrating component to be set on timer 
  //also add vibrating componet to be manually turned on with movement
