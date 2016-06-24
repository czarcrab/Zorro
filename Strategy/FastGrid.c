// helper function to check if the grid line has no trade
bool isFree(var Price,var Grid,bool IsShort)
{
  for(open_trades) {
    if(TradeIsShort == IsShort
      && between(TradeEntryLimit,Price-Grid/2,Price+Grid/2))
        return false;
  }
  return true;
}

// EUR/CHF grid trader main function
int run() 
{
  BarPeriod = 60;
  Hedge = 5; // activate virtual hedging

  var Grid = 20*PIP; // set grid distance to 20 pips
  var Close = priceClose();
 
// place pending trades at 5 grid lines above and below the Close
  int i;
  for(i = Close/Grid - 4; i < Close/Grid + 4; i++)
  {
    var Price = i*Grid;
// place short trades with profit target below the current price
    if(Price < Close && isFree(Price,Grid,true))
      enterShort(10,Price,0,Grid); 
// place long trades with profit target above the current price
    else if(Price > Close && isFree(Price,Grid,false))
      enterLong(10,Price,0,Grid);
  }
}