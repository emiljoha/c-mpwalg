main:
	gcc mpw.c templates.c main.c -lsodium
	./a.out

shared-library:
	gcc -fPIC -shared -o mpw.so mpw.c templates.c -lsodium
