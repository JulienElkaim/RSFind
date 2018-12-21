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
#include <fcntl.h>


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

int rememberExecResult(char** myEPrint, char** cmd, char* thePath){

	int pid, p[2], status;
    pipe(p);

    if( (pid = fork()) ){// POSITIVE, Dad
        wait(&status);
        if(WIFEXITED(status)){
        	if(WEXITSTATUS(status)==0){
    
        		//---- RECEIVE THE MESSAGE ----
        		close(p[1]);
        		char BUFF;
        		char* strToReceive="";
        		
        		while (read(p[0], &BUFF, 1) > 0){
        			myStrCat(&strToReceive, &BUFF);
      			}

      			// ----- RECUPERER L'INFORMATION -----
			printf("==========================\n");
			printf("%s\n", strToReceive);
			printf("==========================\n");
      			*myEPrint = malloc(sizeof(char)* strlen(strToReceive)+1);
      			strcpy(*myEPrint, strToReceive);
      			
        		return 0;
        	}else{

        		return 1; // Not Good finishing
        	}
        }else{
        
        	return 1;
        }


    }else{ // NILL, Son
    	dup2(p[1],1);
    	close(p[0]);
    	if(!changeMyBrackets(cmd,thePath)){
    		//return 1;
    	}
		char* myTest= "eebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuebfieyfukqyfbuefbqkuezebfieyfukqyfbuefbqkuez";
    	printf("%s", myTest);
    	//----- COMPUTE RESULT -----
    	
    	//execvp(cmd[0],cmd);
    
	}


	return 0;
}




listOfFiles* applyEOption(listOfFiles* list, char* eArg){
	listOfFiles* tempList = malloc(sizeof(listOfFiles));
	tempList = list;

	//===== DIVIDE l'argument en un tableau de char* =====
	char** tabOfString = splitMyString(eArg);

	//===== APPLY Restriction on EVERYONE =====
	while (list -> next != NULL){

		//TAKE IN MEMORY THE EXEC RESULT
		rememberExecResult( &(list -> next -> myFile -> myEPrint), tabOfString, completePathBuilder(list-> next) );
		nextFile(&list);  
		
	}

	//===== APPLY Restriction on FIRSTONE =====
	rememberExecResult( &(tempList -> myFile -> myEPrint), tabOfString, completePathBuilder(tempList));

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

	if(isPOpt)
		printf("%s",list->myFile->myPrint);
	printerOfLOption(list);

	while(nextFile(&list))
	{
		if(isPOpt)
			printf("%s",list->myFile->myPrint);
        printerOfLOption(list);
    }
}

void printerOfLOption(listOfFiles* list){
	char* mtime = dateFormater( list -> myFile -> myStat.st_mtime);
	char * st_mode = fonction_permission(list -> myFile -> myStat);
        
	printf("%s %ld %s %s %ld %s %s\n",
               st_mode,
               list -> myFile -> myStat.st_nlink,
               getpwuid(list -> myFile -> myStat.st_uid)->pw_name,
               getpwuid(list -> myFile -> myStat.st_gid)->pw_name,
               list -> myFile -> myStat.st_size,
               mtime,
               completePathBuilder(list));
}


void printerGeneral(listOfFiles* list, int pOpt, int lOpt, int eOpt){
	while(list != NULL){
		if(pOpt || !(pOpt+lOpt+eOpt) ){
			printf("%s", list -> myFile -> myPrint);
		}

		if(lOpt){
			printerOfLOption(list);
		}
		if(eOpt){
			printf("%s", list -> myFile -> myEPrint);
			
		}
		list = list -> next;
	}
}

listOfFiles* applyTOption(listOfFiles* list, char* tArg){

	listOfFiles* tempList = malloc(sizeof(listOfFiles));
	tempList = list;
	
	//========== APPLY Restriction on EVERY \{first} ========== 

	while(list -> next != NULL)
	{
		if(list -> next -> myFile -> isItAFile)
		{
			char BUFF;
			int fd;
			char* readFile = "";

			fd = open(completePathBuilder(list->next), O_RDONLY);
			while(read(fd, &BUFF, 1) > 0)
			{
				myStrCat(&readFile, &BUFF);
			}
			close(fd);
			if(!strstr(readFile, tArg))
			{
				supprNextFileOf(&list);
			}else{
				nextFile(&list);
			}
		}else
		{
			supprNextFileOf(&list);
		}
	}

	//========== APPLY Restriction on first ========== 
	
	if(tempList->myFile->isItAFile)
	{
		char BUFF;
		char* readFile = "";
		int fd;

		fd = open(completePathBuilder(tempList), O_RDONLY);
		while(read(fd, &BUFF, 1) > 0)
		{
			myStrCat(&readFile, &BUFF);
		}
		if(!strstr(readFile, tArg))
		{
			tempList = tempList -> next; 
		}		
		close(fd);
	}else{
		tempList = tempList -> next;
	}
	return tempList;	
}
