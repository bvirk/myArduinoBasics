#ifndef Utils_h
#define Utils_h
#include <stdint-gcc.h>
namespace Utils {
	void hexdump(const void *p, uint16_t size);
	void eepromDump(uint16_t start, uint16_t length);
};
#endif