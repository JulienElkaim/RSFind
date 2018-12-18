#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "myFunctionalLib.h"
#include "argsHandler.h"
#include "searcher.h"
#include "optionsToApply.h"
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <locale.h>


int main(int argc, char** argv){
	
	//==========Local Settlement==========
	
	setlocale(LC_ALL,"");

	//==========Options Checking==========

	int returnOferrInArg = errInArg(argc, argv);
	if (returnOferrInArg!=0)
		if (returnOferrInArg==1)
			return 1;
		else if (returnOferrInArg ==2)
			return 1;
	


	//==========Path Definition==========
	
	char* myPath;
	if (argc>1)
		if (argv[1][0]=='-')
			myPath = ".";
		else
			myPath = argv[1];	
	else
		myPath = ".";

	DIR* initDir;
	initDir = opendir(myPath);
	if(initDir==NULL)
		return 1; // NOT a valid path.

		
	//==========Options Dispatching==========

	int nOpt = 0, iOpt = 0, tOpt = 0;
	int lOpt = 0, eOpt = 0, pOpt = 0;
	char* nArg = malloc(1);
	char* tArg = malloc(1);
	char* eArg = malloc(1);

	if(optDispatcher(argc, argv, &lOpt, &tOpt, &tArg, &iOpt, &nOpt, &nArg, &eOpt, &eArg, &pOpt)){
		return 1; // Wrong entry.
	}
	


	//==========Recursive Research==========
	listOfFiles* myList = malloc(sizeof(listOfFiles));
	myList -> myFile = create_File(myPath, "", 0);
	myList -> next = NULL;
	if(finderRecursive(myList))
		return 1; //Impossible to open.


	
	//==========Apply Restrictions==========

	if (nOpt){myList = applyNOption(myList, nArg);}
	
	if (iOpt){myList = applyIOption(myList);}

	if (tOpt){/*Apply the -i restriction : BENJAMIN*/}



	//==========Datas Complements==========
	
	if (lOpt){ myList = applyLOption(myList); }
	


	//==========Execution on Result==========
	
	if (eOpt){/*Apply the -exec with a pipe : JULIEN*/}
	


	//==========PRINT IT OR NOT==========
	/*
	if (pOpt)
		if(lOpt)
			applyLOptionPrint(myList, 1);
		else
			printListOfFiles(myList);
	else
		if(lOpt)
			applyLOptionPrint(myList, 0);
		else
			printListOfFiles(myList);

		*/

	printerGeneral(myList,pOpt,lOpt,eOpt);
	

	return 0;
}






