CC = gcc
FILES = *.c
FLAGS = -Wall -Werror -Wconversion -std=c99

clear:
	clear

lista: $(FILES)
	$(CC) $(FILES) $(FLAGS) -o abb

run: abb
	./lista

minipruebas: abb
		valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista minipruebas

zip:
	zip A2_TDA1.zip *.c *.h *.pdf *.md makefile

check: lista
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista
