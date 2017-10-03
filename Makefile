all: sequential_index concurrent_index sieve

sequential_index: Main.o Index.o
	g++ -std=c++11 Main.o Index.o -o sequential_index -lpthread

concurrent_index: Conc.o Index.o
	g++ -std=c++11 Conc.o Index.o -o concurrent_index -lpthread

sieve: Sieve.o Index.o
	g++ -std=c++11 Sieve.o Index.o -o sieve -lpthread

Index.o: Index.hpp Index.cpp

Main.o: Main.cpp Index.hpp

Conc.o: Conc.cpp Index.hpp

Sieve.o: Sieve.cpp Index.hpp

%.o: %.cpp
	g++ -std=c++11 -c $< -lpthread

clean:
	rm -rf sequential_index concurrent_index sieve *.o

.PHONY: all clean
