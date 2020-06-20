# OBJS files to be compiled as part of the engine.
OBJS = ./src/*.cpp

# Compiler
CC = clang++

# Compiler flags specifying additional compilation options
COMPILER_FLAGS = -std=c++20 \
								 -Wfatal-errors

# Linking flags specifying libraries being linked against
LINKER_FLAGS = -llua \
							 -lSDL2 \
							 -lSDL2_image \
							 -lSDL2_ttf \
							 -lSDL2_mixer

# Specifies the executable name
OBJ_NAME = itzicpp

build: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm ./$(OBJ_NAME)

run:
	./$(OBJ_NAME)
