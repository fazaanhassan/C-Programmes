// The code below is the basic structure given 
// in the Engduino Tutorials Worksheet.

#include <EngduinoLight.h> 

void setup() {
EngduinoLight.begin(); // Engduino Board starts collecting light data
}

void loop() {
float f;
f = EngduinoLight.lightLevel();
Serial.println(f);    // Prints Values on serial monitor unless another program takes as input
}


