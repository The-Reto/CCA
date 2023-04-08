all: libs Test_RNG.run
    
libs: ./src/*.cpp
	g++ -c ./src/*.cpp
	mv ./*.o ./lib/
	
Test_RNG.run: libs
	g++ -o Test_RNG.run Test_RNG.cpp ./lib/*.o
	
Test_Speed.run: libs
	g++ -o Test_Speed.run Test_Speed.cpp ./lib/*.o
	
clean: 
	rm ./lib/*.o
	rm test.run
