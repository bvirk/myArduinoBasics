#include <CmdLoop.h>
#include <Sendf.h>

namespace slices {
	uint16_t onTime=2100;
	uint16_t offTime=100;
	void goingOn(CmdLoop & cmdLoop) {
		digitalWrite(13,1);
		cmdLoop.setDelay(onTime);
		cmdLoop.next();
	}
	
	void goingOff(CmdLoop & cmdLoop) {
		digitalWrite(13,0);
		cmdLoop.setDelay(offTime);
		cmdLoop.next();
	}

	void (*slicefuncs[])(CmdLoop &) = {goingOn,goingOff};

};

namespace cmdFuncs {
	
	/** 
	  * Very version of this precious mechanism 
	  */
	uint8_t  ver(int argc, char* argv[]) {
		sendf("command loop v0.1\n");
		return 0;
	}
	
	/** 
	  * Like hello world style demo of arguments to main
	  */
	uint8_t printArgs(int argc, char* argv[]) {
		for (uint8_t i = 0; i < argc; i++)
			sendf("%d: >%s<\n",i,argv[i]);
	}

	uint8_t blink(int argc, char* argv[]) {
		if (argc == 3 ) {
			slices::onTime = atoi(argv[1]);
			slices::offTime = atoi(argv[2]);
		} else
			sendf("syntax: blink ontime offtime\n");
	}
	
	/** 
	  * Whole namespace of functions 
	  */
	uint8_t  help(int argc, char *argv[]);

	
	/** 
	  * Array of names to functions 
	  */
	  CommandFunc commands[] = {
		{"ver",ver}
		,{"printargs",printArgs}
		,{"blink",blink}
		,{"help",help}
	};
  
  uint8_t  help(int argc, char *argv[]) {
  	  sendf("Available commands\n");
  	  for (int i=0; i < sizeof(commands)/sizeof(commands[0]); i++)
  	  	  sendf("%s\n",commands[i].name);
  }
};

CmdLoop cmdLoop( 
	 cmdFuncs::commands,sizeof(cmdFuncs::commands)/sizeof(cmdFuncs::commands[0])
	,slices::slicefuncs,sizeof(slices::slicefuncs)/sizeof(slices::slicefuncs[0])
	);

void setup() {
	Serial.begin(9600);
	pinMode(13,OUTPUT);
	sendf("command loop v0.2\n");
	sendf("command: help for viewing commands\n");
	cmdLoop.loop();
}

void loop() { }