// by @iamajeya
// A simple MACD indicator going by crossOver

function run()
{

        set(PARAMETERS);

        LookBack = 1000;
        //StartDate = 2014;
        BarPeriod	= 60;
        NumWFOCycles = 10;

        vars Price = series(price(0));

        Stop = optimize(4,2,10) * ATR(100);
        Trail = optimize(1,0.2,3,0.2) * ATR(100);

        vars m = series(EMA(Price,optimize(12,3,12,1))-EMA(Price,optimize(26,12,36,1))); // Macd
        vars mSignal = series(SMA(m, optimize(9,3,10,1))); // Macd signal

        vars MMI_Raw = series(MMI(Price,optimize(300,100,1000,100,-1)));
        vars MMI_Smooth = series(LowPass(MMI_Raw,optimize(500,100,1000,100,-1)));

        if(falling(MMI_Smooth)) {
                if(crossOver(m,mSignal))
                        enterLong();
                else if(crossUnder(m,mSignal))
                        enterShort();
        }

}
