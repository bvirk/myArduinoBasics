#ifndef Utils_h
#define Utils_h
#include <stdint-gcc.h>
namespace Utils {
	/*! Hexidecimal bytewide dump of ram memory
	  \param p point to lowest memory address which content is showed
	  \param size is length of memory be showed
	  */
    void hexdump(const void *p, uint16_t size);

	
    /*! Hexidecimal bytewide dump of EEPROM memory
	  \param start is lowest memory address which content is showed
	  \param lenght is size of memory be showed
	  */
    void eepromDump(uint16_t start, uint16_t length);
};
#endif