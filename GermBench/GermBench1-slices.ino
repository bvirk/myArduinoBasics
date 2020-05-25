namespace slices {
	uint16_t onTime=2000;         //!< steady blinking on startup
	uint16_t offTime=2000;
	
	//! initial values to ensure no action when temperature measurement fails
	float airTemperature=0;
	float earthTemperature=200;

	
	//! time error depend on blink
	/*!
	  Error signaling by LED_BUILTIN on Time being 100
	  1. static for remembering values - 5 for 3 light on periods and 2 dark periods. =5 is compile time for static
	  2. bit 0 is used as LED_BUILTIN value
	  3. condition for error signaling is ==100 - after last light on cntDown is 0 and statement // 7. is chosen
	  4. switching light/dark of LED_BUILTIN on next onBlinks run and count down to 'pass the baton on' to offBlinks
	  5. necessary on first run after offBlinks(...), but is costs more to test than just setting each time.
	  6. Make ready for next 3 short light pulses on LED_BUILTIN after 2 seconds dark made by  offBlinks(...)
	  7. cheapest way to ensure long light beam when no error has occurred
	  8. 'pass the baton on' to offBlinks
	*/  
	void onBlinks(CmdLoop & cmdLoop) {
		static uint8_t cntDown=5;        		// 1.
		digitalWrite(LED_BUILTIN,1 & cntDown);	// 2.
		if (onTime==100 && cntDown ) {   		// 3.
			cntDown--;                   		// 4.
			cmdLoop.setDelay(onTime);    		// 5.
		} else {                         		
			cntDown = 5;                 		// 6.   
			cmdLoop.setDelay(onTime);    		// 7.
			cmdLoop.next();              		// 8.  
		}
	}
	
	void offBlinks(CmdLoop & cmdLoop) {
		digitalWrite(LED_BUILTIN,0);
		sensors.requestTemperatures();
		int8_t i = address64Index(AIR_SERIAL);
    	if ( i >= 0) 
    		airTemperature = sensors.getTempC(devAddr[i]);
    	i = address64Index(EARTH_SERIAL);
    	if ( i >= 0)
    		earthTemperature = sensors.getTempC(devAddr[i]);
		 
    	if (airTemperature > fanSwitchTemp) // 0.5 degree above 
    		digitalWrite(FAN_CONTROL_PIN, FAN_ON);
      
    	if (airTemperature <  fanSwitchTemp) // 0.5 degree belove
    		digitalWrite(FAN_CONTROL_PIN, FAN_OFF);
    
    	if (earthTemperature < heatSwitchTemp) 
    		digitalWrite(HEAT_CONTROL_PIN, HEAT_ON);
    	
    	if (earthTemperature >  heatSwitchTemp)
    		digitalWrite(HEAT_CONTROL_PIN, HEAT_OFF);
    	
    	cmdLoop.setDelay(offTime);
		cmdLoop.next();
	}

	void (*slicefuncs[])(CmdLoop &) = {onBlinks,offBlinks};

};
