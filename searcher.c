#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "searcher.h"
#include <string.h>
#include <dirent.h>
#include "myFunctionalLib.h"

void whosLAST(listOfFiles* myList){
	listOfFiles* nextList;
	nextList = malloc(sizeof(listOfFiles));
				
	myListOfFilesPtrCpy(&nextList, myList);
			
	while(nextList -> next != NULL)
		myListOfFilesPtrCpy(&nextList, nextList -> next); // Devenir le dernier de la liste
		
	printf("Voci le dernier: %s", nextList -> myFile -> myPrint);
}	


int finderRecursive(listOfFiles* list){	

	char* completePATH = malloc(sizeof(char)*(strlen(list-> myFile -> myName) + strlen(list ->  myFile -> myPath) + 2) );
	strcpy(completePATH,list -> myFile -> myPath);
	if(strlen(list -> myFile -> myPath)>0)
		myStrCat(&completePATH, "/");
	myStrCat(&completePATH, list-> myFile -> myName);

	DIR* currDir;
	currDir = opendir(completePATH);
	if(currDir==NULL)
		return 1;  //directory not allowed to visit it

	struct dirent* dir;


	listOfFiles* nextList;
	while((dir =readdir(currDir))!=NULL){
		
		if(dir -> d_type == DT_DIR){
			//cest un folder
			if (strcmp(dir -> d_name,"..")==0 ||strcmp(dir -> d_name,".")==0){
				//Nothing Happen...
			}else{
				//We proceed
								
				
				insertFile( create_File(dir -> d_name, completePATH,NULL,NULL,NULL,NULL,NULL,NULL),
				 list);
				
				nextList = malloc(sizeof(listOfFiles));
				
				myListOfFilesPtrCpy(&nextList, list);
				while(nextList -> next != NULL)
					myListOfFilesPtrCpy(&nextList, nextList -> next); // Devenir le dernier de la liste
				
				
				if(finderRecursive(nextList)){
					// returned a POSITIVE, Something wrong happened !
					return 1;
				}
			}
			
			//Si Oui add avec create_File & applique finderRecursive

		}else{
			//cest un simple fichier
			insertFile( create_File(dir -> d_name, completePATH,NULL,NULL,NULL,NULL,NULL,NULL),
			 list);


	
		}


	}

	closedir(currDir);

	return 0;

}

