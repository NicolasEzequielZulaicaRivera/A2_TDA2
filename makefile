CC = gcc
FILES = *.c
FLAGS = -Wall -Werror -Wconversion -std=c99

clear:
	clear

abb: $(FILES)
	$(CC) $(FILES) $(FLAGS) -o abb

run: abb
	./abb

minipruebas: abb
		valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb minipruebas

zip:
	zip A2_TDA1.zip *.c *.h *.pdf *.md makefile

check: abb
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb
