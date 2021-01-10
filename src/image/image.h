#ifndef __F_Image_H__
#define __F_Image_H__

#include "./Descripteur_Image/descripteurImage.h"
#include "../Lien/liens.h"

//structure contenant le descripteur et pouvant être empilée
typedef struct s_CelImage{
	DescripteurImage descripteur; // le descripteur
	struct s_CelImage* suivant; // la cellule suivante pour la pile
}CelluleImage;

//Pile contenant les descripteurs image
typedef struct s_pileDescripteurImage{
	int taille; // taille de la pile (pad forcément nécessaire mais facilite certaines opérations)
	CelluleImage* tete; // tete de la pile
}PileDescripteurImage;


/* Utilisation de la pile */
// initialise une pile vide
PileDescripteurImage initPileDescripteurImage();
//empile le descripteur Image passé en paramètre
PileDescripteurImage empileDescripteurImage(PileDescripteurImage,DescripteurImage,int n_bits);
//depile le premier descripteur de la pile
PileDescripteurImage depileDescripteurImage(PileDescripteurImage);

// récupère le description à la position indexe dans la pile 
DescripteurImage* getDescripteurImage(PileDescripteurImage,int indexe);
// récupère le descripteur possédant l'id passé en parramètre 
DescripteurImage* getDescripteurImageViaId(PileDescripteurImage,int id);
// récupère le descripteur possédant le même nom que celui passé en parramètre
DescripteurImage* getDescripteurImageViaNom(PileDescripteurImage,char nom[50]);
// affiche une pile de descripteur image ( surtout utilisé pendant les tests)
void affichePileDescripteurImage(PileDescripteurImage);
// libère l'espace mémoire utilisé par la pile ... enfin je crois 
void freePileDescripteurImage(PileDescripteurImage* p);

// s'occupe de créer le descripteur du fichier passé en parramètre, de l'empiler sur la pile de descripteur et de créer son lien qui sera lui aussi empilé sur la pile de liens
int toutDescripteurImage(char* nomDuFichier,PileDescripteurImage* p,PileLien* l,int n_bits_quantification, int ID);

/* Sauvegarde la pile de descripteur et la pile de liens dans les fichiers :
 - base_descripteur_image
 - liste_base_image
*/
int SauvegardePileDescripteurImage(PileDescripteurImage p,PileLien l);
// charge une pile de descripteur depuis le fichier base_descripteur_image
PileDescripteurImage chargePileDescripteurImage(int n_bits,int* id);

#endif