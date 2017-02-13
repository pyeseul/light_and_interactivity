/* 
  A candle without a candle 
  - A NeoPixel randomly flickers mimicking the flame of a candle.
  - A microphone sensor receives a value and the value make changes in the brightness, flickering, color of the NeoPixel.

  The code is written based on Tom Igoe's RGBW Neopixel fade control code: 
  https://github.com/tigoe/NeoPixel_examples/blob/master/NeoPixelWhiteFade/NeoPixelWhiteFade.ino

  I used a NeoPixel Jewel and a FC-109 (MAX9812) microphone amplifier module with an Arduino.
  
  created in Feb 2017 by Yeseul Song
*/


#include <Adafruit_NeoPixel.h>

const int neoPixelPin = 5;  // control pin
const int numPixels = 7;    // number of pixels
int level1 = 255;            // the white LED color for the whole strip
int difference = 1;         // the fading difference in each loop

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, neoPixelPin, NEO_GRBW + NEO_KHZ800);

// microphone sensor
const int inputPin = A0;
const int inputWindow = 100;
unsigned int sensorVal;

// interval
unsigned long previousMillis = 0; 
unsigned long interval = 1000;    

// turn on and off
boolean on = true;

void setup() {
  
  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  pinMode(0, OUTPUT);
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
  
}

void loop() {

  if (on == true) {
    float mapped = 0;
    
    for (unsigned int i = 0; i < inputWindow; i++) {
      
      // read the sensor value
      sensorVal = analogRead(inputPin);    
    }

    // map the microphone sensor value 
    mapped = map(sensorVal, 80, 1024, 0, 60);
      
    unsigned long currentMillis = millis();
    interval = random(60-mapped, 85-mapped);
    
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      strip.setBrightness(255-mapped*4); // set the brightness for this pixel
      strip.setPixelColor(0, 255, 30, 0, level1); // set the color for this pixel  
      strip.show();    // refresh the strip
      
      level1 = random(200)+55-mapped;
      
      Serial.println(mapped);

      // turn of the candle if mapped sensor value is equal to or bigger than 54
      if (mapped >= 54) {
        if (random(5) < 1) {
          on = false;
        }
      }       
    }
  } else {
      strip.setBrightness(0); 
      strip.show();  
    }
}
          

