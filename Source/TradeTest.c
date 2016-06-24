// Trade Every Minute for Test Purposes ///////////////////

int AutoTrade = 0;

function click(int row,int col)
{
	if(!is(RUNNING)) return; // only clickable when session is active
	sound("click.wav");	
	string Text = panelGet(row,col);
	
	if(Text == "Auto Off") {
		panelSet(row,col,"Auto On",0,0,0); 
		AutoTrade = 1;
	}
	else if(Text == "Auto On") {
		panelSet(row,col,"Auto Off",0,0,0); 
		AutoTrade = 0;
	}
	else if(Text == "NFA Off") {
		panelSet(row,col,"NFA On",0,0,0); 
		set(NFA);
	}
	else if(Text == "NFA On") {
		panelSet(row,col,"NFA Off",0,0,0); 
		reset(NFA);
	}
	else if(Text == "Hedge 0") {
		panelSet(row,col,"Hedge 2",0,0,0); 
		Hedge = 2;
	}
	else if(Text == "Hedge 2") {
		panelSet(row,col,"Hedge 4",0,0,0); 
		Hedge = 4;
	}
	else if(Text == "Hedge 4") {
		panelSet(row,col,"Hedge 5",0,0,0); 
		Hedge = 5;
	}
	else if(Text == "Hedge 5") {
		panelSet(row,col,"Hedge 0",0,0,0); 
		Hedge = 1;
	}
	else {
		Lots = slider(1);	// get current slider position
		Stop = Trail = PIP*slider(2);
		//asset(panelGet(3,0));
		if(Text == "Buy Long")
			enterLong();
		else if(Text == "Buy Short")
			enterShort();
		else if(Text == "Close Long")
			exitLong(0,0,Lots);
		else if(Text == "Close Short")
			exitShort(0,0,Lots);	
		else if(Text == "Adjust Stop") {
			exitShort(0,priceClose()+Stop);	
			exitLong(0,priceClose()-Stop);	
		}
	}
}

function run()
{
#ifndef COMPILE
	if(is(TRAINMODE)) // compile by [Train]
#endif
	{
		set(EXE);
		return;
	}
	if(is(TESTMODE)) {
		quit("Click [Trade]!");
		return;
	} 
	
	BarPeriod = 1;
	NumYears = 1;
	LookBack = 0;
	Verbose = 15;
	set(LOGFILE);

	Lots = slider(1,1,0,20,"Lots",0);
	Stop = Trail = PIP*slider(2,0,0,50,"Stop",0);

	if(is(INITRUN)) {
		AutoTrade = 0;
		reset(NFA);
		Hedge = 0;
		panel(9,1,GREY,80);
		panelSet(0,0,"Auto Off",ColorPanel[2],1,4);
		panelSet(1,0,"NFA Off",ColorPanel[2],1,4);
		panelSet(2,0,"Hedge 0",ColorPanel[2],1,4);
		//panelSet(3,0,Asset,ColorPanel[2],1,2);
		panelSet(4,0,"Buy Long",ColorPanel[3],1,4);
		panelSet(5,0,"Buy Short",ColorPanel[3],1,4);
		panelSet(6,0,"Close Long",ColorPanel[3],1,4);
		panelSet(7,0,"Close Short",ColorPanel[3],1,4);
		panelSet(8,0,"Update Stop",ColorPanel[3],1,4);
	}
	
	if(AutoTrade) {	
		if(NumOpenTotal >= 3) {
			exitLong();
			exitShort();
		} else {
			if(price(0) > price(1)) 
				enterLong();
			else if(price(0) < price(1)) 
				enterShort();
		}
	}
#endif	
}