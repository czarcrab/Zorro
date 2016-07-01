// by @iamajeya
// A simple MACD indicator going by crossOver

function run()
{
	StartDate = 2012;
	BarPeriod	= 1;
  //LookBack = 60;

	while (asset(loop("EUR/USD"))) {
	var FastPeriod, SlowPeriod, SignalPeriod;
	// FastPeriod = slider(1,0,1,10,"Fast","Fast Period");
	//SlowPeriod = slider(2,0,10,40,"Slow","Slow Period");
	//SignalPeriod = slider(3,0,1,10,"Signal","Signal Period");
	FastPeriod = 4;
	SlowPeriod = 22;
	SignalPeriod = 3;

	vars Data = series(price());
  // Creating MACD instead of using the build in function as this provides
	// flexibility of using EMA or SMA (which I prefer) for Signal
	var *rMACD = series(EMA(Data,FastPeriod)-EMA(Data,SlowPeriod));
	var *rMACDSignal = series(EMA(&rMACD,SignalPeriod));
	var *rMACDHist = series(rMACD - rMACDSignal);

	if(crossOver(&rMACD,&rMACDSignal)) {
		//reverseShort(10);
		exitShort();
		enterLong();
	}
	if(crossUnder(&rMACD,&rMACDSignal)) {
		//reverseLong(10);
		exitLong();
		enterShort();
	}

	}
	set(LOGFILE);
}
