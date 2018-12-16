#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "optionsToApply.h"
#include <string.h>
#include <dirent.h>
//#include <debian/magic.h> // Find le good h pour mime type
#include "myFunctionalLib.h"

/*listOfFiles* applyIOption(listOfFiles* list){
		listOfFiles* tempList = malloc(sizeof(listOfFiles));
	tempList = list; // Garder un pointeur sur le premier
	char* mime;
	magic_t magic;
	while(list -> next != NULL){
		magic = magic_open(MAGIC_MIME_TYPE);
		magic_load(magic,NULL);
		magic_compile(magic,NULL);
		mime = magic_file(magic,list -> next -> myFile -> myName);
		if(strstr(mime,"image/")==NULL){
			//N'est pas une image
			supprNextFileOf(&list);

		}else{
			//Est une image
			nextFile(&list);
		}
		magic_close(magic);	
	}

	// Faire le test sur le premier element
	magic = magic_open(MAGIC_MIME_TYPE);
	magic_load(magic,NULL);
	magic_compile(magic,NULL);
	mime = magic_file(magic,tempList -> myFile -> myName);
	
	if(strstr(mime,"image/")==NULL){
		//N'est pas une image
		tempList = tempList -> next;
	}

	return tempList;
}

*/


listOfFiles* applyNOption(listOfFiles* list, char* str){
	//Comparer le nom de l'élement avec str
	listOfFiles* tempList = malloc(sizeof(listOfFiles));
	tempList = list; // Garder un pointeur sur le premier
	while(list -> next != NULL){
		
		if(strlen(list -> next -> myFile -> myName) >= strlen(str)){
			//myName est assez grand pour comporter ce prérequis
			
			if(strstr(list -> next -> myFile -> myName, str) != NULL){
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

	// Faire le test sur le premier element
	if(strstr(tempList -> myFile -> myName, str) == NULL){
		//Le premier elt ne possede pas le nom dans son nom
		tempList = tempList -> next;
	}

	return tempList;
}