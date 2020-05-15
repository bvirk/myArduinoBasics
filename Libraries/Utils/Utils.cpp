#include "Utils.h"
#include <Sendf.h>
#include <EEPROM.h>

namespace Utils {
	void hexdump(const void *p, uint16_t size)  {
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
	void eepromDump(uint16_t start, uint16_t length) {
		sendf(F("Address    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n"));
		char ascii[0x11];
		ascii[0x10]='\0';
		for (uint16_t lineStart = start & 0x3f0; (lineStart < 0x400) && (lineStart < start+length); lineStart += 0x10) {
			//printHex(lineStart,8,": ");
			sendf(F("%.8x: "),lineStart);
			for (int8_t col=0; col < 0x10; col++) { 
					uint8_t dumpCh = EEPROM.read(lineStart+col);
					sendf(F("%.2x "),dumpCh);
					ascii[col] = dumpCh < 0x20 ? '.' : dumpCh;
				}
			sendf(F(" |%s|\n"),ascii);
		}
	}

};