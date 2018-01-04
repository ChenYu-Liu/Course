all:hw8 shell

hw8: Main.o list.o struct.o term.o
ifeq (${OS}, Windows_NT)
	g++ -o hw8 Main.o list.o struct.o term.o -lgtest
else
	g++ -o hw8 Main.o list.o struct.o term.o -lgtest -lpthread
endif
	
Main.o: Main.cpp term.h atom.h number.h struct.h variable.h list.h parser.h node.h scanner.h exp.h expression.h exception.h
	g++ -std=gnu++0x -c Main.cpp 
	
term.o:term.cpp term.h
	g++ -std=c++11 -c term.cpp
		
list.o:list.cpp list.h
	g++ -std=c++11 -c list.cpp
		
struct.o:struct.cpp struct.h
	g++ -std=c++11 -c struct.cpp

	

shell:Main_shell.o list.o struct.o term.o

ifeq (${OS}, Windows_NT)
	g++ -o shell Main_shell.o list.o struct.o term.o -lgtest
else
	g++ -o shell Main_shell.o list.o struct.o term.o -lgtest -lpthread
endif

Main_shell.o: Main_shell.cpp atom.h number.h struct.h variable.h utStruct.h utVariable.h list.h utList.h exp.h
	g++ -std=gnu++0x -c Main_shell.cpp

list.o:list.cpp list.h
	g++ -std=c++11 -c list.cpp
struct.o:struct.cpp struct.h
	g++ -std=c++11 -c struct.cpp
term.o:term.cpp term.h
	g++ -std=c++11 -c term.cpp
	

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw8 shell
endif