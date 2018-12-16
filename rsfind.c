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

char* fonction_permission(struct stat s);
char* date(time_t st_mdate);

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
	myList -> myFile = create_File(myPath, "");
	myList -> next = NULL;

	if(finderRecursive(myList))
		//Not good, impossible to open it
		return 1;
	
	//==========RESTRICTIONS==========
	if (nOpt){
		myList = applyNOption(myList, nArg);
		//Apply the --name restriction with nArg
		//JULIEN
	}

	if (iOpt){
		//myList = applyIOption(myList);
		//Apply the -i restriction
		//JULIEN
	}

	if (tOpt){
		//Apply the -i restriction
		//BENJAMIN
	}

	//==========MORE DATA==========
	listOfFiles* listTampon = malloc(sizeof(listOfFiles));
	myListOfFilesPtrCpy(&listTampon, myList);
	
	if (lOpt){
		//Apply the -l format
		//BENJAMIN
		
		while(nextFile(&myList)) //
		{
		    struct stat current_file;
		    if(!stat(completePathBuilder(myList), &current_file))		    
		    {	
    	        myList -> myFile -> myStat = current_file;
		     }
		}
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
			
		    myListOfFilesPtrCpy(&myList, listTampon);
			while(nextFile(&myList))
			{
			    char* mtime = date( myList -> myFile -> myStat.st_mtime);
                
			    char * st_mode = fonction_permission(myList -> myFile -> myStat);
		        printf("%s %ld %s %s %ld %s %s\n",
                       st_mode,
                       myList -> myFile -> myStat.st_nlink,
                       getpwuid(myList -> myFile -> myStat.st_uid)->pw_name,
                       getpwuid(myList -> myFile -> myStat.st_gid)->pw_name,
                       myList -> myFile -> myStat.st_size,
                       mtime,
                       completePathBuilder(myList));
            }
		}
		else{
			printListOfFiles(myList);
			//JULIEN
		}
	}
	/*
	listOfFiles* testList = malloc(sizeof(listOfFiles));
	testList = myList;
	printf("\n\n");
	printf("Complete Path first Elt: %s\n", completePathBuilder( testList));
	nextFile(&testList);
	printf("Complete Path second Elt: %s\n", completePathBuilder( testList));
	printf("\n\n");
	printf("CompletePath third elt BEFORE: %s\n", completePathBuilder(testList -> next));
	printf("CompletePath fourth elt BEFORE: %s\n", completePathBuilder(testList-> next -> next));
	supprNextFileOf(&testList);
	printf("\n\n");
	printf("CompletePath third elt AFTER: %s\n", completePathBuilder(testList -> next));
	printf("CompletePath fourth elt AFTER: %s\n", completePathBuilder(testList-> next -> next));

	*/
	return 0;
}

char* fonction_permission(struct stat s)
{
    char* string = malloc(11);
    
    strcpy(string,(S_ISDIR(s.st_mode))  ? "d" : "-");
    strcat(string,(s.st_mode & S_IRUSR) ? "r" : "-");
    strcat(string,(s.st_mode & S_IWUSR) ? "w" : "-");
    strcat(string,(s.st_mode & S_IXUSR) ? "x" : "-");
    strcat(string,(s.st_mode & S_IRGRP) ? "r" : "-");
    strcat(string,(s.st_mode & S_IWGRP) ? "w" : "-");
    strcat(string,(s.st_mode & S_IXGRP) ? "x" : "-");
    strcat(string,(s.st_mode & S_IROTH) ? "r" : "-");
    strcat(string,(s.st_mode & S_IWOTH) ? "w" : "-");
    strcat(string,(s.st_mode & S_IXOTH) ? "x" : "-");

    return string;
}

char* date(time_t st_mdate)
{
    char *result;
    strftime(result, 30, "%b %H:%M:%S", localtime(&st_mdate));
    return result;
}


