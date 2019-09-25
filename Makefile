.PHONY = clean all debug release
SOURCE = source
BIN = bin
INCLUDE = include
CC = g++
OBJ_NAME = main

RELEASE_FLAGS = -DNDEBUG -O3
DEBUG_FLAGS = -g -Wshadow
COMPILE_FLAGS = -c -std=c++17 -Wextra -Werror
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

ifeq ($(BUILD), debug)
COMPILE_FLAGS += $(DEBUG_FLAGS)
endif

ifeq ($(BUILD), release)
COMPILE_FLAGS += $(RELEASE_FLAGS)
endif

all: $(OBJ_NAME)

debug:
	make "BUILD=debug"

release:
	mak "BUILD=release"

$(BIN):
	mkdir -p $(BIN)

$(OBJ_NAME): $(BIN)/main.o $(BIN)/Environment.o $(BIN)/Functions.o $(BIN)/Object.o $(BIN)/Button.o $(BIN)/Text.o | $(BIN)
	$(CC) -o $(OBJ_NAME) $(BIN)/main.o $(BIN)/Environment.o $(BIN)/Functions.o $(BIN)/Object.o $(BIN)/Button.o $(BIN)/Text.o $(LINKER_FLAGS)

$(BIN)/main.o: $(SOURCE)/main.cpp |$(BIN)
	$(CC) $(COMPILE_FLAGS) $(LINKER_FLAGS) -o $(BIN)/main.o $(SOURCE)/main.cpp -I$(INCLUDE)

$(BIN)/Environment.o: $(SOURCE)/Environment.cpp $(INCLUDE)/Environment.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) $(LINKER_FLAGS) -o $(BIN)/Environment.o $(SOURCE)/Environment.cpp -I$(INCLUDE)

$(BIN)/Functions.o: $(SOURCE)/Functions.cpp $(INCLUDE)/Functions.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) $(LINKER_FLAGS) -o $(BIN)/Functions.o $(SOURCE)/Functions.cpp -I$(INCLUDE)

$(BIN)/Object.o: $(SOURCE)/Object.cpp $(INCLUDE)/Object.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) $(LINKER_FLAGS) -o $(BIN)/Object.o $(SOURCE)/Object.cpp -I$(INCLUDE)

$(BIN)/Button.o: $(SOURCE)/Button.cpp $(INCLUDE)/Button.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) $(LINKER_FLAGS) -o $(BIN)/Button.o $(SOURCE)/Button.cpp -I$(INCLUDE)

$(BIN)/Text.o: $(SOURCE)/Text.cpp $(INCLUDE)/Text.h | $(BIN)
	$(CC) $(COMPILE_FLAGS) $(LINKER_FLAGS) -o $(BIN)/Text.o $(SOURCE)/Text.cpp -I$(INCLUDE)

clean:
	rm -rf $(BIN) $(OBJ_NAME)

