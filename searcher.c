#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "searcher.h"
#include <string.h>
#include <dirent.h>
#include "myFunctionalLib.h"



int finderRecursive(char* myPath, char* previousPath, char** strStack){	//test si je peux ouvrir ce folder
	// Verification of this directory
	char* pathComplete="";
	myStrCat(&pathComplete,previousPath);
	slashItCorrectly(&pathComplete);
	myStrCat(&pathComplete,myPath);
	
					//printf("AvantMonexec, le pathcomplete est %s",pathcomplete);
	DIR* currDir;
	currDir = opendir(pathComplete);
	if(currDir==NULL)
		return 1;  //directory not allowed to visit it

	//Proceed !
	
	struct dirent* dir;
	while((dir =readdir(currDir))!=NULL){
		printf("%s",*strStack);
		printf("!!!!!!!!!!!!\n");
		if(dir -> d_type == DT_DIR){
		
			//cest un folder
			
			// Ajouter a strStack la chaine pathComplete +"/"+ d_name + \n
			myStrCat(strStack,pathComplete);
			slashItCorrectly(strStack);
			myStrCat(strStack, dir -> d_name);
			myStrCat(strStack,"\n");

			// Effectuer le finder sur ce folder
			finderRecursive(dir -> d_name, pathComplete, strStack);

		}else{
			
			//cest un simple fichier
	
			// Ajouter a strStack la chaine pathComplete +"/"+ d_name + \n
			myStrCat(strStack,pathComplete);
			slashItCorrectly(strStack);
			myStrCat(strStack, dir -> d_name);
			myStrCat(strStack,"\n");
		}


	}

	return 0;

}

