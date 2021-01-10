f= -Wall -Wextra -g

# Permet de relancer le test directement sans perdre de temps
reset: clean test 
	./test

# Compile le programme mais ne l'execute pas 
test: dEx.o pile.o  tst_pile.o lien.o liens.o
	gcc $f -o test lien.o liens.o dEx.o pile.o tst_pile.o

# Compile le fichier de test
tst_pile.o:
	gcc $f -c tst_pile.c

# =================================================
#	Compilation de PileDescripteur et descripteurs
# =================================================

# Compile le fichier des descripteurs
dEx.o:
	gcc $f -c ./descripteurExemple/dEx.c

# Compile le fichier Pile de descripteur
pile.o:
	gcc $f -c pile.c

# =================================================
#	Compilation de PileDescripteur et descripteurs
# =================================================

# Compilation des Liens et Piles de liens
lien.o:
	gcc $f -c ../Lien/lien/lien.c

#compilation pile de liens
liens.o:
	gcc $f -c ../Lien/liens.c

# =========
#	Clean
# =========

clean:
	rm -rf *o test
