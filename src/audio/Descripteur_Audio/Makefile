
test: clean descripteurAudio.o tst_descripteurAudio.o
	gcc -o test descripteurAudio.o tst_descripteurAudio.o
	./test

tst_descripteurAudio.o: tst_descripteurAudio.c
	gcc -c tst_descripteurAudio.c

descripteurAudio.o: descripteurAudio.c descripteurAudio.h
	gcc -c descripteurAudio.c

clean:
	rm -rf *.o test


test2: