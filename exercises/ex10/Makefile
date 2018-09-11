ex10: ex10.o Vector.o
	g++ -Wall -g -std=c++11 -o ex10 ex10.o Vector.o

ex10.o: ex10.cc Vector.h
	g++ -Wall -g -std=c++11 -c ex10.cc

Vector.o: Vector.cc Vector.h
	g++ -Wall -g -std=c++11 -c Vector.cc

clean:
	rm -rf ex10 *# *.o *~
