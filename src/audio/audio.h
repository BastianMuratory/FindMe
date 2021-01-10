#ifndef __F_Audio_H__
#define __F_Audio_H__

#include "./Descripteur_Audio/descripteurAudio.h"
#include "../Lien/liens.h"

typedef struct s_CelAudio{ // la cellule qui contient le descripteur Audio
	DescripteurAudio descripteur;
	struct s_CelAudio* suivant;
}CelluleAudio;

typedef struct s_pileDescripteurAudio{
	int taille;
	CelluleAudio* tete;
}PileDescripteurAudio;


/* Utilisation de la pile */
PileDescripteurAudio initPileDescripteurAudio();
PileDescripteurAudio empileDescripteurAudio(PileDescripteurAudio,DescripteurAudio);
PileDescripteurAudio depileDescripteurAudio(PileDescripteurAudio);

DescripteurAudio* getDescripteurAudio(PileDescripteurAudio,int);
DescripteurAudio* getDescripteurAudioViaId(PileDescripteurAudio,int);
DescripteurAudio* getDescripteurAudioViaNom(PileDescripteurAudio,char nom[50]);
void affichePileDescripteurAudio(PileDescripteurAudio);
void freePileDescripteurAudio(PileDescripteurAudio* p);

int toutDescripteurAudio(char* nomDuFichier,PileDescripteurAudio* p,PileLien* l,int nombreIntervalle,int ID);
/* Cette fonction crée le descripteur du fichier passé en parramètre 
Elle s'occupe de l'empiler dans la pile de descripteur 
Et de mettre à jour la pile de lien */

// se charge de la sauvegarde de la pile de descripteur et de la pile de liens
int SauvegardePileDescripteurAudio(PileDescripteurAudio p,PileLien l);

PileDescripteurAudio chargePileDescripteurAudio(int*);

#endif