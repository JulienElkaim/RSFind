#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "optionsToApply.h"
#include <string.h>
#include <dirent.h>
#include <magic.h>
#include "myFunctionalLib.h"



listOfFiles* applyIOption(listOfFiles* list){
	
	char* mime;
	magic_t magic;
	listOfFiles* tempList = malloc(sizeof(listOfFiles));
	tempList = list;


	//========== APPLY Restriction on EVERY \{first} ========== 

	while(list -> next != NULL){
		magic = magic_open(MAGIC_MIME_TYPE);
		magic_load(magic,NULL);
		mime = (char*)magic_file(magic,completePathBuilder(list -> next) );
		if(strstr(mime,"image/")==NULL){
			//N'est pas une image
			supprNextFileOf(&list);

		}else{
			//Est une image
			nextFile(&list);
		}
		magic_close(magic);	
	}

	//========== APPLY Restriction on first ========== 

	magic = magic_open(MAGIC_MIME_TYPE);
	magic_load(magic,NULL);
	mime = (char*)magic_file(magic,completePathBuilder(tempList) );
	if(strstr(mime,"image/")==NULL){
		tempList = tempList -> next; //N'est pas une image
	}

	return tempList;

}




listOfFiles* applyNOption(listOfFiles* list, char* str){
	
	listOfFiles* tempList = malloc(sizeof(listOfFiles));
	tempList = list;

	//========== APPLY Restriction on EVERY \{first} ========== 
	while(list -> next != NULL){
		
		if(strlen(list -> next -> myFile -> myName) >= strlen(str)){
			//myName est assez grand pour comporter ce prérequis
			
			if(strcmp(list -> next -> myFile -> myName, str) ==0 ){
				// Le nom est dans le nom de fichier
				nextFile(&list);
			}else{
				//Le nom n'est pas dans le nom de fichier
				supprNextFileOf(&list);
			}

		}else{
			//myName n'est pas assez grand, supprimer l'élement !
			supprNextFileOf(&list);

		}
	}

	//========== APPLY Restriction on first ========== 
	if(strcmp(tempList -> myFile -> myName, str) !=0 ){
		//Le premier elt ne possede pas le nom dans son nom
		tempList = tempList -> next;
	}

	return tempList;
}



listOfFiles* applyLOption(listOfFiles* list){

	listOfFiles* tempList = malloc(sizeof(listOfFiles));
	tempList = list;

	struct stat current_file;
	if(!stat(completePathBuilder(list), &current_file)){	
    	list -> myFile -> myStat = current_file;
	}
	while(nextFile(&list)){
		    
	    if(!stat(completePathBuilder(list), &current_file)){	
	    	list -> myFile -> myStat = current_file;
		}
	}

	return tempList;
}



void applyLOptionPrint(listOfFiles* list,int isPOpt){

    char* mtimeFIRST = dateFormater( list -> myFile -> myStat.st_mtime);
	char * st_modeFIRST = malloc(11);
	st_modeFIRST = fonction_permission(list -> myFile -> myStat);
	if(isPOpt)
		printf("%s",list->myFile->myPrint);
    printf("%s %ld %s %s %ld %s %s\n",
               st_modeFIRST,
               list -> myFile -> myStat.st_nlink,
               getpwuid(list -> myFile -> myStat.st_uid)->pw_name,
               getpwuid(list -> myFile -> myStat.st_gid)->pw_name,
               list -> myFile -> myStat.st_size,
               mtimeFIRST,
               completePathBuilder(list));


	while(nextFile(&list))
	{
		char* mtime = dateFormater( list -> myFile -> myStat.st_mtime);
	    char * st_mode = fonction_permission(list -> myFile -> myStat);
        if(isPOpt)
			printf("%s",list->myFile->myPrint);
        printf("%s %ld %s %s %ld %s %s\n",
               st_mode,
               list -> myFile -> myStat.st_nlink,
               getpwuid(list -> myFile -> myStat.st_uid)->pw_name,
               getpwuid(list -> myFile -> myStat.st_gid)->pw_name,
               list -> myFile -> myStat.st_size,
               mtime,
               completePathBuilder(list));
        
       
    }
}