#ifndef __DescripteurImage_h__
#define __DescripteurImage_h__

/*
Structure utilisée dans les descripteurs d'image
*/
typedef struct s_Histo{
	bool couleur;// si l'histogramme représente une image en couleur ou pas
	int taille; // taille de l'histogramme 
	int* histo; // histogramme contenant le nombre d'apparition de la couleur représentée par son indice
	//[apparition_couleur_0,apparition_couleur_1,...]
}Histo;

// structure du descripteur image 
typedef struct s_DescripteurImage{
	int ID; // id du descripteur
	int nombre_bits; // nombre de bits utilisées pour la quatification
	char nom[50]; // nom du fichier décrit
	Histo histogramme; // histogramme
}DescripteurImage;

// Creation du descripteur à partir d'un nom de fichier, du nombre de bits de quantification (définis par l'administrateur) et de l'id qui lui est attribué
DescripteurImage creerDescripteurImage(char* nomDuFichier, int bit_quantification,int ID);
//quelques getters et setters
int getIdDescripteurImage(DescripteurImage d);
char* getNomDescripteurImage(DescripteurImage d);
int setIdDescripteurImage(DescripteurImage* pointeur_d,int x);

//affectation pour permettre l'empilement dans la pile 
void affectDescripteurImage(DescripteurImage* source,DescripteurImage* destination);

// Affichage du descripteur audio (utilisé le plus souvent lors des tests)
void afficheDescripteurImage(DescripteurImage d);

/*
calcul distance entre 2 descripteurs d'image
Dans le cas d'une image en noir et blanc, compte la différence entre chaques valeures des histogrammes 
Dans le cas d'un image en couleur, compte la même chose mais au carré ??

PS: Pour les image couleur je ne savais pas vraiment comment faire donc le logiciel compare surtout si les images ont les mêmes couleures et non les mêmes formes
En cherchant sur internet j'ai vu qu'il y avait plusieurs moyen de comparer des images en coulleur mais je n'ai pas eu le temps de les implémenter
*/
int distanceDescripteurImage(DescripteurImage d1,DescripteurImage d2);

// sauvegarde un descripteur dans un fichier
int sauvegarderDescripteurImage(FILE* fichier,DescripteurImage d);

// charge un descripteur depuis un fichier de sauvegarde
DescripteurImage chargerDescripteurImage(FILE* fichier);
void freeDescripteurImage(DescripteurImage* pointeur);


/*=============================
utilisé seulement pour les test
=============================*/

//Initialise un histogramme vide
Histo init_Histo(bool couleur,int nombre_bits);
// ajoute dans l'histogramme la bonne valeur correspondant aux 3 intensitées RGB en fonction du nombre de bits
Histo add_Image_Coul(Histo h,int R,int G,int B,int nombre_bit);
// ajoute dans l'histogramme la bonne valeur correspondant à l'intensitée en fonction du nombre de bits
Histo add_Image_NB(Histo h,int intensite,int nombre_bit);
// affichage de l'histogramme
void affiche_Histo(Histo h);

#endif
