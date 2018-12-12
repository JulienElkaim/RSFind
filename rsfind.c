#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "argsHandler.h"
#include <string.h>


int main(int argc, char** argv){
	
	int returnOferrInArg = errInArg(argc, argv);
	if (returnOferrInArg!=0){
		if (returnOferrInArg==1){
			return returnOferrInArg;
		}else if (returnOferrInArg ==2){
			return returnOferrInArg;
		}
	}

	int lOpt =0;
	int tOpt =0;
	char* tArg;
	int iOpt =0;
	int nOpt =0;
	char* nArg;
	int eOpt =0;
	char* eArg;
	int pOpt =0;

	if(optDispatcher(argc, argv, &lOpt, &tOpt, &tArg, &iOpt, &nOpt, &nArg, &eOpt, &eArg, &pOpt)){
		//Un mauvais argument, s'ârrête subitement
		return 1;
	}

	/*
	printf("lOpt is %d \n",lOpt);
	printf("tOpt is %d and argument is %s\n",tOpt, tArg);
	printf("iOpt is %d \n",iOpt);
	printf("nOpt is %d and argument is %s\n",nOpt, nArg);
	printf("eOpt is %d and argument is %s\n",eOpt, eArg);
	printf("pOpt is %d \n",pOpt);
	*/

	//EXECUTER la recherche recursive avec dirent

	//APPLIQUER les restrictions -n puis -i puis -t

	//APPLIQUER le format -l

	//EXEC sur le resultat avec du pipe

	//PRINT






	return 0;
}


