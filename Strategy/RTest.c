#include <r.h>

//#define DIAG

function main()
{
#ifdef DIAG	
	if(!g->sRTermPath) {
		printf("R path missing! ");
		return;
	}
	if(!file_date(g->sRTermPath)) {
		printf("%s not found! ",g->sRTermPath);
		return;
	}
	string Cmd = strf("%s  --no-save",g->sRTermPath);
	printf(Cmd); 
	hR = RInit_(Cmd,2);
	if(!hR) {
		printf("Can't initialize RTerm! ");
		return;
	}
	printf("\nR initialized!");
	RExecute(hR,"rm(list = ls());"); 
	printf("\n%s",RLastOutput(hR));
	if(!RIsRunning(hR)) {
		printf("\nR stopped!");
		return;
	} else
		printf("\nR running...");
#else
	if(!Rstart()) return;
	Rx("rm(list = ls());"); // clear the workspace
#endif
	
	var vecIn[5],vecOut[5];
	int i;
	for(i=0; i<5; i++) 
		vecIn[i] = i;
	
	Rset("Rin",vecIn,5);
	Rx("Rout <- Rin * 10");
	//Rx("print(Rout)",3); // display R output
	Rv("Rout",vecOut,5);
	
	if(!Rrun()) 
		printf("Error - R session aborted!");
	else {
		printf("\nReturned: ");
		for(i=0; i<5; i++) 
			printf("%.0f ",vecOut[i]);
	}
}
