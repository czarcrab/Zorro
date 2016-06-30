// convert price history from .csv to .bar

#define HISTDATA
//#define YAHOO // convert csv data from R or Yahoo
#define ADJUSTED	// use adjusted prices

#ifdef HISTDATA
string InName = "History\\DAT_ASCII_EURUSD_M1_2015.csv";  // name of the CSV file
string OutName = "History\\EURUSD_2015x.bar";
#endif
#ifdef YAHOO
string InName = "History\\table.csv";  // name of the CSV file
string OutName = "History\\Stock.bar";
#endif

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME;

API(SystemTimeToVariantTime,oleaut32)
int _stdcall SystemTimeToVariantTime(SYSTEMTIME* lpSystemTime, double* pvtime);

DATE ConvertTime(int Year,int Month,int Dom,int Hour,int Minute,int Second)
{
	SYSTEMTIME Time;
	memset(&Time,0,sizeof(SYSTEMTIME));
	if(Year < 50) Year += 2000;
	else if(Year < 100) year += 1900;
	Time.wYear = Year;
	Time.wMonth = Month;
	Time.wDay = Dom;
	Time.wHour = Hour;
	Time.wMinute = Minute;
	Time.wSecond = Second;
	
	DATE vTime;
	SystemTimeToVariantTime(&Time,&vTime);
#ifdef HISTDATA
	vTime += 5./24.; // add 5 hours for converting EST to UTC
#endif
	return vTime;
}

string readTick(string content,TICK* tick)
{
// tokenize a single line	
	char* line = strtok(content,"\n");
	if(!line) return 0;

	int Year, Month, Dom, Hour = 0, Minute = 0, Second = 0; 
#ifdef HISTDATA // line format "20100103 170000;1.430100;1.430400;1.430100;1.430400;0"

	if(10 != sscanf(line,"%4d%2d%2d %2d%2d%2d;%f;%f;%f;%f;",
		&Year, &Month, &Dom, &Hour, &Minute, &Second,
		&tick->fOpen, &tick->fHigh, &tick->fLow, &tick->fClose)) 
		return 0;
#endif
#ifdef YAHOO // line format "2015-05-29,43.45,43.59,42.81,42.94,10901500,42.94"
	float fVol,fAdj;

	if(9 != sscanf(line,"%4d-%2d-%2d,%f,%f,%f,%f,%f,%f",
		&Year, &Month, &Dom,
		&tick->fOpen, &tick->fHigh, &tick->fLow, &tick->fClose,&fVol,&fAdj)) 
		return 0;
#ifdef ADJUSTED
  if(tick->fClose > 0. && fAdj > 0.) {
		float f = fAdj/tick->fClose;
		tick->fOpen *= f;
		tick->fHigh *= f;
		tick->fLow *= f;
		tick->fClose = fAdj;
	}
#endif		
#endif

#ifdef PRINT
	printf("\n%4d-%2d-%2d, %.4f, %.4f, %.4f, %.4f",
		Year, Month, Dom,
		(var)tick->fOpen, (var)tick->fHigh, (var)tick->fLow, (var)tick->fClose);
#endif

// store the time in DATE format
	tick->time = ConvertTime(Year,Month,Dom,Hour,Minute,Second);

// return pointer to next line
	return line+strlen(line)+1;
}

function main()
{
	if(!file_length(InName)) {
		quit("Data file not found!");
		return;
	}
	string content = file_content(InName);
		
// allocate TICK array		
	int maxticks = 60*24*365; 
	TICK* ticks = malloc(maxticks*sizeof(TICK));

#ifdef HISTDATA
// read ticks in reverse order	
	TICK* tick = ticks+maxticks; 
	while(content)
		content = readTick(content,--tick);

// store the ticks
	int size = (int)(ticks+maxticks)-(int)(tick+1);
	file_write(OutName,tick+1,size);
#endif	

#ifdef YAHOO
// skip the header
	content = strstr(content,"\n")+1;
// already contains ticks in reverse order	
	TICK* tick = ticks; 
	while(content) {
		content = readTick(content,tick++);
	}
// store the ticks
	int size = (int)(tick-1)-(int)(ticks);
	file_write(OutName,ticks,size);
#endif	

	free(ticks);
	printf("\nRead %d ticks",size/sizeof(TICK));
}