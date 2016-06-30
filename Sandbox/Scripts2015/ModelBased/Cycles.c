// Cycles Trading Test ///////////////////

function run()
{
	BarPeriod = 60;
	
	vars Price = series(price());
	var Phase = DominantPhase(Price,10);
	vars Signal = series(sin(Phase+PI/4));
	vars Dominant = series(BandPass(Price,rDominantPeriod,1));
	ExitTime = 10*rDominantPeriod;
	var Threshold = 1*PIP;
	
	if(Amplitude(Dominant,100) > Threshold) {
		if(valley(Signal))
			reverseLong(1); 
		else if(peak(Signal))
			reverseShort(1);
	}
	
	asset("EUR/USD");
	PlotWidth = 800;
	PlotHeight1 = 320;
}

