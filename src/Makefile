# COMPILER
CC=g++

# FLAGS
CF=-Wall -Wextra -pedantic -std=c++11

# PROJECT
PROJECT=ims

# MODULES
A=data_types
B=file_data

all: $(PROJECT)

$(A).o: $(A).cpp $(A).hpp
	$(CC) $(CF) -c $(A).cpp -o $(A).o

$(B).o: $(B).cpp $(B).hpp
	$(CC) $(CF) -c $(B).cpp -o $(B).o

$(PROJECT).o: $(PROJECT).cpp $(A).hpp $(B).hpp
	$(CC) $(CF) -c $(PROJECT).cpp -o $(PROJECT).o

$(PROJECT): $(A).o $(B).o $(PROJECT).o
	$(CC) $(CF) $(A).o $(B).o $(PROJECT).o -lsimlib -lm -o $(PROJECT)

run:
	@./$(PROJECT)

clean:
	rm -f *.o

clean-all: clean
	rm -f $(PROJECT)
