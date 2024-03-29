#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "myFunctionalLib.h"
#include <time.h>
#include <locale.h>

//========== Structural Functions ========== 

/*
 * Create pointer to the read file.
 */

MyFile* create_File(char* name, char* path, int myIsItAFile){

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

	myFileCreated -> isItAFile = myIsItAFile;



	return myFileCreated;
}


/*
 * Add pointer of read file at the end of the table of the pointer to the files.
 */

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

/*
 * Print the list of read files.
 */

void printListOfFiles(listOfFiles* list){
	while(list != NULL){
		printf("%s", list -> myFile -> myPrint);
		list = list -> next;
	}
}

/*
 * Copie a pointer from listOfFiles.
 */

void myListOfFilesPtrCpy(listOfFiles** dest, listOfFiles* ptrToCpy){
	*dest = ptrToCpy;
}

/*
 * Set the list pointer to the next file pointer.
 */

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

/*
 * Change the pointer reference to the file next to the next file, equivalent to delete pointer to the file in list: it won't be reacheable anymore 
 * when browsing the list.
 */

int supprNextFileOf(listOfFiles** list){
	listOfFiles* temp = malloc(sizeof(listOfFiles));
	temp = *list;
	if (temp->next == NULL){
		return 0;
	}else{
		//Next existe si le code ci dessous s'exécute
		temp -> next = temp -> next -> next;
	}
	return 1;
}



//========== Operational Functions ========== 

/*
 * Translate the mode_t value into printable string.
 */

char* fonction_permission(struct stat s)
{	
    char* string = malloc(12);
    
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

	/*
	char* localeT = setlocale(LC_TIME,NULL);
	if(strcmp(localeT,"C")==0){
		strcat(string,".");
	}
	*/ 
	//AS SEEN with Nicolas, no need to implement this format.

    return string;
}

/*
 * Set locale to the french format.
 */

char* dateFormater(time_t st_mdate)
{
	char* localeT = setlocale(LC_TIME,NULL);
	char *result;
	if(strcmp(localeT,"fr_FR.UTF-8")==0){
    	result = malloc(20);
    	strftime(result, 20, "%b  %d %H:%M", localtime(&st_mdate));
    }else{
    	result = malloc(20);
    	strftime(result, 20, "%b %d %H:%M", localtime(&st_mdate));
    }
    return result;
}


/*
 * Return pointer of string of the complete path of the file from concatenation of its name with the complete path of its owner.
 */

char* completePathBuilder(listOfFiles* list){
	char* pathToBuild = malloc(sizeof(char) * (strlen(list -> myFile -> myPath) + 1 + strlen(list -> myFile -> myName) +1) );
	strcpy(pathToBuild, list -> myFile -> myPath);
	slashItCorrectly(&pathToBuild);
	myStrCat(&pathToBuild, list-> myFile -> myName);

	return pathToBuild;

}

/*
 * Copy refence of a pointer into another.
 */

void myStrPtrCpy(char** dest, char* ptrToCpy){
	*dest = ptrToCpy;
}

/*
 * Homemade function equivalent to strcat.
 */

void myStrCat(char** dest, char*c){

	char* temp = malloc(sizeof(char) * ( strlen(*dest) + strlen(c) + 1 ) );
	strcpy(temp, *dest);
	strcat(temp, c);
	myStrPtrCpy(dest, temp);
}


/*
 * Return length of the given string.
 */

int myStrLen(char* strToSize){
	int taille=0;
	while (strToSize[taille]!='\0')
		taille++;
	return taille;
}


/*
 * Add slash to the non void path of the file if it doesn't have already.
 */

void slashItCorrectly(char** str){
	
	char c;
	int boolean =0, i=0;
	if(strlen(*str) > 0){
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

/*
 * Change bracket, if there is one, into path, else do nothing.
 */

int changeMyBrackets(char** tabOfString, char* thePath){
	int i = 0;
	int boolean= 0;
	while(tabOfString[i]!=NULL){
		
		if(strcmp(tabOfString[i],"{}")==0){
			boolean=1;
			tabOfString[i]=thePath;
		}
		
		i++;
	}
	return boolean;
}

char** splitMyString (char* givenStr) {
  
  char* myStr = malloc(sizeof(char)* (strlen(givenStr)+1) );
  strcpy(myStr, givenStr);
  
  const char s[2] = " ";
  char *TempoEltInMyStr;
   
   char** myStrSplitted = malloc(sizeof(char*)* (countItems(myStr) + 1) );
   int i = 0;

   TempoEltInMyStr = strtok(myStr, s);
   while( TempoEltInMyStr != NULL ) {
      myStrSplitted[i] = malloc(sizeof(char)* (strlen(TempoEltInMyStr)+1) );
      strcpy(myStrSplitted[i], TempoEltInMyStr);
      i++;
      TempoEltInMyStr = strtok(NULL, s);
   }
   
   myStrSplitted[i] = NULL;
   
   return myStrSplitted;
}


int countItems(char* myStr){
	int i =0, cnt = 1;

	while(myStr[i] != '\0'){
		if (myStr[i]==' '){	cnt++;}
		i++;
	}
	return cnt;
}
