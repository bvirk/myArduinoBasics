
namespace cmdFuncs {

	int8_t showTime(int argc, char* argv[]) {
		switch(	argc > 1 ? argv[1][0] & 0x5f : 'S' ) {
			case 'N':
				TimedErrorLog::show(TimedErrorLog::NOW);
				break;
			case 'E':
				TimedErrorLog::show(TimedErrorLog::ERROR);
				break;
			case 'S':
			default:
				TimedErrorLog::show(TimedErrorLog::SETTEDTIME);
		} 
		return 0;
	}

	int8_t setTime(int argc, char* argv[]) {
		if ( argc >=2 ) {
			TimedErrorLog::setTime(strtol(argv[1],0,10));
			TimedErrorLog::show(TimedErrorLog::NOW);
			return 0;
		}
		return -1;
	}
	
	int8_t setError(int argc, char* argv[]) {
		if (argc > 1 ) { 
			error = atoi(argv[1]);
			TimedErrorLog::show(TimedErrorLog::ERROR);
			return 0;
		}
		return -1;
	}
	

	int8_t autoexec(int argc, char* argv[]) {
		if (error)
			TimedErrorLog::show(TimedErrorLog::ERROR);
		else {
			TimedErrorLog::show(TimedErrorLog::SETTEDTIME);
		}
		sendf(F("Set time using:\n    settime yymmddhhnn\n"));
		sendf(F("Use list to see all commands\n"));
		return 0;
	}
	
	int8_t temp(int argc, char* argv[]) {
		
    	sendff(F("air temp:   %f dgr.\n"),slices::airTemperature);
    	sendff(F("earth temp: %f dgr.\n"),slices::earthTemperature);
    	sendff(F("\nSwitching temperatures:\n\nAir fan:\t\t%.1f\nHeat element: \t%.1f\n"),fanSwitchTemp,heatSwitchTemp);  
		return 0;
	}

	int8_t ds18b20(int argc, char* argv[]) {
		
    	for (int i=0; i < DS1822_DEVICE_COUNT; i++)
    		// would be lie to claim I don't experimentet with that format specifier! - llx=bogus
    		sendf("device %d: has address: %lx%lx\n",i,*((uint32_t *)devAddr[i]+1),*(uint32_t *)devAddr[i]);
    	return 0;
	}

	int8_t fanSwitch(int argc, char *argv[]) {
	  if (argc > 1) {
	  	  fanSwitchTemp = atof(argv[1]);
	  	  temp(argc,argv);
	  	  return 0;
	  }
	  return -1;  
  	}
  
  	int8_t heatSwitch(int argc, char *argv[]) {
	  if (argc > 1) {
	  	  heatSwitchTemp = atof(argv[1]);
	  	  temp(argc,argv);
	  	  return 0;
	  }
	  return -1;  
  	}

};

//! EDIT THIS WHEN INSERTING/REMOVING COMMANDS - ONE MORE THEN LAST INDEX OF PUTF
#define NUM_COMMANDS 9

CommandFunc CommandFuncBox::commands[NUM_COMMANDS];

namespace cmdFuncs {
	
	int8_t  list(int argc, char *argv[]) {
  	  sendf(F("Available commands:\n\n"));
  	  for (int i=0; i < NUM_COMMANDS; i++) {
  	  	  if (utils::strcmp_PP(CommandFuncBox::commands[i].name,CmdLoop::autoExec)) {
  	  	  	sendf(FP(CommandFuncBox::commands[i].name));
  	  	  	sendf("\n");
  	  	  }
  	  }
  	  return 0;
  	}
};

CommandFuncBox::CommandFuncBox() : size(NUM_COMMANDS) {	

#define PUTF(num) ;commands[num].init(cmdFuncs:: 

	
	   PUTF(0) setTime			,F("settime" // timestamp
		
							//! shows timestamp in EEPROM. The showing, when optional argument now is used, is, 
							//! for obvious reasons, not true after a reset.	
	)) PUTF(1) showTime		,F("showtime" // [now]
		
							//! shows all commands
	)) PUTF(2) list			,F("list" // value		

							//! sets an error value in range {-128 ... 127}
	)) PUTF(3) setError		,F("seterror" // value
		
							//! shows connected dallas ds18b20 devices
	)) PUTF(4) ds18b20		,F("ds18b20"  		

							//! set fan switching temperature
	)) PUTF(5) fanSwitch	,F("fan" // switching-temperature  		

							//! set heat switching temperature
	)) PUTF(6) heatSwitch	,F("heat" // switching-temperature 		

							//! Report earth and air temperature and switching temperatures for heat element and cooling fan 
	)) PUTF(7) temp			,F("temp"  		

	// KEEPS AUTOEXEC AS LAST    
							//! auto executed on startup.
	)) PUTF(8) autoexec		,F("autoexec" 		
	));
}



CmdLoop cmdLoop( 
	 CommandFuncBox::instance()
	,slices::slicefuncs,sizeof(slices::slicefuncs)/sizeof(slices::slicefuncs[0])
	);

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN,OUTPUT);
	pinMode(FAN_CONTROL_PIN, OUTPUT);
	pinMode(HEAT_CONTROL_PIN, OUTPUT);
	sensors.begin();
	for (uint8_t i=0; i < DS1822_DEVICE_COUNT; i++)
	if (!sensors.getAddress(devAddr[i], i)) {
	  sendf(F("Unable to find address for Device %d\n"),i);
	  error = ERROR_DALLASTEMPERATURE_GETADDRESS;
	}
	else 
	  sensors.setResolution(devAddr[i], TEMPERATURE_PRECISION);
	heatSwitchTemp=10.0;
	fanSwitchTemp=29.5;
  
	cmdLoop.loop(F("autoexec"));
}

void loop() { }