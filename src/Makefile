# COMPILER
CC=g++

# FLAGS
CF=-Wall -Wextra -pedantic -std=c++11 -g

# PROJECT
PROJECT=main

# MODULES
A=data_types
B=file_data

.PHONY: all
all: $(PROJECT)

$(A).o: $(A).cpp $(A).hpp
	$(CC) $(CF) -c $(A).cpp -o $(A).o

$(B).o: $(B).cpp $(B).hpp
	$(CC) $(CF) -c $(B).cpp -o $(B).o

$(PROJECT).o: $(PROJECT).cpp $(A).hpp $(B).hpp
	$(CC) $(CF) -c $(PROJECT).cpp -o $(PROJECT).o

$(PROJECT): $(A).o $(B).o $(PROJECT).o
	$(CC) $(CF) $(A).o $(B).o $(PROJECT).o -lsimlib -lm -o $(PROJECT)

.PHONY: run
run:
	@./$(PROJECT) experiment1
	@./$(PROJECT) experiment2
	@./$(PROJECT) experiment3
	
.PHONY: clean
clean:
	rm -f *.o

.PHONY: clean-all
clean-all: clean
	rm -f $(PROJECT)

.PHONY: test
test: clean-all all
	while true; do     			  \
		./$(PROJECT) experiment1; \
		./$(PROJECT) experiment2; \
		./$(PROJECT) experiment3; \
		echo "";       			  \
		sleep 1;       			  \
	done
