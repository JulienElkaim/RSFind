CC=gcc
CFLAGS= #-Wall -Werror -Wextra
COPTIONS=-lmagic
LDFLAGS=
EXEC=rsfind


rsfind:  setLang rsfind.o myFunctionalLib.o optionsToApply.o searcher.o argsHandler.o
	$(CC) -o rsfind rsfind.o myFunctionalLib.o optionsToApply.o searcher.o argsHandler.o $(COPTIONS)

setLang:
	export LANG=fr_FR.UTF-8
	
rsfind.o: rsfind.c
	$(CC) $(CFLAGS) -c rsfind.c

myFunctionalLib.o: myFunctionalLib.c myFunctionalLib.h
	$(CC) $(CFLAGS) -c myFunctionalLib.c myFunctionalLib.h

optionsToApply.o: optionsToApply.c optionsToApply.h
	$(CC) $(CFLAGS) -c optionsToApply.c optionsToApply.h

searcher.o: searcher.c searcher.h
	$(CC) $(CFLAGS) -c searcher.c searcher.h

argsHandler.o: argsHandler.c argsHandler.h 
	$(CC) $(CFLAGS) -c argsHandler.c argsHandler.h 

test: rsfind test.sh
	bash test.sh

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
