// Workshop 8: Scam Robot /////////////////////

function run()
{
	seed(1234);
	BarPeriod = 1440;
	StartDate = 2015;
	NumYears = 1;
	LookBack = 0;
	Verbose = 7;
	asset("EUR/USD");

	TakeProfit = 10*PIP;
	Stop = 200*PIP;

	if(NumOpenTotal == 0) {
		if(random() > 0)
			enterLong();
		else 
			enterShort();
	}
	
	set(PLOTNOW|LOGFILE);
	ColorUp = ColorDn = ColorWin = ColorLoss = ColorDD = 0;
	PlotWidth = 800;
	PlotHeight1 = 320;
}