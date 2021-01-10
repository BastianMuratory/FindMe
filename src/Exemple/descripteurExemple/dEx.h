#ifndef __DescripteurExemple_h__
#define __DescripteurExemple_h__



typedef struct s_DescripteurExemple{
	int ID; // ID du descripteur
	char nom[50]; // nom du fichier decrit
}DescripteurExemple;

// Creation du descripteur
DescripteurExemple creerDecripteurDuExemple(char* nomDuFichier);
//getters et setters
int getIdDescripteurExemple(DescripteurExemple d);
char* getNomDescripteurExemple(DescripteurExemple d);
int setIdDescripteurExemple(DescripteurExemple* pointeur_d,int x);
//affectation et copie
void affectDescripteurExemple(DescripteurExemple* e,DescripteurExemple* x);
void afficheDescripteurExemple(DescripteurExemple d);
// calcul distance
int distanceDescripteurExemple(DescripteurExemple d1,DescripteurExemple d2); // retourne le pourcentage de différence entre deux fichiers (un int compris entre 0 et 100);

#endif
