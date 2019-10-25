#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "argsHandler.h"
#include <string.h>


static struct option myLongOptions[] =
	{
		{"name", required_argument, 0, 'n'}, //optarg is the char* used to know the argument
		{"exec", required_argument, 0, 'e'},
		{"print", no_argument, 0, 'p'},
		{0,0,0,0}
	};



int errInArg(int argc, char** argv){

	int iOption = 0;
	int rsFindOptions;
	int status;

	if(fork()==0){ // FORK ! SON
		while((rsFindOptions = getopt_long(argc, argv, "lt:in:e:p", myLongOptions, &iOption)) != -1){
			if (optarg!=NULL){
				if(optarg[0]=='-'){
					exit(1); // Une erreur se produit
				} 
			}else{
				if (rsFindOptions=='?')
					exit(2); //Missing an argument here
			}
		}
		exit(0);

	}else{ // FORK ! FATHER
		wait(&status);
		if(WIFEXITED(status)){
			if(WEXITSTATUS(status)==0){
				return 0; // Good.
			}else{
				return 1; // Not Good.
			}
		}
	}
	return 0;
}



int optDispatcher(int argc, char** argv, int* lOpt, int* tOpt, char** tArg, int* iOpt, int* nOpt, char** nArg, int* eOpt, char** eArg, int* pOpt){

	int iOption =0;
	int rsFindOptions;

	while((rsFindOptions = getopt_long(argc, argv, "lt:in:e:p", myLongOptions, &iOption)) != -1){
		
		switch(rsFindOptions){ 

			case 'l':
				*lOpt = 1; 
				break;
			case 't':
				*tOpt = 1;
				*tArg = malloc(sizeof(char)*(strlen(optarg)+1) );
				memset(*tArg, 0,sizeof(char)*(strlen(optarg)+1) );
				strcpy(*tArg, optarg);
				break;
			case 'i':
				*iOpt = 1;
				break;
			case 'n':
				*nOpt = 1;
				*nArg = malloc(sizeof(char)*(strlen(optarg)+1) );
				memset(*nArg, 0,sizeof(char)*(strlen(optarg)+1) );
				strcpy(*nArg, optarg);
				break;
			
			case 'e':
				*eOpt = 1;
				*eArg = malloc(sizeof(char)*(strlen(optarg)+1) );
				memset(*eArg, 0,sizeof(char)*(strlen(optarg)+1) );
				strcpy(*eArg, optarg);
				break;
			case 'p':
				*pOpt = 1;
				break;
			default:
				//invalid argument ! 
				return 1;
		}
		
	}

	return 0;

}


