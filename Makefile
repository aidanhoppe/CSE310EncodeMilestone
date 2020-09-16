encode: milestone1.o
	g++ -g -Wall milestone1.o -o encode

milestone1.o: milestone1.cpp
	g++ -g -Wall -c milestone1.cpp
 
clean: 
	rm *.o encode *~
