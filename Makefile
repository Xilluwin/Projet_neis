CC=g++
CFLAGS=-Wall -std=c++11
LDFLAGS=-g -pthread
EXEC=Test
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)
    
%.o: %.cpp
	$(CC) -g -c $< $(CFLAGS)

$(EXEC): $(OBJ)
	
	$(CC) -o $@ $^ $(LDFLAGS)
	
	@echo "Programme OK"

.PHONY: clean mrproper

clean:
	rm -rf *.o

variable:
	@echo $(SRC)

mrproper: clean
	rm -rf $(EXEC)