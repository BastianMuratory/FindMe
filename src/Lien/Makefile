# Bastian fichier permettant de compiler et executer les tests unitaires des piles de liens 

f= -Wall -Wextra -g

# compilation + execution
run: test
	./test

# compilation du fichier de test
test: lien.o liens.o  tst_liens.o
	gcc $f -o test lien.o liens.o tst_liens.o

# compilation du fichier de lien
lien.o: ./lien/lien.c ./lien/lien.h
	gcc $f -c ./lien/lien.c

# compilation du fichier de liens
liens.o: liens.c liens.h
	gcc $f -c liens.c

# compilation du fichier de test
tst_liens.o: tst_liens.c
	gcc -c tst_liens.c

clean:
	rm -rf *o test Temp
