#ifndef __Idexation_H__
#define __Idexation_H__

#include "../image/image.h"
#include "../audio/audio.h"
#include "../texte/texte.h"

#include "../Lien/liens.h"

typedef struct s_resultat {


}Resultat;

//int toutDescripteurImage(char* nomDuFichier,PileDescripteurImage* p,PileLien* l,int bitFort, int ID){
int indexation_fichiers_images(PileDescripteurImage* p,PileLien* l,int nmb_bits,int* ID);
int rechercher_image(PileDescripteurImage* p,PileLien* l,int nBits,int n_resultats);

// fonctions pour les fichiers audio :
int indexation_fichiers_audio(PileDescripteurAudio* p,PileLien* l,int nombreDesIntervales,int* ID);
int rechercher_audio(PileDescripteurAudio* p,PileLien* l,int nombreDesIntervales,int n_resultats);

// fonctions pour les fichiers texte :
int indexation_fichiers_textes(PileDescripteurTexte* p,PileLien* l,int nmb_mots,int* ID);
int rechercher_texte(PileDescripteurTexte* p,PileLien* l,int n_mots,int n_resultats);
int rechercher_mots_texte(PileDescripteurTexte* p,int n_resultats);
#endif