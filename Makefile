CXXFLAGS = -std=c++0x

main.exe: main.o 
	g++ $(CXXFLAGS) main.o -o main.exe

main.o: main.cpp graph.h
	g++ $(CXXFLAGS) -c main.cpp -o main.o

.PHONY: clean
clean:
	rm *.o *.exe
