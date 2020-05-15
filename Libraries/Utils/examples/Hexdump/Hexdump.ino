#include <Utils.h> 


void setup() {
	Serial.begin(115200);
	Utils::hexdump("Hello world",12);	
}
void loop() {}
