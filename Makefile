test: ./lib/*.o
	g++ -o test test.cpp ./lib/*.o
    
libs: ./src/*.cpp
	g++ -c ./src/*.cpp
	mv ./*.o ./lib/
	
clean: 
	rm ./lib/*.o
	rm test
