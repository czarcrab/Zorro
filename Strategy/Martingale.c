// Perfect martingale system ///////////////////

function run()
{
	BarPeriod = 1440;
	Stop = TakeProfit = ATR(100);
	Lots = pow(2,LossStreakTotal); 
	
// wait until last stop/profit target was hit
	if(NumOpenTotal == 0) {
		if(random() < 0)
			enterShort();
		else 
			enterLong();
	}
	
	set(PLOTNOW);
	PlotWidth = 800;
	PlotHeight1 = 320;
}