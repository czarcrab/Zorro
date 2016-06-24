function run()
{
	LookBack = 0;
	StartDate = 2006; //20150101;
	EndDate = 2007;
	//NumDays = 60;
	set(PLOTNOW);
	GapDays = 3;
	asset("GBP/USD");
	priceClose(); // check for outliers
	
	PlotWidth = 900;
	PlotHeight1 = 320;
}