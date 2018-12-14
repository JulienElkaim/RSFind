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
	
	
	// Choix du path
	char* myPath;
	if (argc>1){
		if (argv[1][0]=='-'){
			//No Path defined, default path
			myPath = ".";
		}else
			//Path defined
			myPath = argv[1];	
	}else{
		//ZERO Args/Opts given
		myPath = ".";
		
	}

	int lOpt =0;
	int tOpt =0;
	char* tArg = malloc(1);
	int iOpt =0;
	int nOpt =0;
	char* nArg = malloc(1);
	int eOpt =0;
	char* eArg = malloc(1);
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

	//Verif validity path

	DIR* initDir;
	initDir = opendir(myPath);
	if(initDir==NULL)
		return 1; // NOT a valid directory

	//EXECUTER la recherche recursive avec dirent
	

	listOfFiles* myList = malloc(sizeof(listOfFiles));
	myList -> myFile = create_File(myPath, "",NULL,NULL,NULL,NULL,NULL,NULL);
	myList -> next = NULL;

	if(finderRecursive(myList))
		//Not good, impossible to open it
		return 1;
	
	//==========RESTRICTIONS==========
	if (nOpt){
		//Apply the --name restriction with nArg
		//JULIEN
	}

	if (iOpt){
		//Apply the -i restriction
		//JULIEN
	}

	if (tOpt){
		//Apply the -i restriction
		//BENJAMIN
	}

	//==========MORE DATA==========
	if (lOpt){
		//Apply the -l format
		//BENJAMIN
	}
	//==========LAUNCH THE RESULT IN EXEC==========
	if (eOpt){
		//Apply the -exec with a pipe
		//JULIEN

	}
	//==========PRINT IT OR NOT==========
	if (pOpt){
		if(lOpt){
			//PRINT with the -l relative datas
			//BENJAMIN
		}
		else{
			printListOfFiles(myList);
			//JULIEN
		}
	}



	return 0;
}



