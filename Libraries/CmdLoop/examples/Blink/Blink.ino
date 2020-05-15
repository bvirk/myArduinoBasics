#include <CmdLoop.h>
#include <Sendf.h>

namespace slices {
	uint16_t onTime=2000; 
	uint16_t offTime=300;
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
	int8_t  ver(int argc, char* argv[]) {
		sendf(F("command loop v0.1\n"));
		return 0;
	}

	int8_t blink(int argc, char* argv[]) {
		if (argc == 3 ) {
			slices::onTime = atoi(argv[1]);
			slices::offTime = atoi(argv[2]);
			return 0;
		} 
		return -1;
	}
	
	
	/** 
	  * Array of names to functions 
	  */
	  CommandFunc commands[] = {
		 {blink,"blink"}
		,{ver,"ver"}
		,{ver,"ver"} // or link error???
	};
  
};

CmdLoop cmdLoop( 
	 cmdFuncs::commands,sizeof(cmdFuncs::commands)/sizeof(cmdFuncs::commands[0])
	,slices::slicefuncs,sizeof(slices::slicefuncs)/sizeof(slices::slicefuncs[0])
	);

void setup() {
	Serial.begin(115200);
	pinMode(13,1);
	sendf(F("syntax: blink ontime offtime"));
	cmdLoop.loop();
}

void loop() { }