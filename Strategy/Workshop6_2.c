// Workshop 6_2: Money Management ///////////////////

function tradeCounterTrend()
{
	TimeFrame = 4;
	vars Price = series(price());
	vars Filtered = series(BandPass(Price,optimize(30,20,40),0.5));
	vars Signal = series(Fisher(Filtered,500));
	var Threshold = optimize(1,0.5,1.5,0.1);
	
	Stop = optimize(4,2,10) * ATR(100);
	Trail = 4*ATR(100);
	
	if(crossUnder(Signal,-Threshold)) 
		enterLong(); 
	else if(crossOver(Signal,Threshold)) 
		enterShort();
}

function tradeTrend()
{
	TimeFrame = 1;
	vars Price = series(price());
	vars Trend = series(LowPass(Price,optimize(500,300,700)));

	Stop = optimize(4,2,10) * ATR(100);
	Trail = 0;

	vars MMI_Raw = series(MMI(Price,300));
	vars MMI_Smooth = series(LowPass(MMI_Raw,500));
	
	if(falling(MMI_Smooth)) {
		if(valley(Trend))
			enterLong();
		else if(peak(Trend))
			enterShort();
	}
}

function run()
{
	set(PARAMETERS+FACTORS);  // generate and use optimized parameters and factors
	NumCores = -2;		// use multiple cores (Zorro S only)
	BarPeriod = 60;	// 1 hour bars
	LookBack = 2000;	// needed for Fisher()
	StartDate = 2005;
	EndDate = 2015; 	// fixed simulation period
	NumWFOCycles = 10; // activate WFO
	Capital = 10000;		// reinvestment mode
	
	if(ReTrain) {
		UpdateDays = -1;	// update price data from the server 
		SelectWFO = -1;	// select the last cycle for re-optimization
		reset(FACTORS);	// don't generate factors when re-training
	}
	
// portfolio loop
	while(asset(loop("EUR/USD","USD/JPY")))
	while(algo(loop("TRND","CNTR")))
	{
// method 1: invest the square root of the component profit		
		Margin = 0.5 * OptimalF * Capital * sqrt(1 + ProfitClosed/Capital);
		
// method 2: invest 50% of OptimalF		
		//Margin = 0.5 * OptimalF * (Capital + ProfitClosed);
		
// method 3: invest 1% of the balance	
		//Margin = 0.01 * (Capital + ProfitClosed);	

		if(Algo == "TRND") 
			tradeTrend();
		else if(Algo == "CNTR") 
			tradeCounterTrend();
	}
	
	PlotWidth = 600;
	PlotHeight1 = 300;
	ColorUp = ColorDn = ColorWin = ColorLoss = 0; // don't plot candles and trades
	set(TESTNOW+LOGFILE);
}