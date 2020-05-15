#ifndef CmdLoop_h
#define CmdLoop_h

struct CommandFunc {
		int8_t (*f)(int,char**);
		const char * name;
}; 

	
/**
  * Simultaniously Retrieves command from serial and invoke named command, and
  * run function timeSlice()  
  */
class CmdLoop {
	#define COMMAND_SIZE 64
	char command[COMMAND_SIZE];		//! buffer seriel input as that line that get '\0' bytes to split in args
	#define MAX_ARG_COUNT 6
	
	char forRepeatSaved;			//! A single char in command[0] acts as repeat last, replacing command[0] 
									//! with the prior saved command[0] as forRepeatSaved
	
	uint8_t argc;					//! detected numbers of arguments
	char *argv[MAX_ARG_COUNT];		//! array of pointer to '\0' bytes terminatet string(s) in command
	CommandFunc *cmdFuncs;			//! pointer to first item in array of struct CommandFunc's
	uint8_t cmdsCount;
	int8_t exitLevel;				//! exitlevel of last executed command
	
	void (**timeSlices)(CmdLoop &);	//! Array of pointers to timeSlice functions
	uint8_t timeSlicesCount;
	int8_t timeSliceIndex;			//! index  of that timeSlice that will get thread of execution next time
	uint32_t sliceStart;    		//! milliseconds sinse boot of last slice sceduling 
	uint32_t sliceDelay;			//! delay before timeslice() is called again
	
	//! runs timeslice() and read from serial if characters is avail
	void getCmdAndTimeSlice();
	
	
	
	//! schedules a slice on delay elapsed.
	
	//! the slice is responsible for calling next() for running next slice on next scheduling  
	void timeSlice();
  
  public:
  	//! constructer
  	
  	//! \param cmdFunc point to first item in array of CommandFunc stuctures
  	//! \param commandsCount of CommandFunc stuctures
  	//! \param (*tslice[]) array of functions to be scheduled by timeSlice(); 
  	//! \param tsliceCount of slices
  	CmdLoop( CommandFunc * cmdFunc, uint8_t commandsCount, void (*tslice[])(CmdLoop &), uint8_t tsliceCount);
  	
  	//! Infinite loop of running getCmdAndTimeSlice();
  	void loop();
  	
  	//! Sets delay until next slice running
  	
  	//! \param delay in milliseconds from value in sliceStart before next slice gets thread of execution
  	void setDelay(uint32_t delay);
  	
  	//! schedule next slice on next execution of timeSlice()
  	
  	//! As long as this is not called by execution of a slice, that same slice will get thead of execution on all execution 
  	//! of timeslice()
  	void next();
  	
  	//! makes  previous slice the one that is called next.
  	void prev();
  	
};
	
#endif