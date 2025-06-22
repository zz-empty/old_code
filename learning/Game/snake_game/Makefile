CXX = g++
CXXFLAGS = -std=c++11 -Wall

snake: main.o snake.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp snake.h
	$(CXX) $(CXXFLAGS) -c main.cpp

snake.o: snake.cpp snake.h
	$(CXX) $(CXXFLAGS) -c snake.cpp

clean:
	rm -f *.o snake
