// Workshop 5: Counter trend trading ///////////////////

function run()
{
	StartDate = 2010;
	EndDate = 2015; // fixed simulation period 2010-2015

	BarPeriod = 240;	// 4 hour bars
	
// calculate the buy/sell signal
	vars Price = series(price());
	vars Filtered = series(BandPass(Price,30,0.5));
	vars Signal = series(FisherN(Filtered,500));
	var Threshold = 1.0;

// buy and sell
	Stop = 4*ATR(100);
	Trail = 4*ATR(100);

	if(crossUnder(Signal,-Threshold))
		enterLong(); 
	else if(crossOver(Signal,Threshold))
		enterShort();

// plot signals and thresholds
	plot("Filtered",Filtered,NEW,BLUE);
	plot("Signal",Signal,NEW,RED);
	plot("Threshold1",1,0,BLACK);
	plot("Threshold2",-1,0,BLACK);
	PlotWidth = 600;
	PlotHeight1 = 300;
} 