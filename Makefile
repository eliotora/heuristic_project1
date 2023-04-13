program : src/pfspinstance.h src/flowshop.cpp src/pfspinstance.cpp

	g++ -O3 -c ./src/flowshop.cpp -o src/flowshop.o
	g++ -O3 -c ./src/pfspinstance.cpp -o src/pfspinstance.o
	g++ -O3 -c ./src/utils.cpp -o src/utils.o
	g++ -O3 -c ./src/flowshopinstance.cpp -o src/flowshopinstance.o


	g++ -O3 src/flowshop.o src/pfspinstance.o src/flowshopinstance.o src/utils.o -o pfspwt

clean:
	rm src/*.o pfspwt
