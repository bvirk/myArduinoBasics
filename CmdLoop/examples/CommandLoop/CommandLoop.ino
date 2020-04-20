#include <CmdLoop.h> 

CmdLoop cmdLoop;

void setup() {
  Serial.begin(9600);
  Serial.println("command loop v0.1");
  cmdLoop.loop();
}

void loop() { }