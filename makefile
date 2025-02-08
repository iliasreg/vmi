SRC_FILES = src/main.c vm/vm.c readers/file_lexer.c
FLAGS = -Wall -Wextra -g -std=c11
CC = clang
TARGET = vmi

all:
	$(CC) $(SRC_FILES) $(FLAGS) -o $(TARGET)

clean:
	rm -rf vm