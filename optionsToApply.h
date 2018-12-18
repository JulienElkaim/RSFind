#ifndef OPTIONSTOAPPLY_H
#define OPTIONSTOAPPLY_H

#include "myFunctionalLib.h"

listOfFiles* applyNOption(listOfFiles* list, char* str);
listOfFiles* applyIOption(listOfFiles* list);
listOfFiles* applyLOption(listOfFiles* list);
void applyLOptionPrint(listOfFiles* list,int isPOpt);
void printerOfLOption(listOfFiles* list);
char* takeListReturnLPrint(listOfFiles* list);
void printerGeneral(listOfFiles* list, int pOpt, int lOpt, int eOpt);


#endif