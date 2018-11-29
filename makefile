all: main.o shell.o test.o text_parse.o
	gcc -o shell  main.o shell.o test.o text_parse.o

main.o: main.c shell.h
	gcc -c -g main.c

shell.o: shell.c shell.h
	gcc -c -g shell.c

test.o: test.c test.h
	gcc -c -g test.c

text_parse.o: text_parse.c text_parse.h
	gcc -c -g text_parse.c

run:
	./shell

clean:
	rm *.o
	rm ./shell
