#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "optionsToApply.h"
#include <string.h>
#include <dirent.h>
#include "myFunctionalLib.h"


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