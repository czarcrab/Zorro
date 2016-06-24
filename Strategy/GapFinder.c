// Display gaps in historical data.
// Red lines = gap length in days. 

function run()
{
	LookBack = 0;
	set(PLOTNOW);
	var m = minutesAgo(1);
	plot("Gap",m/(60*24),NEW,RED);
}