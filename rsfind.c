#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "myFunctionalLib.h"
#include "argsHandler.h"
#include "searcher.h"
#include <string.h>
#include <dirent.h>

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


	
	
	// Choix du path
	char* myPath;
	if (argc>1){
		if (argv[1][0]=='-')
			//No Path defined, default path
			myPath = ".";
		else
			//Path defined
			myPath = argv[1];	
	}else{
		//ZERO Args/Opts given
		myPath = ".";
	}
	//Verif validity path

	DIR* initDir;
	initDir = opendir(myPath);
	if(initDir==NULL)
		return 1; // NOT a valid directory

	//EXECUTER la recherche recursive avec dirent

	char* myResult="";
	char* myPreviousPath = "";
	myStrCat(&myResult, myPath);
	myStrCat(&myResult, "\n");

	printf("%s", myResult);
	
	if(finderRecursive(myPath, myPreviousPath, &myResult))
		//Not good, impossible to open it
		return 1;
	
	//printf("%s", myResult);


	//a partir de la all is good, on a myResult
	// settled pour être ensuite parsé et traité
	
	


	//APPLIQUER les restrictions -n puis -i puis -t

	//APPLIQUER le format -l

	//EXEC sur le resultat avec du pipe

	//PRINT






	return 0;
}



