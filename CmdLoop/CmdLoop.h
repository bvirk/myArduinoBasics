/**
  * Simultaniously Retrieves command from serial and invoke named command, and
  * run function timeSlice()
  */
class CmdLoop {
	#define COMMAND_SIZE 64
	char command[COMMAND_SIZE];
	#define MAX_ARG_COUNT 6
	
	uint8_t argc;
	char *argv[MAX_ARG_COUNT];
	uint8_t cmdsCount;
	uint8_t exitLevel;

	void getCmdAndTimeSlice();
	void timeSlice() { }
  
  public:
  	CmdLoop();
  	
  	/**
  	  * Infinite loop
  	  */
  	void loop();	  
};
	
