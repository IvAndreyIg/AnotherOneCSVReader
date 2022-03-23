CC=g++
CFLAGS=-std=c++17 -c -Wall 
CXXFLAGS=-std=c++17 -Wall 

all:csvreader

csvreader: main.o Table.o TableParser.o
	$(CC) $(CXXFLAGS) main.o Table.o TableParser.o -o csvreader

main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp

Table.o: src/lib/Table.cpp
	$(CC) $(CFLAGS) src/lib/Table.cpp

TableParser.o: src/lib/TableParser.cpp
	$(CC) $(CFLAGS) src/lib/TableParser.cpp

clean:
	del -rf *.o csvreader