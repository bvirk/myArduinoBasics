#ifndef TimedErrorLog_h
#define TimedErrorLog_h

// This library is free software; you can redistribute it and/or 
// modify it under the terms of the GNU Lesser General Public 
// License as published by the Free Software Foundation; either 
// version 2.1 of the License, or (at your option) any later version.

#define TIMEDERRORLOGLIBVERSION "0.0.1"

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
	
	uint32_t secOfYear(uint8_t yy, uint8_t mo, uint8_t dd, uint8_t hh, uint8_t mi, uint8_t *pMonlen);
  	enum twoDecimalDigits {SS=0,NN,HH,DD,MM,YY};

  	//! Reestablish from EEPROM   
    TimedErrorLog();
public: 	
	//! Singleton
	static TimedErrorLog & instance();
	
	enum showmode {SETTEDTIME,NOW,ERROR};
  	
  	
    //! Construct an object from a timestamp
    /*!
      \param timestamp is a ten digit integer with format yymmddhhnn (n=mi_n_uts)
      */
  	static void setTime(uint32_t timestamp);
  	
  	
  	//! Report serially time or error number
  	/*!
  	  \param show is one off above enums
  	  - SETTEDTIME 
  	  - NOW
  	  - ERROR
  	  and reflects respectively time of construction, current time and time of logged error
  	*/
  	static bool show(showmode show);
  	
  	//! Assign an error
  	int8_t operator = (short);
  	
  	//! get the error number using short(error), where error is an object in this compilation unit
  	operator short() const;
  	
  	//! get info about a present error usinf if(error),  where error is an object in this compilation unit
  	operator bool() const;
};
extern TimedErrorLog & error; 	//!< makes object available compilation units where this header is included 

#endif

