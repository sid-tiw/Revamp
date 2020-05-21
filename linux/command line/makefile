objDeps = main.o operations.o arguments.o

revamp : $(objDeps)
		g++ -o revamp $(objDeps)
main.o : main.cpp arguments.o
		g++ -c main.cpp -std=c++17
operations.o : operations.cpp operations.h
			g++ -c operations.cpp -std=c++17
arguments.o : arguments.cpp arguments.h operations.o operations.h
			g++ -c arguments.cpp -std=c++17
clean : 
	rm revamp $(objDeps)