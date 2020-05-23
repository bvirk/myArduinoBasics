#include "Utils.h"
#include "Sendf.h"


void setup() {
	Serial.begin(115200);
	utils::dataHexdump("Hello world",12);
	sendf("\n");
	utils::pgmHexdump(F("flash is great"),15);
	sendf("\n");
	utils::eepromHexdump(0,64);
}
void loop() {}
