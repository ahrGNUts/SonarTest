// uses HC-SR04 ultrasonic sensor from Sparkfun
// example code is here:
// https://codebender.cc/sketch:356078#HC-SR04%20Ultrasonic%20Sensor%20Example.ino
// datasheet is here: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf

// this is helpful info about the shift register being used
// http://www.goodliffe.org.uk/arduino/shift.php


// bottom graph LED pins (arduino)
const int TEN = 8;
const int NINE = 9;

// IC pins
const int DATA = 12;
const int CLOCK = 10;
const int LATCH = 11;

// ultrasonic pins
const int TRIG = 6;
const int ECHO = 7;

// for writing data to chip
boolean out[8];

// max range for ultrasonic sensor (400cm)
const unsigned int MAX = 23200;

void setup() {
  Serial.begin(9600);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(NINE, OUTPUT);
  pinMode(TEN, OUTPUT);
  pinMode(TRIG, OUTPUT);
  //pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);

  for(int i = 0; i < 7; i++){
    out[i] = false;
  }
}

void loop() {
  unsigned long t1;
  unsigned long t2;
  unsigned long pulseWidth;
  float cm;

  // trigger held for at least 10 microseconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // wait for echo pulse
  while(digitalRead(ECHO) == 0);

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO) == 1);
  t2 = micros();
  pulseWidth = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  //of sound in air at sea level (~340 m/s).
  cm = pulseWidth / 58.0;

    //debug
  // Print out results
  if ( pulseWidth > MAX ) {
    Serial.println("Out of range");
  } else {
    Serial.print(cm);
    Serial.println(" cm");
  }

  if(cm < 10) {
    writeICPins(0);
    writeDigitalPins(1);
  }
  else if(cm > 10 && cm < 20) {
    writeICPins(0);
    writeDigitalPins(2);
  }
  else if(cm > 20 && cm < 30){
    writeICPins(1);
    writeDigitalPins(2);
  }
  else if(cm > 30 && cm < 40) {
    writeICPins(2);
    writeDigitalPins(2);
  }
  else if(cm > 40 && cm < 50){
    writeICPins(3);
    writeDigitalPins(2);
  }
  else if(cm > 50 && cm < 60){
    writeICPins(4);
    writeDigitalPins(2);
  }
  else if(cm > 60 && cm < 70){
    writeICPins(5);
    writeDigitalPins(2);
  }
  else if(cm > 70 && cm < 80){
    writeICPins(6);
    writeDigitalPins(2);
  }
  else if(cm > 80 && cm < 90){
    writeICPins(7);
    writeDigitalPins(2);
  }
  else if(cm > 90){
    writeICPins(8);
    writeDigitalPins(2);
  }
  
  // Wait at least 250ms before next measurement
  delay(250);
  
}

void writeDigitalPins(int numPins){
  if(numPins == 1){
    digitalWrite(TEN, HIGH);
    digitalWrite(NINE, LOW);
  }
  else if(numPins == 2) {
    digitalWrite(NINE, HIGH);
    digitalWrite(TEN, HIGH);
  }
  else{
    digitalWrite(NINE, LOW);
    digitalWrite(TEN, LOW);
  }
}


void writeICPins(int numLEDs) {
  digitalWrite(LATCH, LOW);

  if(numLEDs == 0){
    for(int i = 7; i >=0; i--){
      out[i] = false; 
    }
  }// the following isn't the prettiest way to do this, but it works
   // wouldn't be the best choice for a larger shift register though
  else if(numLEDs == 1){
    out[7] = true;
    out[6] = false;
    out[5] = false;
    out[4] = false;
    out[3] = false;
    out[2] = false;
    out[1] = false;
    out[0] = false;
  }
  else if(numLEDs == 2){
    out[7] = true;
    out[6] = true;
    out[5] = false;
    out[4] = false;
    out[3] = false;
    out[2] = false;
    out[1] = false;
    out[0] = false;
  }
  else if(numLEDs == 3){
    out[7] = true;
    out[6] = true;
    out[5] = true;
    out[4] = false;
    out[3] = false;
    out[2] = false;
    out[1] = false;
    out[0] = false;
  }
  else if(numLEDs == 4){
    out[7] = true;
    out[6] = true;
    out[5] = true;
    out[4] = true;
    out[3] = false;
    out[2] = false;
    out[1] = false;
    out[0] = false;
  }
  else if(numLEDs == 5){
    out[7] = true;
    out[6] = true;
    out[5] = true;
    out[4] = true;
    out[3] = true;
    out[2] = false;
    out[1] = false;
    out[0] = false;
  }
  else if(numLEDs == 6){
    out[7] = true;
    out[6] = true;
    out[5] = true;
    out[4] = true;
    out[3] = true;
    out[2] = true;
    out[1] = false;
    out[0] = false;
  }
  else if(numLEDs == 7){
    out[7] = true;
    out[6] = true;
    out[5] = true;
    out[4] = true;
    out[3] = true;
    out[2] = true;
    out[1] = true;
    out[0] = false;
  }
  else if(numLEDs == 8){
    out[7] = true;
    out[6] = true;
    out[5] = true;
    out[4] = true;
    out[3] = true;
    out[2] = true;
    out[1] = true;
    out[0] = true;
  }

  for(int i = 7; i >= 0; i--){
    digitalWrite(CLOCK, LOW);
    digitalWrite(DATA, out[i]);
    digitalWrite(CLOCK, HIGH);
  }

  digitalWrite(LATCH, HIGH);
}

