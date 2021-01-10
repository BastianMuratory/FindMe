#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define max 100000

//#include "descripteurAudio.h"






int main(){

  typedef struct s_DescripteurAudio {
	int ID;
	char nom[50];
	int nombreDesIntervalles;
	int tailleDuDescripteur;
	int** histogramme;
} DescripteurAudio;




// Creation du descripteur
DescripteurAudio creerDescripteurAudioBin(char nomDuFichier[50],int nombreDesIntervalles, int id){
  // initialisation des variables locales
    int i,j;
    DescripteurAudio d;
	
	  strcpy(d.nom,nomDuFichier); // mise a jour du nom
	  d.ID = id; // mise a jour de l'id
    d.nombreDesIntervalles = nombreDesIntervalles;
  	d.tailleDuDescripteur = 0;

    char maCommande[80] = "wc -l ../../../data/TEST_SON/";
	  strcat(maCommande,d.nom);

    //Creation d'un nouveau fichier binaire
    strcat(maCommande," > ");

    int commande = system(maCommande);

    FILE * ficbin = NULL ;
    //ficbin = fopen("nouveauFichierBinaire", "wb+"); //w+ lecture ecriture et création si fichier n'existe pas;
  

    FILE* ficbin = fopen("fbin","rb");
    if (fichier == NULL){
    printf("Erreur <-- ouverture du fichier .bin\n");
    exit(EXIT_FAILURE);
    }

    
	//Taille du fichier.bin

    fseek(fichier,0,SEEK_END);
   long  taille= ftell(fichier);
   d.tailleDuDescripteur = taille;
		

 fclose(ficbin); 

/*
  
  // Reservation de la memoire pour l'histogramme
	d.histogramme = (int**)malloc(d.nombreDesIntervalles*sizeof(int));

	for(i=0; i<d.tailleDuDescripteur; i++){
		d.histogramme[i] = (int*)malloc(d.nombreDesIntervalles*sizeof(int));
	}

  // Reservation de la memoire pour vectNombre
	d.vectNombre = (int*)malloc(d.nombreDesIntervalles*sizeof(int));
  // initialisation des toutes ses valeurs à 0
  for(i=0; i<d.nombreDesIntervalles; i++){
		d.vectNombre[i] = 0;
	}
  // Reservation de la memoire pour vectEndroit
	d.vectEndroit = (int*)malloc(d.tailleDuDescripteur*sizeof(int));
	// initialisation des toutes ses valeurs à 0
  for(i=0; i<d.tailleDuDescripteur; i++){
    d.vectEndroit[i] = 0;
	}

	//lecture du fichier audio
	char chemin[80] = "../../../data/TEST_SON/";
	//system("")
	strcat(chemin,nomDuFichier);
	FILE* fichier2 = fopen(chemin,"r");




  // Creation du d.histogramme
  double varTemp=0;
  float borneMax=0;
  float borneMin=0;
  float dist=1.2/(float)nombreDesIntervalles;
  char c;
  for(i=0; i<d.tailleDuDescripteur; i++){
    /* Recuperation de la valeur temporaire dans le ficier .txt */
    /*fscanf(fichier2, " %lf\n", &varTemp);
    // fread() pour des fichiers .bin
    for(j=0; j<d.nombreDesIntervalles; j++){
      /* Calcule des bornes de l'intervalle j  */
   /*   borneMin = -0.6+j*dist;
      borneMax = -0.6+(j+1)*dist;
      /* On remplis l'histogramme avec : 1 si valeur est contenue dans l'intervalle et 0 sinon. Si la vleur est dehors la borne minimal totale et la borne maximal toale, on affiche une message d'erreur pour pouvoir l'augmenter l'intervalle. */
   /*   if (varTemp<(-0.6) || varTemp>0.6)
        printf("\x1b[31m Erreur --> valeurs hors les bornes !!! \x1b[0m\n");
      else if (varTemp>borneMin && varTemp<=borneMax){
        d.histogramme[i][j]=1;
        d.vectNombre[j]+=1;
        d.vectEndroit[i]+=j;
				//printf("%f est compris entre %f et %f\n",varTemp,borneMin,borneMax);
      }else {
        d.histogramme[i][j]=0;
				//printf("%f n'est pas compris entre %f et %f\n",varTemp,borneMin,borneMax);
			}
		}
	}

  */

  // Affichage de la taille d'histogramme
  
  printf("\nTaille du descripteur %s = %d par %d\n", d.nom, d.tailleDuDescripteur,d.nombreDesIntervalles);
  fclose(fichier2);
	return d;
}





}


