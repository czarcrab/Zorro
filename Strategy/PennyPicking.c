// Penny Picking strategy ///////////////////
#include <profile.c>

	
int TrailWhenProfitable()
{

	var AverageOpen = 0;
	int Count = 0;
	
	
	
 	if(NumOpenLong > 0 )
	{
		var AverageOpen = 0;
		int Count = 0;
		for(current_trades)
		  if(TradeIsOpen) 
		  {
		    AverageOpen += TradePriceOpen;
		    Count++;
		  }
		  
		if(Count) 
		  AverageOpen /= Count;
	
		if (priceClose() > AverageOpen + (2 * ATR(100)) && TradeStopLimit <= 0)
			{
				TradeStopLimit = priceClose() - 2 * ATR(100);
				TradeTrailLimit =  priceClose() - ATR(100);
				printf("  TradeStopLimit = %.3f,  TradeTrailLimit = %.3f", (var) TradeStopLimit, (var) TradeTrailLimit);
				printf("  ATR = %.3f,  priceClose = %.3f", ATR(100), priceClose());
				printf("  AverageOpen = %.3f, ltod = %f", AverageOpen, (var) ltod(ET));
				
			}
			
		if (TradeStopLimit > 0 && ltod(ET) > 1230)
		{
			exitLong();
			printf("  ltod = %f", (var) ltod(ET));
		}
	}
  
   	
   	
   return 0;
   		
}

function run()
{
	StartDate = 2009;
	EndDate = 2016; 	
	LookBack = 500;
	set(LOGFILE); // log all trades
	set(TICKS);  // normally needed for TMF
	
	Trail = 0;
	Stop = 0;
	
	while(asset(loop("UK100","GER30","NAS100")))
	{
	
		vars Price = series(price());
		vars Trend = series(LowPass(Price,500));
		
	
	  	
		if(valley(Trend) && NumOpenLong < 4) 
		{
			var AverageOpen = 0;
			var AverageProfit = 0;
			int Count = 0;
			
			for(current_trades)
		  		if(TradeIsOpen) 
		  		{
	    			AverageOpen += TradePriceOpen;
	    			Count++;
	  			}
	  			
			if(Count) 
	  			AverageOpen /= Count;
	  			
	  		if(AverageOpen > 0)
	  			AverageProfit = (priceClose() - AverageOpen)/AverageOpen;
	  		
	  			
	  		switch (Count)
			{
			  case 0:
			    enterLong(TrailWhenProfitable);
			    break;
			  case 1:
			    if (AverageProfit < -0.10)
			    {
			    	enterLong(TrailWhenProfitable);
			    	printf(" enter 2nd trade ");
			    	printf(" AverageOpen %.3f ", AverageOpen);
		    	 }
			    break;
			  case 2: 
			    if (AverageProfit < -0.15)
			    {
			    	enterLong(TrailWhenProfitable);
			    	printf(" enter 3rd trade ");
		    	 }
			    break;	  
			  case 3: 
			    if (AverageProfit < -0.20)
			    {
			    	enterLong(TrailWhenProfitable);
			    	printf(" enter 4th trade ");
		    	 }
			    break;
			  default:
			    printf("None of them! ");
			}	// switch count
  			
		
		}  // if trending
	
	}  // while asset loop
  
}  // run