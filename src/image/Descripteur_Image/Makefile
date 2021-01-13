# Bastian : Permet de compiler le module DescripteurImage affin de réaliser des tests unitaires. (Les tests ne fonctionneront probablement plus car les chemins utilisées dans les fonctions sont définis pour fonctionner avec le main ex "./sauvegarde/Base_descripteur_Image" au lieu de  "../../../sauvegarde/Base_descripteur_Image")

# compile et lance les tests unitaires des images
run: descripteurImage.o tst_descripteurImage.o
	gcc -o test.exe descripteurImage.o tst_descripteurImage.o
	./test.exe

# compilation du fichier de test 
tst_descripteurImage.o: tst_descripteurImage.c
	gcc -c tst_descripteurImage.c

# compilation des fonction liées aux descripteurs images
descripteurImage.o: descripteurImage.c descripteurImage.h
	gcc -c descripteurImage.c

clean:
	rm -rf *.o TEMP
