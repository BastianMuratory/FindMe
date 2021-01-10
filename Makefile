Objet = lien.o liens.o descripteurAudio.o audio.o descripteurTexte.o texte.o descripteurImage.o image.o main.o fonction.o pile_dossier.o chargement.o indexation.o

run: fonction.o chargement.o liens.o audio.o texte.o image.o Indexation.o
	gcc -c main.c 
	gcc -o main.exe $(Objet)
	./main.exe

#Fonctions utilisées par le Main seulement
fonction.o: src/FonctionMain/fonction.c src/FonctionMain/fonction.h
	gcc -c -Wall src/FonctionMain/fonction.c

#Fonction pour charger les fichiers config
chargement.o: pile_dossier.o src/chargement/chargement.c src/chargement/chargement.h
	gcc -c -Wall src/chargement/chargement.c

#utilisé par chargement.c pour avor une pile de char* (liste de nom de dossiers)
pile_dossier.o: src/chargement/Pile/pile_dossier.c src/chargement/Pile/pile_dossier.h
	gcc -c -Wall src/chargement/Pile/pile_dossier.c


# Fichiers texte
texte.o: descripteurTexte.o src/texte/texte.c  src/texte/texte.h
	gcc -c -Wall src/texte/texte.c

descripteurTexte.o: src/texte/Descripteur_Texte/descripteurTexte.c src/texte/Descripteur_Texte/descripteurTexte.h
	gcc -c -Wall src/texte/Descripteur_Texte/descripteurTexte.c

# Fichiers image
image.o: descripteurImage.o src/image/image.c  src/image/image.h
	gcc -c -Wall src/image/image.c

descripteurImage.o: src/image/Descripteur_Image/descripteurImage.c src/image/Descripteur_Image/descripteurImage.h
	gcc -c -Wall src/image/Descripteur_Image/descripteurImage.c

# Fichiers Audio
audio.o: descripteurAudio.o src/audio/audio.c  src/audio/audio.h
	gcc -c -Wall src/audio/audio.c

descripteurAudio.o: src/audio/Descripteur_Audio/descripteurAudio.c src/audio/Descripteur_Audio/descripteurAudio.h
	gcc -c -Wall src/audio/Descripteur_Audio/descripteurAudio.c

# Liens entre descripteur et nom 
liens.o: lien.o src/Lien/liens.c src/Lien/liens.h
	gcc -c -Wall src/Lien/liens.c

lien.o: src/Lien/lien/lien.c src/Lien/lien/lien.h
	gcc -c -Wall src/Lien/lien/lien.c 

# Indexation.c qui sert pour l'indexation et la recherche de fichiers
Indexation.o: src/Indexation/indexation.c src/Indexation/indexation.h
	gcc -c -Wall src/Indexation/indexation.c

clean:
	rm *.o