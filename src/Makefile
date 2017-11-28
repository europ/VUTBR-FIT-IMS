# COMPILER
CC=g++

# FLAGS
CF=-Wall -Wextra -pedantic -std=c++11

# PROJECT
PROJECT=ims

# MODULES
A=modul

all: $(PROJECT)

$(A).o: $(A).cpp $(A).hpp
	$(CC) $(CF) -c $(A).cpp -o $(A).o

$(PROJECT).o: $(PROJECT).cpp $(A).hpp
	$(CC) $(CF) -c $(PROJECT).cpp -o $(PROJECT).o

$(PROJECT): $(A).o $(PROJECT).o
	$(CC) $(CF) $(A).o $(PROJECT).o -lsimlib -lm -o $(PROJECT)

clean:
	rm -f *.o

clean-all: clean
	rm -f $(PROJECT)
