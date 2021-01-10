#ifndef __DescripteurAudio_h__
#define __DescripteurAudio_h__

typedef struct s_DescripteurAudio {
	int ID; // ID du descripteur
	char nom[50]; // nom du fichier decrit
	int nombreDesIntervalles;	
	int tailleDuDescripteur; // variable contenant le nombre de ligne d'histogramme (=nombre de lignes du fichier)
	int** histogramme; // matrice contenant l'histogramme
  int* vectNombre; // vecteur contenant le nombre d'apparation de frequences (dans telle et telle intervalle)
  int* vectEndroit; // vecteur contenant l'endroit (le placement) des frequances
} DescripteurAudio;

// Creation du descripteur
DescripteurAudio creerDescripteurAudioBin(char nomDuFichier[50],int nombreDesIntervalles, int id);
DescripteurAudio creerDescripteurAudio(char* nomDuFichier, int nombreDesIntervalles, int id);

//Taille fichier binaiare
unsigned long tailleFichierBin(FILE *ficbin);



//getters et setters
int getIdDescripteurAudio(DescripteurAudio d);
char* getNomDescripteurAudio(DescripteurAudio d);
int setIdDescripteurAudio(DescripteurAudio* pointeur_d,int x);
//affectation et copie
void affectDescripteurAudio(DescripteurAudio* e,DescripteurAudio* x); // pas besoin ?
void afficheDescripteurAudio(DescripteurAudio d);
// calcul distance
float distanceDescripteurAudio(DescripteurAudio* d1,DescripteurAudio* d2, float*); // retourne le pourcentage de différence entre deux fichiers (un reel compris entre 0 et 100);

void afftest(DescripteurAudio d); // pas besoin ? fonction existe deja

int sauvegarderDescripteurAudio(FILE* fichier,DescripteurAudio d);
DescripteurAudio chargerDescripteurAudio(FILE* fichier);



#endif
