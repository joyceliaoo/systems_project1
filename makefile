all: main.o shell.o test.o
	gcc -o shell  main.o shell.o test.o

main.o: main.c shell.h
	gcc -c -g main.c

shell.o: shell.c shell.h
	gcc -c -g shell.c

test.o: test.c test.h
	gcc -c -g test.c

run: 
	./shell

clean:
	rm *.o
	rm ./shell
