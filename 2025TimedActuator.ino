/*
 Example sketch for the Logitech F310 gamepad
 */

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#include <SPI.h>
#include "lf310.h"

USB Usb;
LF310 lf310(&Usb);

bool controllerCheck = false;

const int valvePin4 = 8;
const int valvePin3 = 7;
const int valvePin2 = 6;
const int valvePin1 = 5;

int minTime = 5000;

int ledPin = LED_BUILTIN;
int ledState = HIGH;

unsigned long previousMillis = 0; //Stores solemoid toggle value
const long interval = 1000; //Interval at which to toggle
const unsigned frequency_ms = 100; //Pulse width for relays

unsigned long currentMillis;
unsigned long time;
unsigned long blowTime;

void setup() {
        delay(1000);
        Serial.begin(115200);
        Serial.println("Setup Entered");

        pinMode(valvePin1, OUTPUT);
        pinMode(valvePin2, OUTPUT);
        pinMode(valvePin3, OUTPUT);
        pinMode(valvePin4, OUTPUT);
        pinMode(ledPin, OUTPUT);

        digitalWrite(valvePin1, HIGH);
        digitalWrite(valvePin2, HIGH);
        digitalWrite(valvePin3, HIGH);
        digitalWrite(valvePin4, HIGH);
        digitalWrite(ledPin, HIGH);

        while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
        
        Serial.println("Starting Logitech F310 gamepad");

        if (Usb.Init() == -1)
          Serial.println("OSC did not start. (-1)");
        if(Usb.Init() == 1)
          Serial.println("Failure (1)");
        if(Usb.Init() == 0)
          Serial.println("USB Host Shield Init Sucessful");

        delay(200);
       
}

void loop() {
  Usb.Task();
  currentMillis = millis();

  if(lf310.connected() && !controllerCheck){
          Serial.println("Controller Connected!");
          controllerCheck = true;
          }

  if(lf310.connected()){

    if(lf310.buttonClickState.Abutton && time + blowTime > currentMillis){
      digitalWrite(valvePin1, LOW);
      Serial.println("A");
      time = currentMillis;
      //lf310.buttonClickState.Abutton = 0;
    } else if (time + blowTime > currentMillis){
      digitalWrite(valvePin1, HIGH);
    }

    if(lf310.buttonClickState.Bbutton && time + blowTime > currentMillis){
      digitalWrite(valvePin2, LOW);
      Serial.println("B");
      time = currentMillis;
      //lf310.buttonClickState.Bbutton = 0;
    } else if (time + blowTime > currentMillis){
      digitalWrite(valvePin2, HIGH);
    }

    if(lf310.buttonClickState.Ybutton && time + blowTime > currentMillis){
      digitalWrite(valvePin3, LOW);
      Serial.println("Y");
      time = currentMillis;
      //lf310.buttonClickState.Ybutton = 0;
    } else if (time + blowTime > currentMillis){
      digitalWrite(valvePin3, HIGH);
    }

    if(lf310.buttonClickState.Abutton && time + blowTime > currentMillis){
      digitalWrite(valvePin4, LOW);
      Serial.println("X");
      time = currentMillis;
      //lf310.buttonClickState.Xbutton = 0;
    } else if (time + blowTime > currentMillis){
      digitalWrite(valvePin4, HIGH);
    }

  }
}