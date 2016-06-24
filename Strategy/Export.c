//Export selected asset history to CSV

function run()
{
	StartDate = 20100101;
	LookBack = 0;
	//asset("AAPL");
	
	string Format = ifelse(assetType(Asset) == FOREX,
		"\n%04i-%02i-%02i %02i:%02i, %.5f, %.5f, %.5f, %.5f",
		"\n%04i-%02i-%02i %02i:%02i, %.1f, %.1f, %.1f, %.1f");
	char FileName[40];
	sprintf(FileName,"History\\%s.csv",strx(Asset,"/","")); // remove slash from forex pairs
	
	if(is(INITRUN))
		file_write(FileName,"Date,Open,High,Low,Close",0);
	else
		file_append(FileName,strf(Format,
			year(),month(),day(),hour(),minute(),
			round(priceOpen(),0.1*PIP),
			round(priceHigh(),0.1*PIP),
			round(priceLow(),0.1*PIP),
			round(priceClose(),0.1*PIP)));
}

// Generate a XTS object in R from the exported data:
// Data <- xts(read.zoo("MyAsset.csv",tz="UTC",format="%Y-%m-%d %H:%M",sep=",",header=TRUE))
