#ifndef TimedErrorLog_h
#define TimedErrorLog_h 
#include <stdint-gcc.h>

#define TIMED_ERROR_LOG_ADDRESS 0
class TimedErrorLog {
	uint32_t secSReset : 24; 	//! seconds sinse reset.
	uint32_t dateTime; 			//! seconds =0, yymmddhhmm of millisOfTime
	int8_t errNr;				//! setted by setError and cleared by construction with parameter timestamp
	uint32_t secAtError: 24;	//! seconds adjustment to secSReset that indicates time of error.
	
	uint32_t secOfYear(uint8_t yy, uint8_t mo, uint8_t dd, uint8_t hh, uint8_t mi, uint8_t *pMonlen);
  	enum twoDecimalDigits {SS=0,NN,HH,DD,MM,YY};

public: 	
  	TimedErrorLog();
  	TimedErrorLog(uint32_t timestamp);
  	enum showmode {SETTEDTIME,NOW,ERROR};
  	bool show(showmode show);
  	void setError(int errorNr);
  	int8_t getError(); 
};

#endif

