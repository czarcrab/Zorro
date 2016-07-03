function tradeOneNightStand() {

        vars Price = series(price());
        vars SMA10 = series(SMA(Price, 10));
        vars SMA40 = series(SMA(Price, 40));

        //Stop = 3 * 90 * PIP;

        var BuyStop,SellStop;

        BuyStop = HH(10) + 1*PIP;
        SellStop = LL(10) - 1*PIP;

        if (dow() == 5 && NumOpenLong == 0 && NumPendingLong == 0 && SMA10[0] > SMA40[0])
                enterLong(0,BuyStop);
        else if (dow() == 5 && NumOpenShort == 0 && NumPendingShort == 0 && SMA10[0] < SMA40[0])
                enterShort(0,SellStop);

        if (dow() != 5 && dow() != 6 && dow() != 7) {
                exitLong();
                exitShort();
        }

}


function run() {

        BarPeriod = 1440;

        while(asset(loop("USD/CHF", "USD/JPY", "GBP/USD", "EUR/USD")))
                tradeOneNightStand();

}
