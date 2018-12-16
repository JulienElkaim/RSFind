#ifndef ARGSHANDLER_H
#define ARGSHANDLER_H

#include <getopt.h>

static struct option myLongOptions[] =
	{
		{"name", required_argument, 0, 'n'}, //optarg is the char* used to know the argument
		{"exec", required_argument, 0, 'e'},
		{"print", no_argument, 0, 'p'},
		{0,0,0,0}
	};

int errInArg(int argc, char** argv);
int optDispatcher(int argc, char**argv, int* lOpt, int* tOpt, char** tArg, int* iOpt, int* nOpt, char** nArg, int* eOpt, char** eArg, int* pOpt);



#endif