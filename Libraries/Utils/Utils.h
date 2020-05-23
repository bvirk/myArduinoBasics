#ifndef Utils_h
#define Utils_h
#include <stdint-gcc.h>
#include <avr/pgmspace.h>

//! Some Utilities might reflect unfamiliarity with Arduino libraries and standard solutions.
namespace utils {
	void dataHexdump(const void *p, uint16_t size);
	void eepromHexdump(uint16_t start, uint16_t length);
	void pgmHexdump(const void *p, uint16_t size);
	
	//! compare two strings in program space 
	int8_t strcmp_PP(PGM_P s1, PGM_P s2);
};
#endif