// brute force optimization
function run(){  
	set(PARAMETERS);
  int PeriodsEMA1[4] = { 5, 10, 15, 20 };
  int PeriodsEMA2[3] = { 100, 150, 200 };  LookBack = 250;
  int Index = optimize(1,1,4*3,1) - 1;  int PeriodEMA1 = PeriodsEMA1[Index%4];
  int PeriodEMA2 = PeriodsEMA2[Index/4];    vars Price = series(price(0));
  vars EMA1 = series(EMA(Price,PeriodEMA1));
  vars EMA2 = series(EMA(Price,PeriodEMA2));    
  if(crossOver(EMA1,EMA2))
    enterLong();  
  else if(crossUnder(EMA1,EMA2))    
   enterShort();
 }