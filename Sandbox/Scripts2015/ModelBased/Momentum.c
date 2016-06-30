function run()
{
	BarPeriod = 60;
	
  vars Price = series(price());
  vars Trend = series(LowPass(Price,500));
	
  vars MMI_Raw = series(MMI(Price,300));
  vars MMI_Smooth = series(LowPass(MMI_Raw,500));
	
  if(falling(MMI_Smooth)) {
    if(valley(Trend))
      reverseLong(1);
    else if(peak(Trend))
      reverseShort(1);
  }

	asset("EUR/USD");
	PlotWidth = 800;
	PlotHeight1 = 320;
}