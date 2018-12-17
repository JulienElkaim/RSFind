#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "searcher.h"
#include <string.h>
#include <dirent.h>
#include "myFunctionalLib.h"


int finderRecursive(listOfFiles* list){	

	//========== SET the complete Path =========== 

	char* completePATH = malloc(sizeof(char)*(strlen(list-> myFile -> myName) + strlen(list ->  myFile -> myPath) + 2) );
	strcpy(completePATH,list -> myFile -> myPath);
	slashItCorrectly(&completePATH);
	myStrCat(&completePATH, list-> myFile -> myName);

	//========== TEST the disponibility of this Directory =========== 
	DIR* currDir;
	currDir = opendir(completePATH);
	if(currDir==NULL)
		return 1;  //Not allowed to visit it.


	//========== SKIM the Folder =========== 
	struct dirent* dir;
	listOfFiles* nextList;

	while((dir =readdir(currDir))!=NULL){
		
		if(dir -> d_type == DT_DIR){
			//--- THIS IS A FOLDER ---

			if (strcmp(dir -> d_name,"..")==0 ||strcmp(dir -> d_name,".")==0){
				//Nothing Happen...
			}else{		
				
				insertFile( create_File(dir -> d_name, completePATH, 0), list);
				nextList = malloc(sizeof(listOfFiles));
				myListOfFilesPtrCpy(&nextList, list);
				while(nextList -> next != NULL)
					myListOfFilesPtrCpy(&nextList, nextList -> next);
				
				if(finderRecursive(nextList))
					return 1; //A Folder was not available.
				
			}
			
		

		}else{
			//--- THIS IS A FILE ---
			insertFile( create_File(dir -> d_name, completePATH, 1), list);
		}
	}

	closedir(currDir);

	return 0;

}

