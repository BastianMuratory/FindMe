# Bastian : Permet de compiler le module Texte gérant les piles de descripteur et les descripteurs Texte affin de réaliser des tests unitaires sur la partie Texte. (Les tests ne fonctionneront probablement plus car les chemins utilisées dans les fonctions sont définis pour fonctionner avec le main ex "./sauvegarde/Base_descripteur_Texte" au lieu de  "../../sauvegarde/Base_descripteur_Texte")

f= -Wall -Wextra -g

# Permet de relancer le test directement sans perdre de temps
run: clean test 
	./test

# Compile le programme mais ne l'execute pas 
test: descripteurTexte.o texte.o  tst_texte.o lien.o liens.o
	gcc $f -o test lien.o liens.o descripteurTexte.o texte.o tst_texte.o

# Compile le fichier de test
tst_texte.o: tst_texte.c 
	gcc $f -c tst_texte.c

# =================================================
#	Compilation de PileDescripteur et descripteurs
# =================================================

# Compile le fichier des descripteurs
descripteurTexte.o: ./Descripteur_Texte/descripteurTexte.c ./Descripteur_Texte/descripteurTexte.h
	gcc $f -c ./Descripteur_Texte/descripteurTexte.c

# Compile le fichier texte
texte.o: texte.c texte.h
	gcc $f -c texte.c

# =================================================
#	Compilation de PileDescripteur et descripteurs
# =================================================

# Compilation des Liens et Piles de liens
lien.o: ../Lien/lien/lien.c ../Lien/lien/lien.h
	gcc $f -c ../Lien/lien/lien.c

#compilation pile de liens
liens.o: ../Lien/liens.c ../Lien/liens.h
	gcc $f -c ../Lien/liens.c

# =========
#	Clean
# =========
clean:
	rm -rf *o test temp*
