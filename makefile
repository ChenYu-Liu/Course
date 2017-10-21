all:hw4

hw4: Main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 Main.o -lgtest
else
	g++ -o hw4 Main.o -lgtest -lpthread
endif
	
Main.o: Main.cpp atom.h number.h struct.h utAtom.h variable.h utStruct.h utVariable.h list.h utList.h
	g++ -std=gnu++0x -c Main.cpp


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif