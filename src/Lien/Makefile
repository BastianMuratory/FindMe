f= -Wall -Wextra -g

reset: clean test
	./test

test: lien.o liens.o  tst_liens.o
	gcc $f -o test lien.o liens.o tst_liens.o

lien.o:
	gcc $f -c ./lien/lien.c

liens.o:
	gcc $f -c liens.c

tst_liens.o:
	gcc -c tst_liens.c

clean:
	rm -rf *o test
