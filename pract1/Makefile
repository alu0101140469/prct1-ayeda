CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
OBJS = main.o Tape.o Ant.o Simulator.o
DEPS = Tape.h Ant.h Simulator.h
TARGET = langton

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c main.cc

Tape.o: Tape.cc Tape.h
	$(CXX) $(CXXFLAGS) -c Tape.cc

Ant.o: Ant.cc Ant.h Tape.h
	$(CXX) $(CXXFLAGS) -c Ant.cc

Simulator.o: Simulator.cc Simulator.h Tape.h Ant.h
	$(CXX) $(CXXFLAGS) -c Simulator.cc

clean:
	rm -f $(OBJS) $(TARGET)
