all:
	gcc mpw.c templates.c main.c -lsodium
	./a.out
