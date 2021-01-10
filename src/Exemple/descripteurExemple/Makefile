
test: clean dEx.o tst_dEx.o
	gcc -o test dEx.o tst_dEx.o
	./test

tst_dEx.o:
	gcc -c tst_dEx.c

dEx.o:
	gcc -c dEx.c

clean:
	rm -rf *.o test
