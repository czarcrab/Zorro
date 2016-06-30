var session1TZ = WET;
var session1Start = 8;
var session1End = 16;
var session2TZ = ET;
var session2Start = 11; // = 16 WET
var session2End = 17;

function tradeIS()
{
	if(dow() >= 1 && dow() <= 5) {
		if(NumOpenShort == 0 && lhour(session1TZ) == session1Start)
			enterShort();
		if(NumOpenShort > 0 && lhour(session1TZ) >= session1End)
			exitShort();
		if(NumOpenLong == 0 && lhour(session2TZ) == session2Start)
			enterLong();
		if(NumOpenLong > 0 && lhour(session2TZ) >= session2End)
			exitLong();
	}
}

function run()
{
	StartDate = 2012;
	UnstablePeriod = 0;
	LookBack = 0;
	BarPeriod = 1;
	while(asset(loop("EUR/USD")))
		tradeIS();
	set(LOGFILE);
}
