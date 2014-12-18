CPP=g++
CPPFLAGS = -std=c++0x -g
LIBS=-lemon
DEPS = ReliabilityGraph.hpp ReliabilityComputation.hpp
OBJ = ReliabilityGraph.o ReliabilityComputation.o


%.o: %.cpp $(DEPS)
	$(CPP) $(CPPFLAGS) -c -o $@ $<

main: main.cpp $(OBJ)
	$(CPP) -o $@ $^ $(CPPFLAGS) $(LIBS)



ReliabilityComputation.o: ReliabilityGraph.o $(DEPS)
	$(CPP) $(CPPFLAGS) -c -o $@ ReliabilityComputation.cpp
	



