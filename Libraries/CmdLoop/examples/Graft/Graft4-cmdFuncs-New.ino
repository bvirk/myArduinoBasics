
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
			slices::onTime=200;
			return 0;
		}
		return -1;
	}
	
	int8_t r8(int argc, char* argv[]) {
		if (argc >=2) {
			uint16_t address=strtol(argv[1],0,16);
			uint8_t b = eeprom_read_byte(address);//   EEPROMValue<uint8_t>(address);
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
		
	void eepromDump(uint16_t start, uint16_t length) {
		sendf(F("Address    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n"));
		char ascii[0x11];
		ascii[0x10]='\0';
		for (uint16_t lineStart = start & 0x3f0; (lineStart < 0x400) && (lineStart < start+length); lineStart += 0x10) {
			//printHex(lineStart,8,": ");
			sendf(F("%.8x: "),lineStart);
			for (int8_t col=0; col < 0x10; col++) { 
					uint8_t dumpCh = EEPROM.read(lineStart+col);
					sendf(F("%.2x "),dumpCh);
					ascii[col] = dumpCh < 0x20 ? '.' : dumpCh;
				}
			sendf(F(" |%s|\n"),ascii);
		}
	}
	
	int8_t EEDump(int argc, char* argv[]) {
		uint16_t start = 0;
		uint16_t len = 0x400;
		if (argc > 1)
			start = strtol(argv[1],0,16);
		if (argc > 2)
			len = strtol(argv[2],0,16);
		eepromDump(start,len);
		return 0;
	}

	
	template<typename T>void showSize(const char* niceName) {
	sendf(F("%.10s\t%d\n"),niceName,sizeof(T));
	}

	/**
	 * quick test after reset without typing in terminal 
	 */
	int8_t showSizes(int argc, char* argv[]) {
		showSize<int>("int");
		showSize<short>("short");
		showSize<char>("char");
		showSize<long>("long");
		showSize<float>("float");
		showSize<double>("double");
		showSize<int*>("int*");
		showSize<CmdLoop>("CmdLoop");

		return 0;
	}
	/**
	 * quick test after reset without typing in terminal 
	 */
	int8_t autoexec(int argc, char* argv[]) {
		TimedErrorLog ts;
		slices::onTime = ts.getError() ? 100 : 2000;
		return 0;
	}
	
	int8_t  list(int argc, char *argv[]);
	
	CommandFunc commands[] = { //! Array of names to functions
		  {ver		,"ver"
		  	  
		  	  		//! demo of printing arguments
		},{printArgs,"printargs" //! [arg [...]] 
			
					//! set blink on pin13 in milleseconds
		},{blink	,"blink" //! ontime offtime
		
					//! list all comands	
		},{list		,"list"
		
//					//! shows sizeof of various types
//		},{typeSize	,"typeSize"
		
					//! reads 8 bit unit from EEPROM - address in hex
		},{r8		,"r8" //! address
		
					//! writes 8 bit unit to EEPROM - address and value in hex
		},{w8		,"w8" //! address value
		
					//! reads 16 bit unit from EEPROM - address in hex	
		},{r16		,"r16" //! address
		
					//! writes 16 bit unit to EEPROM - address and value in hex
		},{w16		,"w16" //! address value
		
					//! heximal dump of, if no arguments given, entire, EEPROM. address and length in hex 
		},{EEDump	,"eedump" //! [address [length]]
		
					//! puts a 32 bit timestamp in EEPROM. The timestamp is an integer which digits is yymmddhhnn
					//! eg. 2005121330 for time of day 13:30 on maj the 12' year 2020. 
		},{setTime	,"settime" //! timestamp
		
					//! shows timestamp in EEPROM. The showing, when optional argument now is used, is, 
					//! for obvious reasons, not true after a reset.	
		},{showTime	,"showtime" //! [now]

					//! sets an error value
		},{setError,"seterror" //! value		
//		},{,""		
					//! auto executed on startup
		},{autoexec,"autoexec" 		
	}};
  
  int8_t  list(int argc, char *argv[]) {
  	  sendf(F("Available commands:\n\n"));
  	  for (int i=0; i < sizeof(commands)/sizeof(commands[0]); i++)
  	  	  sendf(F("\t%s\n"),commands[i].name);
  	  return 0;
  }
};
