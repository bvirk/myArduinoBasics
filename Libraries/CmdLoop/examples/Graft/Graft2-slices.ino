namespace slices {
	uint16_t onTime=2000;
	uint16_t offTime=2000;
	void onBlinks(CmdLoop & cmdLoop) {
		static uint8_t cntDown=5;
		digitalWrite(13,1 & cntDown);
		if (onTime==100 && cntDown ) {
			cntDown--;
			cmdLoop.setDelay(onTime);
		} else {
			cntDown = 5;
			cmdLoop.setDelay(onTime);
			cmdLoop.next();
		}
	}
	
	void offBlinks(CmdLoop & cmdLoop) {
		digitalWrite(13,0);
		cmdLoop.setDelay(offTime);
		cmdLoop.next();
	}

	void (*slicefuncs[])(CmdLoop &) = {onBlinks,offBlinks};

};
