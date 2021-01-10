
test: clean descripteurTexte.o tst_descripteurTexte.o
	gcc -o test descripteurTexte.o tst_descripteurTexte.o
	./test

tst_descripteurTexte.o: tst_descripteurTexte.c
	gcc -c -Wall tst_descripteurTexte.c

descripteurTexte.o: descripteurTexte.c descripteurTexte.h
	gcc -c -fstack-protector -Wall descripteurTexte.c

clean:
	rm -rf *.o test
