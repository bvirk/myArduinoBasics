#include "Sendf.h"

void hexdump(const char *p, uint16_t size)  {
	sendf(F("Address    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n"));
	char ascii[0x11];
	ascii[0x10]='\0';
	for (unsigned int lineStart = (unsigned int)p & 0xfff0; lineStart < (unsigned int)p+size; lineStart += 0x10) {
		//printHex(lineStart,8,": ");
		sendf(F("%.8x: "),lineStart);
		for (int8_t col=0; col < 0x10; col++) 
			if (lineStart+col < (unsigned int)p || lineStart+col >= (unsigned int)p+size) {
				sendf(F(" . "));
				ascii[col]='.';
			} else {
				uint8_t dumpCh = *(uint8_t *)(lineStart+col);
				sendf(F("%.2x "),dumpCh);
				ascii[col] = dumpCh < 0x20 ? '.' : dumpCh;
			}
		sendf(F(" |%s|\n"),ascii);
	}
}

extern unsigned int __data_start;
extern unsigned int __data_end;
extern unsigned int __bss_start;
extern unsigned int __bss_end;

void setup() {
	Serial.begin(9600);
	uint16_t data_size = unsigned(&__data_end)-unsigned(&__data_start);
	uint16_t bss_size = unsigned(&__bss_end)-unsigned(&__bss_start);
	sendf(F("data: %x-%x : %x (%u)\n"),&__data_start,&__data_end,data_size,data_size);
	sendf(F("bss: %x-%x : %x (%u)\n"),&__bss_start,&__bss_end,bss_size,bss_size);
	sendf(F("\ndata dump\n"));
	hexdump(reinterpret_cast<const char *>(&__data_start),data_size);
	sendf(F("\nbss dump\n"));
	hexdump(reinterpret_cast<const char *>(&__bss_start),bss_size);
	sendff(F("the number PI equals something near %.7f\n"),22.0/7);
}

void loop() { }