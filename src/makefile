CC = g++
CFLAGS = -g -Wall -std=c++11 -pedantic
OBJECTS = main.o and.o command.o connector.o exit.o or.o semicolon.o testing.o

a.out: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS)

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

and.o: and.cpp
	$(CC) -std=c++11 -c and.cpp

command.o: command.cpp
	$(CC) -std=c++11 -c command.cpp

connector.o: connector.cpp
	$(CC) -std=c++11 -c connector.cpp

exit.o: exit.cpp
	$(CC) -std=c++11 -c exit.cpp

or.o: or.cpp
	$(CC) -std=c++11 -c or.cpp

semicolon.o: semicolon.cpp
	$(CC) -std=c++11 -c semicolon.cpp

testing.o: testing.cpp
	$(CC) -std=c++11 -c testing.cpp

clean:
	rm *.o a.out
