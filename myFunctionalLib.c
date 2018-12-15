#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "myFunctionalLib.h"
// Structural FUNCTIONS


MyFile* create_File(char* name, char* path, mode_t* perms, nlink_t* links, uid_t* usrID, gid_t* grpID, off_t* sizeFile, time_t* lastMod){

	MyFile* myFileCreated = malloc(sizeof(MyFile));

	myFileCreated -> myName = malloc(sizeof(char) * (strlen(name)+1));
	strcpy(myFileCreated -> myName,name);
	myFileCreated -> myPath = malloc(sizeof(char) * (strlen(path)+1));
	strcpy(myFileCreated -> myPath, path);

	myFileCreated -> myPrint = malloc( sizeof(char) * (strlen(name) + strlen(path)+3) ); //carac de fin, \n et le / entre les deux
	strcpy(myFileCreated -> myPrint, path);
	slashItCorrectly(&(myFileCreated->myPrint));
	myStrCat(&(myFileCreated->myPrint), name);
	myStrCat(&(myFileCreated->myPrint), "\n");


	myFileCreated -> myPerms = malloc(sizeof(mode_t));
	myFileCreated -> myPerms = perms;
	myFileCreated -> myLinks = malloc(sizeof(nlink_t));
	myFileCreated -> myLinks = links;
	myFileCreated -> myUsrId = malloc(sizeof(uid_t));
	myFileCreated -> myUsrId = usrID;
	myFileCreated -> myGrpId = malloc(sizeof(gid_t));
	myFileCreated -> myGrpId = grpID;
	myFileCreated -> mySizeFile = malloc(sizeof(off_t));
	myFileCreated -> mySizeFile = sizeFile;
	myFileCreated -> myLastMod = malloc(sizeof(time_t));
	myFileCreated -> myLastMod = lastMod;


	return myFileCreated;
}


listOfFiles* insertFile(MyFile* newFile, listOfFiles* list){
	listOfFiles* newList = malloc(sizeof(listOfFiles));
	newList -> myFile = newFile;
	newList -> next = NULL;

	listOfFiles* listParcours = list;
	while(listParcours -> next != NULL)
		listParcours = listParcours -> next;
	listParcours -> next = newList;


	return list;
}


void printListOfFiles(listOfFiles* list){
	while(list != NULL){
		printf("%s", list -> myFile -> myPrint);
		list = list -> next;
	}
}

void myListOfFilesPtrCpy(listOfFiles** dest, listOfFiles* ptrToCpy){
	*dest = ptrToCpy;
}

int nextFile(listOfFiles** list){
	listOfFiles* temp = malloc(sizeof(listOfFiles));
	temp = *list;
	if(temp -> next != NULL){// Un Next existe, la liste continue
		myListOfFilesPtrCpy(list, temp -> next);
		return 1;
	}else{ // Il n'y a plus d'élément après celui là

		return 0;
	}
}

int supprNextFileOf(listOfFiles** list){
	listOfFiles* temp = malloc(sizeof(listOfFiles));
	temp = *list;
	if (temp->next == NULL){
		//Next existe pas, rien à supprimer
		return 0;
	}else{
		//Next existe si le code ci dessous s'exécute
		temp -> next = temp -> next -> next;
	}
	return 1;
}


// USUAL FUNCTIONS

char* completePathBuilder(listOfFiles* list){
	
	char* pathToBuild = malloc(sizeof(char) * (strlen(list -> myFile -> myPath) + 1 + strlen(list -> myFile -> myName) +1) );
	
	strcpy(pathToBuild, list -> myFile -> myPath);
	slashItCorrectly(&pathToBuild);
	myStrCat(&pathToBuild, list-> myFile -> myName);

	return pathToBuild;

}

void myStrPtrCpy(char** dest, char* ptrToCpy){
	*dest = ptrToCpy;
}

void myStrCat(char** dest, char*c){

	char* temp = malloc(sizeof(char) * ( strlen(*dest) + strlen(c) + 1 ) );
	strcpy(temp, *dest);
	strcat(temp, c);
	myStrPtrCpy(dest, temp);
}



int myStrLen(char* strToSize){
	int taille=0;
	while (strToSize[taille]!='\0')
		taille++;
	return taille;
}
void slashItCorrectly(char** str){
	
	char c;
	int boolean =0, i=0;
	if(strlen(*str) > 0){
		//Le path est pas vide, faut slasher si pas deja fait
		c = (*str)[i];
		while(c != '\0'){
			if (c=='/')
				boolean = 1;
			else
				boolean = 0;
			i++;
			c = (*str)[i];
		}
		if(boolean == 0){myStrCat(str,"/");}
	}

}