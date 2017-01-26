// The first assignment for the light and interactivity class
// Led fade with an interruption
// Coded by Yeseul Song

#define led 9
#define swtch 8

int brightness = 0;
int fade = 1;

void setup() {
  
  pinMode(led, OUTPUT);
  pinMode(swtch, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  
  brightness+=fade;   
  
  if (brightness >= 255 || brightness <= 0) {    
      fade = -fade;  
  } 
  
  if (digitalRead(swtch) ==  LOW) {
    brightness = 0;
  }
  
  analogWrite(led, brightness);
  delay(5);
  
  Serial.println(digitalRead(swtch));
  
}
