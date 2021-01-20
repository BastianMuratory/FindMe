# Bastian : Permet de compiler et lancer le fichier de test unitaire lié aux fonctions des liens. Les liens sont la structure qui relie un descripteur et son id 

# compilation et lancement des tests unitaires
run: lien.o tst_lien.o
	gcc -o test lien.o tst_lien.o
	./test

# compilation du fichier de test
tst_lien.o:
	gcc -c tst_lien.c

#compilation des fonctions liées aux liens 
lien.o: lien.c lien.h
	gcc -c lien.c

clean:
	rm -rf *.o test
