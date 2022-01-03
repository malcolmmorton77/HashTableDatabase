#Author: Malcolm Morton, Troy Davenport \
Professor:  Utpal Kumar-Dey \
Date:	      11/06/2020 \
Description:facilitates all the high level input and calls to other files \

all: program clean run

program: main.o employee.o department.o project.o
	g++ -o program *.o

main.o: main.cpp employee.h department.h project.h 
	g++ -c $*.cpp

employee.o: employee.h employee.cpp
	g++ -c $*.cpp

department.o: department.h department.cpp
	g++ -c $*.cpp

project.o: project.h project.cpp
	g++ -c $*.cpp

run:
	./program

clean:
	rm -f *.o
