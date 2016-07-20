// by @iamajeya
// A simple Stoch Trader Test

function run()
{

        set(PARAMETERS);
        	BarPeriod	= 15;
			//Detrend = 8; // for checking if it also works with the inverse curve
        LookBack = 1000;
        StartDate = 2014;
        NumWFOCycles = 10;

        vars Price = series(price(0));
        vars Close = series(priceClose(0));

        Stop = optimize(4,2,10) * ATR(100);
        //Trail = optimize(1,0.2,3,0.2) * ATR(100);
        
			// Data, TimePeriod, CutoffLow, Cutoffhigh
        vars m = series(StochEhlers(Close,optimize(20,15,25,5),optimize(40,30,50,5),optimize(10,5,15,5)));

        vars MMI_Raw = series(MMI(Price,optimize(300,100,1000,100,-1)));
        vars MMI_Smooth = series(LowPass(MMI_Raw,optimize(500,100,1000,100,-1)));

        if(falling(MMI_Smooth)) {
                if(crossOver(m,0.2))
                        enterLong();
                else if(crossUnder(m,0.8)))
                        enterShort();
        }

}
