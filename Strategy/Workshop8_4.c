// Workshop 8: Scam Robot /////////////////////

function strategy3()
{
	Stop = 20*PIP;
	//TakeProfit = 5*PIP;
	Trail=1;
	TrailSlope=120;
	TrailLock=30;
	var ProfitGoal = 1*PIPCost*Bar;
	Lots = clamp((ProfitGoal-ProfitClosed)/(7*PIPCost),1,200); 
	
	//if(ProfitOpen+ProfitClosed < -250) { // margin call
	//	exitLong();
	//	exitShort();
	//	return;
	//}
	
	if(NumOpenTotal == 0) {
		if(random() < 0)
			enterShort();
		else 
			enterLong();
	}
}

// generate a profit distribution chart
function run()
{
	BarPeriod = 5; //1440
	StartDate = 2015;
	NumYears = 1;
	LookBack = 0;
	asset("EUR/USD");

// run this simulation 3000 times	
	NumTotalCycles = 3000;
	strategy3();

// plot the result of every run in a bar graph
	if(is(EXITRUN)) {
		int Step = 2000;
		int Result = floor(ProfitClosed/PIPCost/Step);
		if(Step*Result >= -100000) // clip the chart at the left
			plotBar("Profit",Result,Step*Result,1,SUM+BARS+LBL2,RED);	
	}
	
	PlotHeight1 = 320;
}