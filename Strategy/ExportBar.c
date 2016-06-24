string Filename = "Log\\Test.bar";

function main()
{
	file_delete("Data\\exportBar.csv");
	TICK *Ticks = file_content(Filename);
	int nTicks = file_length(Filename)/sizeof(TICK);

	BAR b; 
	g->bars = &b;	// dummy bar for the day()... functions
	while(nTicks--) 
	{
		TICK *t = Ticks+nTicks;
		b.time_base = t->time;
		b.time_span = 0.;
		string line = strf(
			"%02i/%02i/%02i %02i:%02i, %.5f, %.5f, %.5f, %.5f\n",
			day(),month(),year()%100,hour(),minute(),
			(var)t->fOpen,(var)t->fHigh,(var)t->fLow,(var)t->fClose);
		file_append("Data\\exportBar.csv",line);
	}
	g->bars = 0;
}