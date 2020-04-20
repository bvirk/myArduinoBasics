#include "Arduino.h"
#include "CmdLoop.h"
	
/** 
  * main style arglist and return value 'commands' functions. The functions are meant to be used as remote shell comands, 
  * invoked by named equality of argv[0] 
  */
namespace cmdFuncs {
	
	/** 
	  * Very version of this precious mechanism 
	  */
	uint8_t  ver(int argc, char* argv[]) {
		Serial.println("command loop v0.1");
		return 0;
	}
	
	/** 
	  * Like hello world style demo of arguments to main
	  */
	uint8_t printArgs(int argc, char* argv[]) {
		Serial.println(argv[0]);
		for (uint8_t i = 1; i < argc; i++) {
			Serial.print(i);
			Serial.print(": >");
			Serial.print(argv[i]);
			Serial.println("<");
		}
	}
	
	/** 
	  * Whole namespace of functions 
	  */
	uint8_t  help(int argc, char *argv[]);

	
	/** 
	  * Array of names to functions 
	  */
	struct {
		const char *name;
		uint8_t (*f)(int,char**);
	} commands[] = {
		{"ver",ver}
		,{"printargs",printArgs}
		,{"help",help}
	};
  
  uint8_t  help(int argc, char *argv[]) {
  	  Serial.println(F("Available commands"));
  	  for (int i=0; i < sizeof(commands)/sizeof(commands[0]); i++)
      Serial.println(commands[i].name);
  }
};
		

CmdLoop::CmdLoop() {
	argv[0]=command;
	cmdsCount = sizeof(cmdFuncs::commands)/sizeof(cmdFuncs::commands[0]);
}


inline void CmdLoop::getCmdAndTimeSlice() {
	uint8_t cmdNPos=0;
	while (true) {
		timeSlice();	
		
		if (Serial.available()) {
			uint8_t inp = Serial.read();
			if (inp != 10 && inp != 13 && cmdNPos < COMMAND_SIZE-1)  {
				command[cmdNPos++] = inp;
			}
			if ( inp == 10 || inp == 13 || cmdNPos == COMMAND_SIZE-1) {
				// we got line with a command with possible arguments
				// cmdNPos is its the length
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
				return;
			} // lineshift or buffer full
		} // serial.available
	} // end while
}

void CmdLoop::loop() {
    while (true) {
		getCmdAndTimeSlice();
		uint8_t cmdsPos;
		for (cmdsPos=0; cmdsPos < cmdsCount; cmdsPos++)
		  if (strcmp(argv[0],cmdFuncs::commands[cmdsPos].name)==0) {
			exitLevel = (cmdFuncs::commands[cmdsPos].f)(argc,argv);
			break;
		  }
		if (cmdsPos == cmdsCount) {
		  Serial.print("Command not found: " );
		  Serial.println(command);
		}
	}	
}
