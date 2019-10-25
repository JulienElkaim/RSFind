CC=gcc
DEBUG= -Wall -Werror -Wextra
LIBMAGIC=-lmagic
EXEC=rsfind


rsfind: rsfind.o myFunctionalLib.o optionsToApply.o searcher.o argsHandler.o
	$(CC) -o rsfind rsfind.o myFunctionalLib.o optionsToApply.o searcher.o argsHandler.o $(LIBMAGIC)

rsfind.o: rsfind.c
	$(CC) $(DEBUG) -c rsfind.c

myFunctionalLib.o: myFunctionalLib.c myFunctionalLib.h
	$(CC) $(DEBUG) -c myFunctionalLib.c myFunctionalLib.h

optionsToApply.o: optionsToApply.c optionsToApply.h
	$(CC) $(DEBUG) -c optionsToApply.c optionsToApply.h

searcher.o: searcher.c searcher.h
	$(CC) $(DEBUG) -c searcher.c searcher.h

argsHandler.o: argsHandler.c argsHandler.h 
	$(CC) $(DEBUG) -c argsHandler.c argsHandler.h 

test: rsfind test.sh
	bash test.sh

clean:
	rm -rf *.o
	rm -rf *.gch

mrproper: clean
	rm -rf $(EXEC)
