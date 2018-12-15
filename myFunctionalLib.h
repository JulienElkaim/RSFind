#ifndef MYFUNCTIONALLIB_H
#define MYFUNCTIONALLIB_H

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

struct _MyFile{
	char* myPrint;
	char* myName;
	char* myPath;
	mode_t* myPerms;
	nlink_t* myLinks;
	uid_t* myUsrId;
	gid_t* myGrpId;
	off_t* mySizeFile;
	time_t* myLastMod;
}; typedef struct _MyFile MyFile;

struct _myDirAndFileList{
	MyFile* myFile;
	struct _myDirAndFileList* next;
}; typedef struct _myDirAndFileList listOfFiles;


MyFile* create_File(char* name, char* path, mode_t* perms, nlink_t* links, uid_t* usrID, gid_t* grpID, off_t* sizeFile, time_t* lastMod);
listOfFiles* insertFile(MyFile* newFile, listOfFiles* list);
void printListOfFiles (listOfFiles* list);
void myListOfFilesPtrCpy(listOfFiles** dest, listOfFiles* ptrToCpy);
int nextFile(listOfFiles** list);
int supprNextFileOf(listOfFiles** list);

char* completePathBuilder(listOfFiles* list);
void myStrPtrCpy(char** dest, char* ptrToCpy);
void myStrCat(char** dest, char* c);
void slashItCorrectly(char** str);

#endif