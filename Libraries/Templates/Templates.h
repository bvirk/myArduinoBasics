#ifndef Templates_h
#define Templates_h

#include <EEPROM.h>

/**
  * NEVER, as programmer, burdens yourself with need to remeber
  * syncing copies of anything
  *
  * It seems function template definitions has to be contained in
  * every compilation unit - makes sense it uses defintion to compile 
  * the actual types.
  *
  * Therefore definitions i a header file i a library for common use
  */


template<typename T>void EEPROMRead(uint16_t address, T & object) {
uint8_t* p = (uint8_t*)(void*)&object;
	for (uint8_t i = 0; i < sizeof(object); i++) 
		*p++ = EEPROM.read(address++);
}                                         

template<typename T>void EEPROMWrite(uint16_t address, T value) {
	uint8_t* p = (uint8_t*)(void*)&value;
	for (uint8_t i = 0; i < sizeof(value); i++) {
		if (EEPROM.read(address) != *p) 
			EEPROM.write(address, *p);
		address++,
		p++;
	}
}

template<typename T>T EEPROMValue(uint16_t address) {
	T value = 0;
	uint8_t* p = (uint8_t*)(void*)&value;
	for (uint8_t i = 0; i < sizeof(value); i++)
		*p++ = EEPROM.read(address++);
	return value;
}
#endif