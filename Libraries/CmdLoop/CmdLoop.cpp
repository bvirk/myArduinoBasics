#include "Arduino.h"
#include "CmdLoop.h"
#include "Sendf.h"
#include <avr/pgmspace.h>
	
const uint32_t defaultDelay=1000;
int8_t pin13State=0;

	

/** 
  * main style arglist and return value 'commands' functions. The functions are meant to be used as remote shell comands, 
  * invoked by named equality of argv[0] 
  */

  CmdLoop::CmdLoop( CommandFunc * cmdFunc, uint8_t commandsCount, void (*tslice[])(CmdLoop &), uint8_t tsliceCount) 
  	: cmdFuncs(cmdFunc),cmdsCount(commandsCount),forRepeatSaved('\0')
  	,sliceDelay(defaultDelay),timeSlices(tslice),timeSlicesCount(tsliceCount),timeSliceIndex(0) {
	sliceStart = millis();
	argv[0]=command;
	
}


inline void CmdLoop::getCmdAndTimeSlice() {
	uint8_t cmdNPos=0;
	while (true) {
		timeSlice();	
		
		if (Serial.available()) {
			uint8_t inp = Serial.read();
			if (inp != 10 && inp != 13 && cmdNPos < COMMAND_SIZE-1) 
				command[cmdNPos++] = inp;
			if ( inp == 10 || inp == 13 || cmdNPos == COMMAND_SIZE-1) {
				// we got line with a command with possible arguments
				// cmdNPos is its length
				if ( forRepeatSaved && cmdNPos == 1 && command[0] == '.') {
					command[0]=forRepeatSaved;
					return;
				} else { // not a repeat command or no prior command[0] saved  	
					command[cmdNPos] = '\0';
					argc = 1;
					for (uint8_t cmdPos=0; cmdPos < cmdNPos; cmdPos++)
						if (command[cmdPos] == ' ')
							command[cmdPos] = '\0';
						else
							if (cmdPos && command[cmdPos-1] == '\0' ) {
								argv[argc++] = &command[cmdPos];
								if (argc == MAX_ARG_COUNT)
									break; // for loop
							}
				} // end else no repeat comannd
				if (cmdNPos > 1) 
					forRepeatSaved = command[0];
				return;
			} // lineshift or buffer full
		} // serial.available
	} // end while
}

inline void CmdLoop::timeSlice() {
	uint32_t millisNow = millis();
	if (sliceStart+sliceDelay > millisNow)
		return;
	(timeSlices[timeSliceIndex])(*this);
	sliceStart=millisNow;
}

void CmdLoop::setDelay(uint32_t delay) {
	sliceDelay=delay;
}

void CmdLoop::next() {
	timeSliceIndex++;
	if (timeSliceIndex < timeSlicesCount)
		return;
	timeSliceIndex=0;
}
void CmdLoop::prev() {
	timeSliceIndex--;
	if (timeSliceIndex <= 0)
		return;
	timeSliceIndex=timeSlicesCount-1;
}

void CmdLoop::loop() {
	strcpy_P(command,reinterpret_cast<PGM_P>(F("autoexec")));
	argc=1;
	while (true) {
		uint8_t cmdsPos;
		for (cmdsPos=0; cmdsPos < cmdsCount; cmdsPos++)
		  if (strcmp(argv[0],cmdFuncs[cmdsPos].name)==0) {
		  	  exitLevel = (cmdFuncs[cmdsPos].f)(argc,argv);
		  	  sendf(F(" %d\n"),exitLevel);
		  	  break;
		  }
		if (cmdsPos == cmdsCount)
			sendf(F("Command not found: %s\n"),command );
		getCmdAndTimeSlice();
	}
}
