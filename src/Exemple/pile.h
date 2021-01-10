#ifndef __F_p_H__
#define __F_p_H__
// ^ à changer en focntion du nom de votre fichier

#include "./descripteurExemple/dEx.h"
#include "../Lien/liens.h"

typedef struct s_CelExemple{ // la cellule qui contient le descripteur Exemple
	DescripteurExemple descripteur;
	struct s_CelExemple* suivant;
}CelluleExemple;

typedef struct s_pileDescripteurExemple{
	int taille;
	CelluleExemple* tete;
}PileDescripteurExemple;


/* Utilisation de la pile */
PileDescripteurExemple initPileDescripteurExemple();
PileDescripteurExemple empileDescripteurExemple(PileDescripteurExemple,DescripteurExemple);
PileDescripteurExemple depileDescripteurExemple(PileDescripteurExemple);

DescripteurExemple* getDescripteurExemple(PileDescripteurExemple,int);
DescripteurExemple* getDescripteurExempleViaId(PileDescripteurExemple,int);
DescripteurExemple* getDescripteurExempleViaNom(PileDescripteurExemple,char nom[50]);
void affichePileDescripteurExemple(PileDescripteurExemple);
void freePileDescripteurExemple(PileDescripteurExemple* p);

int toutDescripteurExemple(char* nomDuFichier,PileDescripteurExemple* p,PileLien* l);
/* Cette fonction crée le descripteur du fichier passé en parramètre 
Elle s'occupe de l'empiler dans la pile de descripteur 
Et de mettre à jour la pile de lien */

#endif
