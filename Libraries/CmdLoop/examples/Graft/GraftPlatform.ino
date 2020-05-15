
CmdLoop cmdLoop( 
	 cmdFuncs::commands,sizeof(cmdFuncs::commands)/sizeof(cmdFuncs::commands[0])
	,slices::slicefuncs,sizeof(slices::slicefuncs)/sizeof(slices::slicefuncs[0])
	);

void setup() {
	Serial.begin(115200);
	pinMode(13,OUTPUT);
	sendf(F("command loop v0.2\nUse list to see all commands\n"));
	cmdLoop.loop();
}

void loop() { }