.PHONY = clean all
SOURCE = source
BIN = bin
INCLUDE = include
CC = g++
OBJ_NAME = main

COMPILE_FLAGS = -c -std=c++17 -Wall -Wextra -Werror -lSDL2 -lSDL2_image -lSDL2_ttf
LINKER_FLAGS =

all: $(OBJ_NAME)

$(BIN):
	mkdir -p $(BIN)

$(OBJ_NAME): $(BIN)/main.o $(BIN)/Environment.o $(BIN)/Functions.o $(BIN)/Object.o $(BIN)/Button.o $(BIN)/Text.o | $(BIN)
	$(CC) -o $(LINKER_FLAGS) $(OBJ_NAME) $(BIN)/main.o $(BIN)/Environment.o $(BIN)/Functions.o $(BIN)/Object.o $(BIN)/Button.o $(BIN)/Text.o

$(BIN)/main.o: $(SOURCE)/main.cpp |$(BIN)
	$(CC) $(COMPILE_FLAGS) -o $(BIN)/main.o $(SOURCE)/main.cpp -I$(INCLUDE)

$(BIN)/Environment.o: $(SOURCE)/Environment.cpp $(INCLUDE)/Environment.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) -o $(BIN)/main.o $(SOURCE)/Environment.cpp -I$(INCLUDE)

$(BIN)/Functions.o: $(SOURCE)/Functions.cpp $(INCLUDE)/Functions.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) -o $(BIN)/Functions.o $(SOURCE)/Functions.cpp -I$(INCLUDE)

$(BIN)/Object.o: $(SOURCE)/Object.cpp $(INCLUDE)/Object.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) -o $(BIN)/Object.o $(SOURCE)/Object.cpp -I$(INCLUDE)

$(BIN)/Button.o: $(SOURCE)/Button.cpp $(INCLUDE)/Button.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) -o $(BIN)/Button.o $(SOURCE)/Button.cpp -I$(INCLUDE)

$(BIN)/Text.o: $(SOURCE)/Text.cpp $(INCLUDE)/Text.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) -o $(BIN)/Text.o $(SOURCE)/Text.cpp -I$(INCLUDE)

clean:
	rm -rf $(BIN) $(OBJ_NAME)

