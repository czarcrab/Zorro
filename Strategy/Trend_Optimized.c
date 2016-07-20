function run()
{
	set(PARAMETERS);  // generate and use optimized parameters
	LookBack = 100*10;
  vars Price = series(price());
  vars Trend = series(LowPass(Price,optimize(500,100,1000,100,-1)));
  vars Signals = series(0);
	NumWFOCycles = 10;

  Stop = 4*ATR(100);

  vars MMI_Raw = series(MMI(Price,optimize(300,100,1000,100,-1)));
  vars MMI_Smooth = series(LowPass(MMI_Raw,optimize(500,100,1000,100,-1)));

  if(falling(MMI_Smooth)) {
    if(valley(Trend))
      enterLong();
    else if(peak(Trend))
      enterShort();
  }
}
