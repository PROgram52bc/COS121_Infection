CC = g++
OBJ = Human.o Board.o conio.o Hunter.o Healer.o
CXXFLAGS = -g -Wall

infection: $(OBJ) main.cpp
	$(CC) $(CXXFLAGS) -o infection $(OBJ) main.cpp

Healer.o: Healer.cpp Healer.h Human.o Board.o conio.o
	$(CC) $(CXXFLAGS) -o Healer.o -c Healer.cpp 

Hunter.o: Hunter.cpp Hunter.h Human.o Board.o conio.o
	$(CC) $(CXXFLAGS) -o Hunter.o -c Hunter.cpp 

Human.o: Human.h Human.cpp conio.o
	$(CC) $(CXXFLAGS) -o Human.o -c Human.cpp 

Board.o: Board.h Board.cpp conio.o
	$(CC) $(CXXFLAGS) -o Board.o -c Board.cpp

conio.o: conio.cpp conio.h
	$(CC) $(CXXFLAGS) -o conio.o -c conio.cpp

clean:
	rm -f *.o infection 
