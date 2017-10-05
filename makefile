all:hw2

hw2: mainTerm.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o -lgtest
else
	g++ -o hw2 mainTerm.o -lgtest -lpthread
endif
	
main.o: mainTerm.cpp atom.h number.h prolog.h utTerm.h variable.h stdafx.cpp stdafx.h targetver.h
	g++ -std=gnu++0x -c main.cpp


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif