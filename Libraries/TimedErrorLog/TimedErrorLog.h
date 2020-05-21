#ifndef TimedErrorLog_h
#define TimedErrorLog_h 
#include <stdint-gcc.h>

#define TIMED_ERROR_LOG_ADDRESS 0

//! Byond reset, one item error log.
/*!  
  The saved time denoted error consisting of a single 8 bit number.
  The used 11 bytes EEPROM memory is the real object reestablished by default construction. An error number can only be set one
  time and survives reset. To enable being able to recieve an error number, a constuction with parameter time must be
  (re)performed. A device on which a TimeErrorLog newer has been constructed will on default construction have bogus settings.
  */
class TimedErrorLog {
	uint32_t secSReset : 24; 	//!< seconds sinse reset.
	uint32_t dateTime; 			//!< seconds =0, yymmddhhmm of millisOfTime
	int8_t errNr;				//!< setted by setError and cleared by construction with parameter timestamp
	uint32_t secAtError: 24;	//!< seconds adjustment to secSReset that indicates time of error.
	
	static uint32_t secOfYear(uint8_t yy, uint8_t mo, uint8_t dd, uint8_t hh, uint8_t mi, uint8_t *pMonlen);
  	enum twoDecimalDigits {SS=0,NN,HH,DD,MM,YY};

  	//! Reestablish that object EEPROM contains  
    TimedErrorLog();
    static TimedErrorLog & instance();
public: 	
  	
    //! Construct an object from a timestamp
    /*!
      \param timestamp is a ten digit integer with format yymmddhhnn (n=mi_n_uts)
      */
  	static void setTime(uint32_t timestamp);
  	
  	
  	enum showmode {SETTEDTIME,NOW,ERROR};
  	
  	
  	//! Report serially time or error number
  	/*!
  	  \param show is one off
  	  - SETTEDTIME 
  	  - NOW
  	  - ERROR
  	  and reflects respectively time of construction, current time and time of logged error
  	  */
  	static bool show(showmode show);
  	
  	
  	//! Set the error number
  	static void setError(int errorNr);
  	
  	//! Get the error number.
  	static int8_t getError(); 
};

#define error TimedErrorLog::getError()
#endif

