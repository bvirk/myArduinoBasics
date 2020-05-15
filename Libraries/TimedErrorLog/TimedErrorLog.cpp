#include "TimedErrorLog.h"
#include "Templates.h"
#include <wiring.c>
#include "Sendf.h"


TimedErrorLog::TimedErrorLog() {
	EEPROMRead<TimedErrorLog>(TIMED_ERROR_LOG_ADDRESS,*this);
}
	
TimedErrorLog::TimedErrorLog(uint32_t timestamp) { 
	secSReset = millis()/1000;
	dateTime = timestamp;
	errNr=0;
	EEPROMWrite(TIMED_ERROR_LOG_ADDRESS,*this);
}

inline uint32_t TimedErrorLog::secOfYear(uint8_t yy, uint8_t mo, uint8_t dd, uint8_t hh, uint8_t mi,uint8_t *pmonlen) {
	*(pmonlen+1) = yy % 4 == 0 ? 29 : 28;
	uint16_t days = dd;
	while (mo > 1) 
		days += *(pmonlen+ --mo -1);
	return 60L*60*24*(days-1)+ 60L*60*hh + 60L*mi;
}


	
bool TimedErrorLog::show(showmode show) {
	uint8_t monlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
	uint8_t dd[6];  //! {5 .. 0} ~ {yy,mm,dd,hh,nn,ss} (miNuts=nn)
					//! dd for decimal digits - a number in {0 ... 99} in a uint8_t
					//! enum twoDecimalDigits {SS=0,NN,HH,DD,MM,YY};
	
	dd[SS] = 0;
	uint32_t ddSplitted=dateTime;		//! dateTime: decimal packed yymmddhhnn used in construction. 
	
	for (uint8_t i=1; i<6; i++) {
		dd[i] = ddSplitted % 100;
		ddSplitted /= 100;
	}
	bool validDateTime = dd[YY] < 50 && dd[MM] > 0 && dd[MM] < 13 && dd[DD] > 0 && dd[DD] <= monlen[dd[MM]] 
						 && dd[HH] < 24 && dd[NN] < 60;		

	if (show != SETTEDTIME && validDateTime) {
		uint32_t soy = secOfYear(dd[YY],dd[MM],dd[DD],dd[HH],dd[NN],monlen) + (show == NOW	? millis()/1000 : secAtError) - secSReset;
		uint32_t secOfSettedYear = 24L*60*60*(dd[YY] % 4 == 0 ? 366 : 365); //! setted on constructon - leap year awareness
		if ( soy > secOfSettedYear) {
			dd[YY]++;
			soy -= secOfSettedYear;
			monlen[1] = dd[YY] % 4 == 0 ? 29 : 28;	//! no thread safeness of saving in static monlen.
		}
		uint8_t modulus[] = {60,60,24};
		for (uint8_t i=0; i<3; i++) {
			dd[i] = soy % modulus[i];
			soy /= modulus[i];
		}
		uint16_t restDays = soy+1; //! Now days
		
		dd[MM] = 0; //! index januar
		while (monlen[dd[MM]] < restDays ) {
			restDays -= monlen[dd[MM]];
			dd[MM]++;
		}
		dd[MM]++; //! back to number from index
		dd[DD] = restDays;
		if (show == ERROR & errNr)
			sendf(F("Error: %d at "),errNr);
	}
	if (!validDateTime)
		sendf(F("Invalid date/time "));
	sendf(F("%02d-%02d-%02d %02d:%02d:%02d\n"),dd[YY],dd[MM],dd[DD],dd[HH],dd[NN],dd[SS]);
	return validDateTime;
}

void TimedErrorLog::setError(int errorNr) {
	if (errNr == 0) {
		errNr = errorNr;
		secAtError = millis()/1000-secSReset;
		EEPROMWrite(TIMED_ERROR_LOG_ADDRESS,*this);
	}
}

int8_t TimedErrorLog::getError() {
	return errNr;
}
