#include<string.h>
#include<stdlib.h>
#include<stdio.h>


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
	//If it does not end with a /, add it.
	if (strlen(*str)>=1)
		if (*str[myStrLen(*str)-1] != '/')
			myStrCat(str, "/");	
	
}