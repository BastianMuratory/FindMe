
test: clean lien.o tst_lien.o
	gcc -o test lien.o tst_lien.o
	./test

tst_lien.o:
	gcc -c tst_lien.c

lien.o:
	gcc -c lien.c

clean:
	rm -rf *.o test
