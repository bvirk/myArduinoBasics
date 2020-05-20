
namespace cmdFuncs {

	int8_t showTime(int argc, char* argv[]) {
		TimedErrorLog ts;
		switch(	argc > 1 ? argv[1][0] & 0x5f : 'S' ) {
			case 'N':
				ts.show(TimedErrorLog::NOW);
				break;
			case 'E':
				ts.show(TimedErrorLog::ERROR);
				break;
			case 'S':
			default:
				ts.show(TimedErrorLog::SETTEDTIME);
		} 
		return 0;
	}

	int8_t setTime(int argc, char* argv[]) {
		if ( argc >=2 ) {
			TimedErrorLog ts(strtol(argv[1],0,10));
			slices::onTime=ts.show(TimedErrorLog::NOW) ? 2000 : 100;
			return 0;
		}
		return -1;
	}
	
	int8_t setError(int argc, char* argv[]) {
		if (argc > 1 ) { 
			TimedErrorLog ts;
			ts.setError(atoi(argv[1]));
			ts.show(TimedErrorLog::ERROR);
			slices::onTime=100;
			return 0;
		}
		return -1;
	}
	
	int8_t r8(int argc, char* argv[]) {
		if (argc >=2) {
			uint16_t address=strtol(argv[1],0,16);
			uint8_t b = eeprom_read_byte(address);
			sendf("*%03x=%02x\n",address,b);
			return 0;
		} 
		return -1;
	}

	int8_t r16(int argc, char* argv[]) {
		if (argc >=2) {
			uint16_t address=strtol(argv[1],0,16);
			uint16_t w = EEPROMValue<uint16_t>(address);
			sendf("*%03x=%04x\n",address,w);
			return 0;
		} 
		return -1;
	}
	
	int8_t w8(int argc, char* argv[]) {
		if (argc >=3 ) {
			uint16_t address=strtol(argv[1],0,16);
			uint8_t value = strtol(argv[2],0,16);
			EEPROMWrite(address,value);
			r8(argc,argv);
			return 0;
		} 
		return -1;
	}

	int8_t w16(int argc, char* argv[]) {
		if (argc >=3 ) {
			uint16_t address=strtol(argv[1],0,16);
			uint16_t value = strtol(argv[2],0,16);
			EEPROMWrite(address,value);
			r16(argc,argv);
			return 0;
		} 
		return -1;
	}
		
	int8_t EEDump(int argc, char* argv[]) {
		uint16_t start = 0;
		uint16_t len = 0x400;
		if (argc > 1)
			start = strtol(argv[1],0,16);
		if (argc > 2)
			len = strtol(argv[2],0,16);
		Utils::eepromDump(start,len);
		return 0;
	}

	int8_t autoexec(int argc, char* argv[]) {
		TimedErrorLog ts;
		slices::onTime = ts.getError() ? 100 : 2000;
		return 0;
	}
	
	int8_t schnellStart(int argc, char* argv[]) {
		sendf("Schnell start\n");	
		
		return 0;
	}
};


#define NUM_COMMANDS 14

CommandFunc CommandFuncBox::commands[NUM_COMMANDS];

namespace cmdFuncs {
	
	int8_t  list(int argc, char *argv[]) {
  	  sendf(F("Available commands:\n\n"));
  	  for (int i=0; i < NUM_COMMANDS; i++) {
  	  	  if (Utils::strcmp_PP(CommandFuncBox::commands[i].name,CmdLoop::autoExec)) {
  	  	  	sendf(FP(CommandFuncBox::commands[i].name));
  	  	  	sendf("\n");
  	  	  }
  	  }
  	  return 0;
  	}
};

CommandFuncBox::CommandFuncBox() : size(NUM_COMMANDS) {	

#define PUTF ;commands[i++].init(cmdFuncs:: 

	int i=0;
	
	PUTF ver				,F("ver"
		  
							//! demo of printing arguments
	)) PUTF printArgs,		F("printargs" // [arg [...]]
	
							//! set blink on pin13 in milleseconds
	)) PUTF blink			,F("blink" // ontime offtime
	
							//! reads 8 bit unit from EEPROM - address in hex
	)) PUTF r8				,F("r8" // address

							//! writes 8 bit unit to EEPROM - address and value in hex
	)) PUTF w8				,F("w8" // address value

							//! reads 16 bit unit from EEPROM - address in hex	
	)) PUTF r16				,F("r16" // address
		
							//! writes 16 bit unit to EEPROM - address and value in hex
	)) PUTF w16				,F("w16" // address value
		
							//! heximal dump of, if no arguments given, entire, EEPROM. address and length in hex 
	)) PUTF EEDump			,F("eedump" // [address [length]]
		
							//! puts a 32 bit timestamp in EEPROM. The timestamp is an integer which digits is yymmddhhnn
							//! eg. 2005121330 for time of day 13:30 on maj the 12' year 2020. 
	)) PUTF setTime			,F("settime" // timestamp
		
							//! shows timestamp in EEPROM. The showing, when optional argument now is used, is, 
							//! for obvious reasons, not true after a reset.	
	)) PUTF showTime		,F("showtime" // [now]
		
							//! shows all commands
	)) PUTF list			,F("list" // value		

							//! sets an error value in range {-128 ... 127}
	)) PUTF setError		,F("seterror" // value
		
							//! For testing
	)) PUTF schnellStart	,F("ss"  		

							//! auto executed on startup
	)) PUTF autoexec		,F("autoexec" 		
	));
}



CmdLoop cmdLoop( 
	 CommandFuncBox::instance()
	,slices::slicefuncs,sizeof(slices::slicefuncs)/sizeof(slices::slicefuncs[0])
	);

void setup() {
	Serial.begin(115200);
	pinMode(13,OUTPUT);
	sendf(CmdLoop::version());
	sendf(F("Use list to see all commands\n"));
	cmdLoop.loop(F("autoexec"));
}

void loop() { }