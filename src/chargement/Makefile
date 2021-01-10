run: test
	./test

test: pile_dossier.o chargement.o tst_charge.o
	gcc -o test pile_dossier.o chargement.o tst_charge.o

pile_dossier.o:
	gcc -c ./Pile/pile_dossier.c

chargement.o:
	gcc -c chargement.c

tst_charge.o:
	gcc -c tst_charge.c

clean:
	rm -rf *o test
