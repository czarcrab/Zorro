// Trend Trading Experiment ///////////////////
#include <default.c>

//#define WRC
//#define DO_STATISTIC

#ifdef DO_STATISTIC	
var _getvar(string filename,string name)
{
	if(!file_date(filename)) return 0;
	return strvar(file_content(filename),name,0);
}

void _putvar(string filename,string name,var value)
{
	string line = strf("%s %12.5f\n",name,value);
	string s = 0,content = 0;
	if(file_date(filename)) 
		content = file_content(filename);
	if(content)
		s = strstr(content,name);
	if(!s)
		file_append(filename,line);
	else {
		memcpy(s,line,strlen(line));
		file_write(filename,content,0);
	}
}
#endif

int Period;
var Daily[3000];
int Day = 0;

var objective() 
{ 
	if(NumWinTotal < 30 || NumLossTotal < 30) { // not enough trades
		g->bDoStep = 0;	// abort optimization
		return 0; 
	}
	
#ifdef DO_STATISTIC	
// store the result statistic	
	string FileName = "Log\\TrendStats.txt";
	string NameScript,NameAsset,NameAlgo;
	if(WinTotal > LossTotal) {
		NameScript = strf("%s_Won",Script);
		NameAsset = strf("%s_Won",Asset);
		NameAlgo = strf("%s_Won",Algo);
	} else {
		NameScript = strf("%s_Lost",Script);
		NameAsset = strf("%s_Lost",Asset);
		NameAlgo = strf("%s_Lost",Algo);
	}
	lock();
	var Score = _getvar(FileName,NameScript);
	_putvar(FileName,NameScript,Score+1);
	Score = _getvar(FileName,NameAsset);
	_putvar(FileName,NameAsset,Score+1);
	Score = _getvar(FileName,NameAlgo);
	_putvar(FileName,NameAlgo,Score+1);
	unlock();
#endif	

#ifdef WRC
// store the curves of daily returns
	string FileName = "Log\\TrendDaily.bin";
	string Name = strf("%s_%s_%s_%i",Script,Asset,Algo,Period);
	int Size = Day*sizeof(var);
	lock();
	file_append(FileName,Name,strlen(Name)+1);
	file_append(FileName,&Size,sizeof(int));
	file_append(FileName,Daily,Size);
	unlock();
#endif
	
	return WinTotal/max(1,LossTotal); // Profit factor
}

var filter(var* Data,int Period);

void run()
{
	set(PARAMETERS|LOGFILE);
	PlotHeight1 = 200;
	PlotScale = 8;
	ColorBars[1] = BLACK; // winning trades
	ColorBars[2] = GREY; // losing trades

#ifdef WRC
	Spread = Commission = RollLong = RollShort = Slippage = 0;
#endif

	StartDate = 2010;
	BarPeriod = 15;
	LookBack = 80*4*24; // ~ 4 months
	
	while(asset(loop("EUR/USD","SPX500","XAG/USD")))
	while(algo(loop("M15","H1","H4")))
	{
		TimeFrame = 1;
		if(Algo == "H1")
			TimeFrame = 4;
		else if(Algo == "H4")
			TimeFrame = 4*4;	

		int Periods[10] = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };
		Period = Periods[optimize(1,1,10,1)-1];
		
		var *Price = series(price());
		var *Smoothed = series(filter(Price,Period));

		if(valley(Smoothed))
			enterLong();
		else if(peak(Smoothed))
			enterShort();
	} 
	
#ifdef WRC
// story daily result
	static int LastDay = 0;
	if(is(LOOKBACK))
		LastDay = Day = 0;
	else if(LastDay != day()) {
		Daily[Day++] = Balance;
		LastDay = day();
	}
#endif
}