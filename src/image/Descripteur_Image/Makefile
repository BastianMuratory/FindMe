run: descripteurImage.o tst_descripteurImage.o
	gcc -o test.exe descripteurImage.o tst_descripteurImage.o
	./test.exe

tst_descripteurImage.o: tst_descripteurImage.c
	gcc -c tst_descripteurImage.c

descripteurImage.o: descripteurImage.c descripteurImage.h
	gcc -c descripteurImage.c

clean:
	rm -rf *.o
