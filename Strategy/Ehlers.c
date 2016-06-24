// Strategy from "Predictive Indicators for Effective Trading Strategies"
// by John Ehlers

//#define USE_PREDICT

function run() 
{
	BarPeriod	= 1440;
	//Detrend = 8; // for checking if it also works with the inverse curve
	asset("SPX500");
	
	vars Osc = series(StochEhlers(series(price()),20,40,10));

#ifndef USE_PREDICT	
	if(crossOver(Osc,0.8)) 
		reverseShort(1);
	if(crossUnder(Osc,0.2))
		reverseLong(1);
#else		
	if(predict(CROSSOVER,series(Osc[0]-0.8),10,0.01) > -5) 
		reverseShort(1);
	if(predict(CROSSOVER,series(0.2-Osc[0]),10,0.01) > -5) 
		reverseLong(1);
#endif

	PlotWidth = 800;
	plot("StochEhlers",Osc,NEW,RED);
	plot("Threshold1",.2,0,BLACK);
	plot("Threshold2",.8,0,BLACK);
	set(PLOTNOW);
}
