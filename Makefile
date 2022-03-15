CXXFLAGS = 

main.exe: main.o set_index_out_of_bound.o
	g++ main.o set_index_out_of_bound.o -o main.exe -std=c++0x

main.o: main.cpp
	g++ -c main.cpp -o main.o -std=c++0x

set_index_out_of_bound.o: set_index_out_of_bound.cpp
	g++ -c set_index_out_of_bound.cpp -o set_index_out_of_bound.o
.PHONY:
clean:
	rm *.exe *.o
