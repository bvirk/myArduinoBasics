namespace cmdFuncs {
	
	/** 
	  * version of this precious mechanism 
	  */
	int8_t  ver(int argc, char* argv[]) {
		sendf(F("command loop v0.1\n"));
		return 0;
	}
	
	/**
	 * Argumens retrievement like in c++'s main on a Desktop computer.
	 */
	int8_t printArgs(int argc, char* argv[]) {
		for (uint8_t i = 0; i < argc; i++)
			sendf(F("%d: >%s<\n"),i,argv[i]);
		return 0;
	}

	int8_t blink(int argc, char* argv[]) {
		if (argc == 3 ) {
			slices::onTime = atoi(argv[1]);
			slices::offTime = atoi(argv[2]);
			return 0;
		}
		return -1;
	}

};
