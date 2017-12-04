all:hw7

hw7: Main.o list.o struct.o term.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 Main.o list.o struct.o term.o -lgtest
else
	g++ -o hw7 Main.o list.o struct.o term.o -lgtest -lpthread
endif
	
Main.o: Main.cpp atom.h number.h struct.h utAtom.h variable.h utStruct.h utVariable.h list.h utList.h 
	g++ -std=gnu++0x -c Main.cpp

list.o:list.cpp list.h
		g++ -std=c++11 -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=c++11 -c struct.cpp
term.o:struct.cpp term.h
		g++ -std=c++11 -c term.cpp
	

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw7
endif