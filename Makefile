program : src/pfspinstance.h src/flowshop.cpp src/pfspinstance.cpp

	g++ -O3 -c ./src/flowshop.cpp -o src/flowshop.o
	g++ -O3 -c ./src/pfspinstance.cpp -o src/pfspinstance.o
	g++ -O3 -c ./src/improvement.cpp -o src/improvement.o
	g++ -O3 -c ./src/permutations.cpp -o src/permutations.o
	g++ -O3 -c ./src/permutations/transpose.cpp -o src/permutations/transpose.o
	g++ -O3 -c ./src/permutations/exchange.cpp -o src/permutations/exchange.o
	g++ -O3 -c ./src/permutations/insert.cpp -o src/permutations/insert.o
	g++ -O3 -c ./src/utils.cpp -o src/utils.o
	g++ -O3 -c ./src/flowshopinstance.cpp -o src/flowshopinstance.o


	g++ -O3 src/flowshop.o src/pfspinstance.o src/improvement.o src/permutations.o src/permutations/transpose.o src/permutations/exchange.o src/permutations/insert.o src/flowshopinstance.o src/utils.o -o flowshopWCT

clean:
	rm src/*.o src/permutations/*.o flowshopWCT
