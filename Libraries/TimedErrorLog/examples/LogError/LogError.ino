#include "TimedErrorLog.h"
#include "Sendf.h"


void setup() {
	Serial.begin(115200);
	TimedErrorLog tl(2005132157L);
	tl.show(TimedErrorLog::SETTEDTIME);
	delay(3000);
	tl.show(TimedErrorLog::NOW);
	tl.setError(34);
	tl.show(TimedErrorLog::ERROR);
	delay(3000);
	//Only one error - a new constructon must occur before setting a new error
	tl.setError(7);
	tl.show(TimedErrorLog::ERROR);
	
}
	
void loop() { }
