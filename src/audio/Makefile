# Bastian : Permet de compiler le module audio gérant les piles de descripteur et les descripteurs audios affin de réaliser des tests unitaires sur la partie audio. (Les tests ne fonctionneront probablement plus car les chemins utilisées dans les fonctions sont définis pour fonctionner avec le main ex "./sauvegarde/Base_descripteur_audio" au lieu de  "../../sauvegarde/Base_descripteur_audio")
#PS : J'ai eu un problème de commande seulement dans ce makefile, lancer la commande descripteurAudio.o supprimait des fichiers et je n'ai pas réussi à trouver pourquoi. Du coup j'ai écris toutes les commandes dans le run pour permettre à Kosma et Moumouni de pouvoir faire des tests 
f= -Wall -Wextra -g

# Permet de relancer le test directement sans perdre de temps
run:
	gcc $f -c ./Descripteur_Audio/descripteurAudio.c
	gcc $f -c audio.c
	gcc $f -c ../Lien/lien/lien.c
	gcc $f -c ../Lien/liens.c
	gcc $f -c tst_audio.c
	gcc $f -o test lien.o liens.o descripteurAudio.o audio.o tst_audio.o
	./test

# Cette commande ne fonctionne pas attention !!!!
# ne fonctionne pas -> # descripteurAudio.o
test: audio.o tst_audio.o lien.o liens.o 
	gcc $f -c ./Descripteur_Audio/descripteurAudio.c
	gcc $f -o test lien.o liens.o descripteurAudio.o audio2.o tst_audio.o

# Compile le fichier de test
tst_audio.o:
	gcc $f -c tst_audio.c

# =================================================
#	Compilation de PileDescripteur et descripteurs
# =================================================

# Compile le fichier des descripteurs 
#ne fonctionne pas pour une raison inconnue ???
#descripteurAudio.o:
#	gcc $f -c ./Descripteur_Audio/descripteurAudio.c

# Compile le fichier Audio
audio2.o:
	gcc $f -c audio2.c

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
	rm -rf *.o test