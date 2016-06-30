function run()
{
	set(TICKS|FAST);
	BarPeriod = 60;
	NumYears = 10;
	asset("EUR/USD");
	
// get the RSI series
	vars Close = series(priceClose());
	vars Rsi12 = series(RSI(Close,12));
 
// set up stop / profit levels
	Stop = 200*PIP;
	TakeProfit = 200*PIP;
 
// if rsi crosses over buy level, exit short and enter long
	if(crossOver(Rsi12,75))
		reverseLong(1);
// if rsi crosses below sell level, exit long and enter short
	if(crossUnder(Rsi12,25))
		reverseShort(1);
}