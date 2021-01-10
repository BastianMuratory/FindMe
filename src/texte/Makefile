f= -Wall -Wextra -g

# Permet de relancer le test directement sans perdre de temps
run: clean test 
	./test

# Compile le programme mais ne l'execute pas 
test: descripteurTexte.o texte.o  tst_texte.o lien.o liens.o
	gcc $f -o test lien.o liens.o descripteurTexte.o texte.o tst_texte.o

# Compile le fichier de test
tst_texte.o:
	gcc $f -c tst_texte.c

# =================================================
#	Compilation de PileDescripteur et descripteurs
# =================================================

# Compile le fichier des descripteurs
descripteurTexte.o:
	gcc $f -c ./Descripteur_Texte/descripteurTexte.c

# Compile le fichier texte
texte.o:
	gcc $f -c texte.c

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
