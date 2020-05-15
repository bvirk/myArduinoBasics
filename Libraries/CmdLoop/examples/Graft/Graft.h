	
#define TIMESYNC_ADDRESS 0
class TimeSync {
	uint32_t secSReset : 24; 	//! seconds sinse reset.
	uint32_t dateTime; 			//! seconds =0, yymmddhhmm of millisOfTime
	int8_t errNr;
	uint32_t secAtError: 24;
	
	void EEClone();
  	//! constructs class from EEPROM Address
  	uint32_t secOfYear(uint8_t yy, uint8_t mo, uint8_t dd, uint8_t hh, uint8_t mi, uint8_t *pMonlen);
  	enum twoDecimalDigits {SS=0,NN,HH,DD,MM,YY};

public: 	
  	TimeSync();
  	
  	
  	//! \param timestamp has format yymmddhhnn - nn for minuts
  	TimeSync(uint32_t timestamp);
  	enum showmode {SETTEDTIME,NOW,ERROR};
  	void show(showmode show);
  	void setError(int errorNr);
  	void showError(); 
  	
};
