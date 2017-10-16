all:hw3

hw3: Main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 Main.o -lgtest
else
	g++ -o hw3 Main.o -lgtest -lpthread
endif
	
Main.o: Main.cpp atom.h number.h struct.h utAtom.h variable.h utStruct.h utVariable.h
	g++ -std=gnu++0x -c Main.cpp


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif