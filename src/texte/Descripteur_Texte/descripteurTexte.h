#ifndef __DescripteurTexte_h__
#define __DescripteurTexte_h__

#define TAILLE_MAX 100
#define TAILLE_MOT 50

typedef struct s_Cellule {
  char token[TAILLE_MOT+1];
  int nbOcc;
  struct s_Cellule* suiv;
} Cellule;

typedef struct s_ListeTermes {
  Cellule* tete;
  int taille;
} ListeTermes;

typedef struct s_DescripteurTexte{
	ListeTermes termes; // Liste des termes les plus significatifs
  int nbTermes; // Nombre total des termes retenus
  int nbTokenFic; // Taille du fichier en nombre de token
	int ID; // ID du descripteur
	char nom[TAILLE_MAX+1]; // nom du fichier decrit
}DescripteurTexte;

/* Libère l'espace mémoire d'un descripteur */
int freeDescripteurTexte(DescripteurTexte* d);

// Creation du descripteur
DescripteurTexte creerDescripteurTexte(char nomDuFichier[TAILLE_MAX+1],int nmbDeMots,int ID);
//getters et setters
int getIdDescripteurTexte(DescripteurTexte d);
char* getNomDescripteurTexte(DescripteurTexte d);
int setIdDescripteurTexte(DescripteurTexte* pointeur_d,int x);
//affectation et copie
void affectDescripteurTexte(DescripteurTexte* e,DescripteurTexte* x);
void afficheDescripteurTexte(DescripteurTexte d);
// calcul distance

int distanceDescripteurTexte(DescripteurTexte d1,DescripteurTexte d2);
int distanceDescripteurMotTexte(char* mot,DescripteurTexte d2);

// Chargement et sauvegarde du fichier descripteur
int sauvegarderDescripteurTexte(FILE* fichier,DescripteurTexte d);
DescripteurTexte chargerDescripteurTexte(FILE* fichier);

#endif
