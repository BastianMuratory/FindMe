f= -Wall -Wextra -g

run: test clean
	./test

test: indexation.o tst_indexation.o image.o liens.o audio.o texte.o
	gcc $f -o test liens.o lien.o image.o descripteurImage.o texte.o descripteurTexte.o audio.o descripteurAudio.o indexation.o tst_indexation.o

# fichiers du dossier 
indexation.o: indexation.c indexation.h
	gcc $f -c indexation.c

tst_indexation.o: tst_indexation.c
	gcc $f -c tst_indexation.c


#Liens
liens.o: lien.o ../Lien/liens.c ../Lien/liens.h
	gcc $f -c ../Lien/liens.c

lien.o: ../Lien/lien/lien.c ../Lien/lien/lien.h
	gcc $f -c ../Lien/lien/lien.c


#image
image.o: descripteurImage.o ../image/image.c ../image/image.h
	gcc $f -c ../image/image.c

descripteurImage.o: ../image/Descripteur_Image/descripteurImage.c ../image/Descripteur_Image/descripteurImage.h
	gcc $f -c ../image/Descripteur_Image/descripteurImage.c


#audio
audio.o: descripteurAudio.o ../audio/audio.c ../audio/audio.h
	gcc $f -c ../audio/audio.c


descripteurAudio.o: ../audio/Descripteur_Audio/descripteurAudio.c ../audio/Descripteur_Audio/descripteurAudio.h
	gcc $f -c ../audio/Descripteur_Audio/descripteurAudio.c

#texte
texte.o: descripteurTexte.o ../texte/texte.c ../texte/texte.h
	gcc $f -c ../texte/texte.c


descripteurTexte.o: ../texte/Descripteur_Texte/descripteurTexte.c ../texte/Descripteur_Texte/descripteurTexte.h
	gcc $f -c ../texte/Descripteur_Texte/descripteurTexte.c


#texte
clean:
	rm -rf *o
