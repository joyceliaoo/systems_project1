all: main.o shell.o
	gcc -o shell  main.o shell.o

main.o: main.c shell.h
	gcc -c -g main.c

shell.o: shell.c shell.h
	gcc -c -g shell.c

run: 
	./shell

clean:
	rm *.o
	rm ./shell
