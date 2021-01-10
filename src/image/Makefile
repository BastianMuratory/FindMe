f= -Wall -Wextra -g

# Permet de relancer le test directement sans perdre de temps
run: test 
	./test

# Compile le programme mais ne l'execute pas 
test: descripteurImage.o image.o  tst_image.o lien.o liens.o
	gcc $f -o test lien.o liens.o descripteurImage.o image.o tst_image.o

# Compile le fichier de test
tst_image.o: tst_image.c
	gcc $f -c tst_image.c

# =================================================
#	Compilation de PileDescripteur et descripteurs
# =================================================

# Compile le fichier des descripteurs
descripteurImage.o: ./Descripteur_Image/descripteurImage.c ./Descripteur_Image/descripteurImage.h
	gcc $f -c ./Descripteur_Image/descripteurImage.c

# Compile le fichier image
image.o: image.c image.h
	gcc $f -c image.c

# =================================================
#	Compilation des liens
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
	rm -rf *o test
