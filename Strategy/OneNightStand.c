function run()
{
//	BarPeriod = 60; // Hourly Bars
        Verbose = 14;
// Detrend = 1;
        vars Price = series(price());
        vars SMA10 = series(SMA(Price, 10));
        vars SMA40 = series(SMA(Price, 40));

        Stop = 90 * PIP;
        Capital = 100000;
        Margin = 0.01* Capital * sqrt(1 + max(0,WinTotal-LossTotal)/Capital);
//	Risk = 0.01 * Capital * sqrt(1 + max(0,WinTotal-LossTotal)/Capital);
//
        var BuyLimit,SellLimit,BuyStop,SellStop;

        if(NumOpenLong < 5 & dow() == 5 & SMA10[0] > SMA40[0]) {
                BuyStop = HH(10) + 1*PIP;
                enterLong(0, BuyStop);
        }

        else if(NumOpenShort < 5 & dow() == 5 & SMA10[0] < SMA40[0])
        {
                SellStop = LL(10) - 1*PIP;
                enterShort(0, SellStop);
        }


        if(TradeIsOpen and dow() == 1)
                exitLong();
        if(TradeIsOpen and dow() == 1)
                exitShort();

        plot("SMA10", SMA10[0], LINE, BLUE);
        plot("SMA40", SMA40[0], LINE, ORANGE);
}
