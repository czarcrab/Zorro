// Mean Reversion Test /////////////////////////////////

function run()
{
	BarPeriod = 240;	// 4 hour bars	
	vars Price = series(price());
	vars Filtered = series(HighPass(Price,30));
	vars Signal = series(FisherN(Filtered,500));
	var Threshold = 1.0;

	if(Hurst(Price,500) < 0.4) {
		if(crossUnder(Signal,-Threshold))
			reverseLong(1); 
		else if(crossOver(Signal,Threshold))
			reverseShort(1);
	}

	PlotWidth = 800;
	PlotHeight1 = 300;
} 