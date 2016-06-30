// Trend Experiment - ALMA
#include "Strategy\TrendMMI.c"

var filter(var* Data,int Period)
{
	return Laguerre(Data,2.0/(1+Period));
}