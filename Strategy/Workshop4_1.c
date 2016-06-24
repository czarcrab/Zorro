// Workshop 4: Trend Trading ///////////////////
#include <profile.c>

function run()
{
	vars Price = series(price());
	vars Trend = series(LowPass(Price,500));
	
	Stop = 4*ATR(100);

	if(valley(Trend))
		enterLong();
	else if(peak(Trend))
		enterShort();

// zoom in a certain date
//	PlotDate = 20110103;
//	PlotBars = 300;
//	set(PLOTNOW);

	StartDate = 2010;
	EndDate = 2015; // fixed simulation period 2010-2015
	
	PlotWidth = 700;
	PlotHeight1 = 300;
//	plotTradeProfile(-50); // plot the trade profit distribution
	set(LOGFILE); // log all trades
}