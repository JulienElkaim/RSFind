#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "argsHandler.h"
#include <string.h>

int errInArg(int argc, char** argv){
	//Si la liste des arguments est mal entrée, 

	int iOption = 0;
	int rsFindOptions;
	int status;

	if(fork()==0){//fils
		while((rsFindOptions = getopt_long(argc, argv, "lt:in:e:p", myLongOptions, &iOption)) != -1){
			if (optarg!=NULL){
				if(optarg[0]=='-'){
					exit(1);
				} // Une erreur se produit
			}else{
				if (rsFindOptions=='?')
					exit(2); //Missing an argument here
			}
		}exit(0);
	}else{//pere
		wait(&status);
		if(WIFEXITED(status)){
			if(WEXITSTATUS(status)==0){
				//tout etait normal
				return 0;
			}else{
				return 1;
			}
		}
	}
	
}

int optDispatcher(int argc, char** argv, int* lOpt, int* tOpt, char** tArg, int* iOpt, int* nOpt, char** nArg, int* eOpt, char** eArg, int* pOpt){

	int iOption =0; //Useful to find the long_option characteristic
	int rsFindOptions;

	if (argc==1){
		*pOpt = 1;
	}else{
		if (argc==2 && argv[1][0]!='-'){
			
			*pOpt=1;
		}
	}

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
				printf("Je passe \n");
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


