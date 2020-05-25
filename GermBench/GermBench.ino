#include <CmdLoop.h>
#include <Sendf.h>
#include <EEPROM.h>
#include "TimedErrorLog.h"
#include <avr/pgmspace.h>
#include "Templates.h"
#include "Utils.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9
#define EARTH_SERIAL 0x8102162CBF22EE28
#define AIR_SERIAL   0x36021616B726EE28
#define DS1820_DEVICE_COUNT 2

enum {ERROR_READ_DS18B22_DEVICE=1,ERROR_DALLASTEMPERATURE_GETADDRESS};


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DeviceAddress devAddr[2];

float heatSwitchTemp;
float  fanSwitchTemp;

#define FAN_CONTROL_PIN 11
#define HEAT_CONTROL_PIN 12
#define FAN_ON 1
#define FAN_OFF 0
#define HEAT_ON 1
#define HEAT_OFF 0

int8_t address64Index(uint64_t addr) {
	for (int8_t i=0; i < DS1820_DEVICE_COUNT;i++) 
		if (*(uint64_t*)&devAddr[i] == addr )
			return i;
	error = ERROR_READ_DS18B22_DEVICE;
	return -1;  
}
