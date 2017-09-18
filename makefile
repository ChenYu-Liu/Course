INC_DIR = include



hw1: main.o Shapes.o Media.o
ifeq (${OS}, Windows_NT)
	g++ -o exp mainExp.o Shapes.o Media.o -lgtest
else
	g++ -o exp mainExp.o Shapes.o Media.o -lgtest -lpthread
endif
	
main.o: main.cpp utSort.h utSort.h Sort.h
	g++ -std=gnu++0x -c main.cpp
Shapes.o: $(INC_DIR)/Shapes.h Shapes.cpp
	g++ -std=gnu++0x -c Shapes.cpp
Media.o: $(INC_DIR)/Media.h Media.cpp
	g++ -std=gnu++0x -c Media.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif