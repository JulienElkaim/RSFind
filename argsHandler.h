#ifndef ARGSHANDLER_H
#define ARGSHANDLER_H

#include <getopt.h>

int errInArg(int argc, char** argv);
int optDispatcher(int argc, char**argv, int* lOpt, int* tOpt, char** tArg, int* iOpt, int* nOpt, char** nArg, int* eOpt, char** eArg, int* pOpt);


#endif