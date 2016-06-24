// Update Assets.dta and/or download price history of a certain asset (or all)
// Select the account (Demo/Real) before.
// MT4 and IB do not provide price history. FXCM provides history from 2002. 
// See remarks in the manual under "Import" and "loadHistory".


#define YEAR 2015
#define MAX_GAP 3
BOOL Loading = FALSE;

int Download(string years,int period)
{
	if(years) {
		NumYears = 0;
		if(!strstr(years,"-")) // single date only
			StartDate = EndDate = atoi(years);
		else
			if(2 != sscanf(years,"%4i-%4i",&StartDate,&EndDate))
				return 0;
		if(StartDate > EndDate || StartDate > YEAR || EndDate < 2002)
			return 0;
	} else {
		StartDate = EndDate = YEAR;
		NumYears = -1;
	}
		
	string name;
	Loading = TRUE;
	if(panelGet(0,0) == "All Assets") {
		while(name = loop(Assets))
			loadHistory(name,period);
	} else {
		name = panelGet(0,1);
		loadHistory(name,period);
	}
	
	Loading = FALSE;
	return 1; // date ok	
}

void click(int row,int col)
{
	if(Loading) return; // don't click while downloading data
	sound("click.wav");
	
	string Text = panelGet(row,col);
	if(Text == "New Asset") {
		panelSet(row,col,"All Assets",0,0,0); 
		panelSet(0,1,0,ColorPanel[0],3,1);
	}
	else if(Text == "All Assets") {
		panelSet(row,col,"New Asset",0,0,0); 
		panelSet(0,1,0,ColorPanel[2],1,2);
	}
	else if(Text == "Exit")
		quit();
	else if(Text == "Load M1 Data") {
		if(!Download(panelGet(row,1),1))
			panelSet(row,1,0,ColorPanel[1],2,2);
	} else if(Text == "Load Tick Data") {
		if(!Download(panelGet(row,1),0))
			panelSet(row,1,0,ColorPanel[1],2,2);
	} else if(Text == "Save Assets to") {
		string Dest = strf("History\\%s.csv",panelGet(row,1));
		Download(0,1);
		file_copy(Dest,"Log\\Assets.csv");
	}
}


function run()
{
	if(!is(TRADEMODE)) {
		set(EXE);
		quit("Click [Trade] to download assets!");
		return;
	}

	LookBack = 0;
	StartDate = EndDate = YEAR;
	GapDays = MAX_GAP;		// detect gaps
	
	panel("Strategy\\Download.csv",GREY,100);
	panelSet(1,1,strf("%i-%i",StartDate,EndDate),0,0,0);
	panelSet(2,1,strf("%i-%i",StartDate,EndDate),0,0,0);
	panelSet(4,0,0,0,12,4);
	if(!is(SPONSORED)) {
		panelSet(2,0,0,0,3,1);
		panelSet(2,1,0,0,3,1);
	}
	while(wait(100)); // wait for panel entry
	panel(0,0,0,0);
}