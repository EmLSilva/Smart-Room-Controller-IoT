/* 
 * Project Cat Toy and Deterrent Dog Collar (TBD)
 * Author: Emily Silva
 * Date: 22-OCT-2023
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "Button.h"
#include "Adafruit_SSD1306.h"
#include "Grove-Ultrasonic-Ranger.h"

const int sigPin = D16;
const int HUEBULB = 2;
//const int HUEBULB[] = {1,2,3,4,5,6}; Six (6) Hue bulbs, commented out due to delay
const int BUZZER = D15; 
const int CATBUTTON = D10; 
const int MYWEMO=1;
int numBulbs; //added 10.27
int ledPin = D6; 
int color;
int soundBuzzer = 1500;
int distanceInch;
float distance;
float inch;
bool onOff;
//bool hueOnOff; To operate six (6) Hue bulbs, commented out due to delay
String ONOFF;
Button catButton(CATBUTTON);
long duration;
long rangeInInches;
//unsigned long currentTime; To operate six (6) Hue bulbs, commented out due to delay
//unsigned long lastSecond; To operate six (6) Hue bulbs, commented out due to delay
//void hueFill(int startHue, int endHue, int color, bool onOff); To operate six (6) Hue bulbs, commented out due to delay

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);
Ultrasonic ultrasonic(sigPin);
SYSTEM_MODE(SEMI_AUTOMATIC);


void setup() {
pinMode (ledPin, OUTPUT);
pinMode (HUEBULB, OUTPUT);
pinMode (BUZZER, OUTPUT);
pinMode (CATBUTTON, INPUT); 
onOff = false; 

Serial.begin(9600);
waitFor(Serial.isConnected,15000);
onOff = false;
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.display(); 
delay(1000);

WiFi.on();
WiFi.setCredentials("IoTNetwork");
WiFi.connect();

while(WiFi.connecting()) {
  Serial.printf("Connecting, Please Wait.");
}
  Serial.printf("\n\n");
}

void loop() {
//currentTime=millis(); To operate six (6) Hue bulbs, commented out due to delay
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
   Serial.printf("Turning on Wemo# %i\n",MYWEMO);//wemo turning fan on
   wemoWrite(MYWEMO, HIGH);
   setHue(HUEBULB, TRUE, HueRed, 55, 255);
   setHue(HUEBULB, TRUE, HueRed, 255);

}
   
   //if ((currentTime-lastSecond)>5000) { To operate six (6) Hue bulbs, commented out due to delay
     //lastSecond=millis();
     //hueOnOff = !hueOnOff;
     //hueFill(0,2,HueRed, hueOnOff);
     //hueFill(3,6, HueRed, !hueOnOff);
    //}
  

 if ((rangeInInches >5)||(rangeInInches==0)) {
   setHue(HUEBULB, true, HueBlue, 55,255);
   //hueFill(0,6,HueBlue, true); To operate six (6) Hue bulbs, commented out due to delay
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
        setHue(HUEBULB, true, HueBlue, 55, 255);
        //hueFill(0,6,HueBlue, true); To operate six (6) Hue bulbs, commented out due to delay
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
  //FUTURE ADD: while loop for vibrating component to be set on timer 
  //FUTURE ADD: vibrating componet to be manually turned on with movement
  //FUTURE ADD: dog collar to sense difference in "whom's" movement should be detected

//void hueFill(int startHue, int endHue, int color, bool onOff){ To operate six (6) Hue bulbs, commented out due to delay
      //for(numBulbs=startHue; numBulbs<endHue; numBulbs++) { 
     //   setHue(HUEBULB[numBulbs], onOff, color, 55,255);
     // }
