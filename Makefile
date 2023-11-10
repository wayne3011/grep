FLAGS = -Wall -Werror -Wextra
CC = gcc

all: s21_grep

s21_grep: main.o arguments_parser.o grep_output.o regulars.o
	$(CC) $(FLAGS) build/s21_grep.o build/arguments_parser.o build/grep_output.o build/regulars.o -o build/s21_grep
	rm -rf build/*.o

main.o: src/s21_grep.c
	$(CC) $(FLAGS) -c src/s21_grep.c -o build/s21_grep.o

arguments_parser.o: src/arguments_parser.c
	$(CC) $(FLAGS) -c src/arguments_parser.c -o build/arguments_parser.o

grep_output.o: src/grep_output.c
	$(CC) $(FLAGS) -c src/grep_output.c -o build/grep_output.o

regulars.o: src/regulars.c
	$(CC) $(FLAGS) -c src/regulars.c -o build/regulars.o

clean:
	rm -rf build/*.o build/s21_grep




