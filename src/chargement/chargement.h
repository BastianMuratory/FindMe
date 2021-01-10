#ifndef __F_CHARGEMENT_H__
#define __F_CHARGEMENT_H__

/*
#include "../image/image.h"
#include "../texte/texte.h"
#include "../audio/audio.h"
*/

#include "./Pile/pile_dossier.h"

//=============
// Partie test
//=============

//chargement et sauvegarde des parramètres d'indexation
int chargement_config(int* parramTexte,int* parramImage,int* parramAudio,bool* chercheTexte,bool* chercheImage,bool* chercheAudio);
void sauvegarde_config(int parramTexte,int parramImage,int parramAudio,bool chercheTexte,bool chercheImage,bool chercheAudio);

//récupération de tout les fichiers présents dans un dossier
Pile* get_files(char* folder);

void chargement_derniere_indexation(int* texte,int* image,int* audio,int* s_texte,int* s_image,int* s_audio);
void sauvegarde_derniere_indexation(int texte,int image,int audio,int s_texte,int s_image,int s_audio);


#endif