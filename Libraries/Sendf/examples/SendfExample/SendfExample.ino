#include "Sendf.h"

void setup() {
	Serial.begin(115200);
	sendf("sendf example\n");

	int maxlen = -1;
	char fmt[] = "%.pf";
	for (int i=30; i; i--) {
        float f = ((float)(500000-(random() % 1000001)))/500000.0*pow(10,(rand() % 21)-10);
        uint8_t preci=rand() % 8;
        Serial.print("Serial.println says: ");
        Serial.println(f,preci);
        fmt[2] = char(preci+48);
        int8_t len = sendff(fmt,f);
        sendf(" (len=%d presision=%d)\n",len,preci);
        if (len > maxlen) 
            maxlen=len;
    }
    sendf("maxlen %d\n",maxlen);
}

void loop() { }