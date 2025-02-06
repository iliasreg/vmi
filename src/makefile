SRC_FILES = main.c vm.c file_lexer.c
FLAGS = -Wall -Wextra -g -std=c11
CC = clang
TARGET = vm

all:
	$(CC) $(SRC_FILES) $(FLAGS) -o $(TARGET)

clean:
	rm -rf vm