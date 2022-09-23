TARGET=a.out
CXX=g++
DEBUG=-g
OPT=-O2
WARN=-Wall
SFML=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS=$(DEBUG) ${INCLUDE} $(OPT) $(WARN) $(SFML) 
LD=g++
OBJS=main.o flappy.o

all: $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAGS)
	@rm *.o
	@./$(TARGET)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o

flappy.o: flappy.cpp
	$(CXX) -c $(CXXFLAGS) flappy.cpp -o flappy.o