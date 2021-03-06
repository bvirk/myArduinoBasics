#ifndef Templates_h
#define Templates_h

// This library is free software; you can redistribute it and/or 
// modify it under the terms of the GNU Lesser General Public 
// License as published by the Free Software Foundation; either 
// version 2.1 of the License, or (at your option) any later version.

#include <EEPROM.h>

/*!
  It seems function template definitions has to be contained in
  every compilation unit - makes sense it uses defintion to compile 
  the actual types.
  
  Therefore definitions in this header file in a library for common use
  */

/*! Initilalize object from EEPROM memory
  \param address of objects persistent data
  \param object the be initialized
  */
template<typename T>void EEPROMRead(uint16_t address, T & object) {
uint8_t* p = (uint8_t*)(void*)&object;
	for (uint8_t i = 0; i < sizeof(object); i++) 
		*p++ = EEPROM.read(address++);
}                                         


/*! Save value to EEPROM memory
  \param address
  \param value to be saved
  */
template<typename T>void EEPROMWrite(uint16_t address, T value) {
	uint8_t* p = (uint8_t*)(void*)&value;
	for (uint8_t i = 0; i < sizeof(value); i++) {
		if (EEPROM.read(address) != *p) 
			EEPROM.write(address, *p);
		address++,
		p++;
	}
}


/*! Read value from EEPROM memory 
  \param address of least significant byte of value
  \return value
  */
template<typename T>T EEPROMValue(uint16_t address) {
	T value;
	uint8_t* p = (uint8_t*)(void*)&value;
	for (uint8_t i = 0; i < sizeof(value); i++)
		*p++ = EEPROM.read(address++);
	return value;
}
#endif