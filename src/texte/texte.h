#ifndef __F_Texte_H__
#define __F_Texte_H__

#include "./Descripteur_Texte/descripteurTexte.h"
#include "../Lien/liens.h"

typedef struct s_CelTexte{ // la cellule qui contient le descripteur Texte
	DescripteurTexte descripteur;
	struct s_CelTexte* suivant;
}CelluleTexte;

typedef struct s_pileDescripteurTexte{
	int taille;
	CelluleTexte* tete;
}PileDescripteurTexte;


/* Utilisation de la pile */
PileDescripteurTexte initPileDescripteurTexte();
PileDescripteurTexte empileDescripteurTexte(PileDescripteurTexte,DescripteurTexte);
PileDescripteurTexte depileDescripteurTexte(PileDescripteurTexte);

DescripteurTexte* getDescripteurTexte(PileDescripteurTexte,int);
DescripteurTexte* getDescripteurTexteViaId(PileDescripteurTexte,int);
DescripteurTexte* getDescripteurTexteViaNom(PileDescripteurTexte,char nom[50]);
void affichePileDescripteurTexte(PileDescripteurTexte);
void freePileDescripteurTexte(PileDescripteurTexte* p);

int SauvegardePileDescripteurTexte(PileDescripteurTexte p,PileLien l);
PileDescripteurTexte chargePileDescripteurTexte(int*id);


int toutDescripteurTexte(char* nomDuFichier,PileDescripteurTexte* p,PileLien* l,int nmbMots,int ID);
/* Cette fonction crée le descripteur du fichier passé en parramètre 
Elle s'occupe de l'empiler dans la pile de descripteur 
Et de mettre à jour la pile de lien */
#endif