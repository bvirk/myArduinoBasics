#include "TimedErrorLog.h"
#include "Sendf.h"


void setup() {
	Serial.begin(115200);
	sendf("initial values of error\n");
	sendf("settedtime\n");
	TimedErrorLog::show(TimedErrorLog::SETTEDTIME);
	sendf("settedtime\n");
	TimedErrorLog::show(TimedErrorLog::SETTEDTIME);
	sendf("now\n");
	TimedErrorLog::show(TimedErrorLog::NOW);
	sendf("error from last reset\n");
	TimedErrorLog::show(TimedErrorLog::ERROR);
	sendf("now setting time to 2003030820L\n");
	TimedErrorLog::setTime(2003030820L);
	TimedErrorLog::show(TimedErrorLog::SETTEDTIME);
	delay(3000);
	TimedErrorLog::show(TimedErrorLog::NOW);
	TimedErrorLog::setError(34);
	#define error TimedErrorLog::getError()
	if (error)
		sendf("error is now %d\n",error);
	TimedErrorLog::show(TimedErrorLog::ERROR);
	delay(3000);
	TimedErrorLog::show(TimedErrorLog::ERROR);
	//Only one error - a new constructon must occur before setting a new error
	TimedErrorLog::setError(7);
	TimedErrorLog::show(TimedErrorLog::ERROR);
	TimedErrorLog::show(TimedErrorLog::NOW);
	
}
	
void loop() { }
