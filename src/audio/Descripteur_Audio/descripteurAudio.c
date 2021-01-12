#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <conio.>

#include "descripteurAudio.h"

/*
typedef struct s_DescripteurAudio {
	int ID;
	char nom[50];
	int nombreDesIntervalles;
	int tailleDuDescripteur;
	int** histogramme;
} DescripteurAudio;
*/


///Fonction Taille fichier binaire
unsigned long tailleFichierBin(FILE *ficbin){
  

  fseek(ficbin,0,SEEK_END);
  
  unsigned long  taille= ftell(ficbin);
  
  return taille;

}






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
    //   ./data/TEST_SON/ --> pour compiler depuis le main

    //Creation d'un nouveau fichier binaire
    strcat(maCommande," > fbin");

    system(maCommande);
		//puts("B");
    FILE * ficbin = NULL ;

    //ficbin = fopen("nouveauFichierBinaire", "wb+"); //w+ lecture ecriture et création si fichier n'existe pas;
    

    ficbin = fopen("fbin","rb");
    if (ficbin == NULL){
    	printf("Erreur <-- ouverture du fichier .bin\n");
    	exit(EXIT_FAILURE);
    }

  //  int tabbin[10000] ;

	//d.tailleDuDescripteur = fread(tabbin, sizeof(int), 10000, ficbin);
    //puts("C");
    
	//Taille du fichier.bin
 
  
 // d.tailleDuDescripteur= tailleFichierBin(ficbin);
  
   //printf("taille = %d\n",d.tailleDuDescripteur );
		

  fclose(ficbin); 
  //puts("D");
 
	//puts("F");
	//lecture du fichier audio
	char chemin[80] = "../../../data/TEST_SON/";
	//system("")
	strcat(chemin,nomDuFichier);

	FILE* ficbin2 = fopen(chemin,"rb"); // 

 


  // Creation du d.histogramme
  unsigned long varTemp=0;
  float borneMax=0;
  float borneMin=0;
  float dist=1.2/(float)nombreDesIntervalles;
  //char c;

  puts("L'erreur arrive apres ce puts");

	


  float tabbin[1000000]; // bloc inconn

  int 	nb = fread(tabbin, sizeof(float),1000000, ficbin2);

		// la ligne precedente permet de lire le contenu accessible
		// depuis ficbin par bloc de 10000 int au max
		// et range cela dans le tableau tabbin
		// s'il y a moins de 10000 int ds le fichier, alors nb 
		// contiendra le nb d'int lus
     // Reservation de la memoire pour l'histogramme
     d.tailleDuDescripteur=nb;

  d.histogramme = (int**)malloc(d.tailleDuDescripteur*sizeof(int*));
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

	//	printf("nb = %d", nb);
  
		if (feof(ficbin))
			printf("\n arret : fin fichier\n") ;
		if (ferror(ficbin))
			printf("\n arret : erreur lecture\n") ;
		
		// affichage contenu du fichier binaire sous la forme d'int
  printf("\n");
	/*	for (int i = 0 ; i < d.tailleDuDescripteur ; i++) 
			printf("%d - ", tabbin[i]) ;ç
		*/

	
/*	printf("taille du desc %d, nombre des intervalles = %d\n",d.tailleDuDescripteur,d.nombreDesIntervalles);*/

  
  for(i=0; i<d.tailleDuDescripteur; i++){
    /* Recuperation de la valeur temporaire dans le ficier .bin
    fscanf(ficbin2, " %lf\n", &varTemp);*/

    //Il faut afficher impérativement le fichier

    varTemp = tabbin[i]; // ok
   //  printf("ok ok ok %lf\n",varTemp);





    //printf("i=%d",i);puts("");
    // fread() pour des fichiers .bin
    for(j=0; j<d.nombreDesIntervalles; j++){
      /* Calcule des bornes de l'intervalle j  */
      borneMin = -0.6+j*dist;
      borneMax = -0.6+(j+1)*dist;
      //printf("j=%d", j);puts("");
      /* On remplis l'histogramme avec : 1 si valeur est contenue dans l'intervalle et 0 sinon. Si la vleur est dehors la borne minimal totale et la borne maximal toale, on affiche une message d'erreur pour pouvoir l'augmenter l'intervalle. */
      
			/*
      if (varTemp<(-0.6) || varTemp>0.6){
				printf("\x1b[31m Erreur --> valeurs hors les bornes !!! \x1b[0m\n");
			}else */
			if (varTemp>borneMin && varTemp<=borneMax){
        d.histogramme[i][j]=1;
			//	puts("1");
        d.vectNombre[j]+=1;
        d.vectEndroit[i]+=j;
        
				//printf("%f est compris entre %f et %f\n",varTemp,borneMin,borneMax);
      }else {
				//printf("i=%d j=%d",i,j); // PROBLEME à i=42 j=0 
        d.histogramme[i][j]=0;
				//printf("%f n'est pas compris entre %f et %f\n",varTemp,borneMin,borneMax);
			}
		}
	}
  puts("L'erreur arrive apres ce puts\n");
	puts("I");

  // Affichage de la taille d'histogramme
 // printf("\nTaille du descripteur %s = %d par %d\n", d.nom, d.tailleDuDescripteur,d.nombreDesIntervalles);
  fclose(ficbin2);

	return d;
}






// Creation du descripteur
DescripteurAudio creerDescripteurAudio(char nomDuFichier[50],int nombreDesIntervalles, int id){
  // initialisation des variables locales
  int i,j;
	DescripteurAudio d;
	
	strcpy(d.nom,nomDuFichier); // mise a jour du nom
	d.ID = id; // mise a jour de l'id
  d.nombreDesIntervalles = nombreDesIntervalles;
	d.tailleDuDescripteur = 0;

  // creation de la commande pour ouvrir le fichier txt (depuis src/audio)
  char maCommande[80] = "wc -l ./data/TEST_SON/";
  // depuis src/audio/DescripteurAudio
	//char maCommande[80] = "wc -l ../../../data/TEST_SON/";
	strcat(maCommande,d.nom);
	// cette fonction ^ rajoute le char* d.nom à la fin du char* maCommande 
	strcat(maCommande," > Temp");
	/* Test maCommande */
  /*printf("Test maCommande : %s\n", maCommande);
  printf("maCommande bonne: wc -l ../../../data/TEST_SON/jingle_fi.txt > Temp\n");
  if (strcmp(maCommande,"wc -l ../../../data/TEST_SON/jingle_fi.txt > Temp")==0)
    printf("Test maCommande : OK\n");
  else
    printf("Test maCommande : NOK\n"); 
  */

  // puis tu peux lancer ta commande :
	system(maCommande);
	
	
	// Création du fichier temporaire
	FILE* fichier = fopen("Temp","r");
  if (fichier == NULL){
    printf("Erreur <-- ouverture du fichier .txt\n");
    exit(EXIT_FAILURE);
  }
  // Recuperation de la taille du fichier .txt
	int taille = 0;
	fscanf(fichier,"%d",&taille);
	//printf("Nombre de lignes dans le fichier %s = %d\n", d.nom, taille);
  // affectation de la taille du fichier 
  d.tailleDuDescripteur=taille;
  //fclose(fichier);
  
  // Reservation de la memoire pour l'histogramme
	d.histogramme = (int**)malloc(d.tailleDuDescripteur*sizeof(int*));
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
	char chemin[80] = "./data/TEST_SON/";

	strcat(chemin,nomDuFichier);
	fichier = NULL;
	fichier = fopen(chemin, "r");

	if(fichier == NULL){
		printf("Le fichier n'est pas touvé\n");	
	}
	// FILE* fichier2 = fopen(chemin,"r");
  
  // Creation du d.histogramme
  double varTemp=0;
  float borneMax=0;
  float borneMin=0;
  float dist=1.2/(float)nombreDesIntervalles;
  //char c;
  for(i=0; i<d.tailleDuDescripteur; i++){
    /* Recuperation de la valeur temporaire dans le ficier .txt */
    fscanf(fichier, " %lf\n", &varTemp);

    // fread() pour des fichiers .bin
    for(j=0; j<d.nombreDesIntervalles; j++){
      /* Calcule des bornes de l'intervalle j  */
      borneMin = -0.6+j*dist;
      borneMax = -0.6+(j+1)*dist;
      /* On remplis l'histogramme avec : 1 si valeur est contenue dans l'intervalle et 0 sinon. Si la vleur est dehors la borne minimal totale et la borne maximal toale, on affiche une message d'erreur pour pouvoir l'augmenter l'intervalle. */
      if (varTemp<(-0.6) || varTemp>0.6)
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
  // Affichage de la taille d'histogramme
  //printf("\nTaille du descripteur %s = %d par %d\n", d.nom, d.tailleDuDescripteur,d.nombreDesIntervalles);
  //fclose(fichier2);
  fclose(fichier);
  remove("Temp");
	return d;
}


//getters et setters
int getIdDescripteurAudio(DescripteurAudio d){
	return d.ID;
}
char* getNomDescripteurAudio(DescripteurAudio d){
  char* nom = malloc(50*sizeof(char));
	strcpy(nom,d.nom);
	return nom;
}

int setIdDescripteurAudio(DescripteurAudio* pointeur_d,int x){
	pointeur_d->ID = x;
	return 0;
}

/*
typedef struct s_DescripteurAudio {
	int ID; 
	char nom[50];
	int nombreDesIntervalles;	
	int tailleDuDescripteur; 
	int** histogramme; 
  int* vectNombre;
  int* vectEndroit;
} DescripteurAudio;
*/

//affectation
void affectDescripteurAudio(DescripteurAudio* e1,DescripteurAudio* e2){
  int i,j;
	// affectation de ID et du nom
  e2->ID = e1->ID;
  strcpy(e2->nom,e1->nom);

  // affectation du nombreDesIntervalles et de la tailleDuDescripteur
  e2->nombreDesIntervalles = e1->nombreDesIntervalles;
  e2->tailleDuDescripteur = e1->tailleDuDescripteur;
  
  /*
  // affectation de memoire pour l'histogramme
  e2->histogramme = (int**)malloc(e2->tailleDuDescripteur*sizeof(int*));
	for(i=0; i<e2->tailleDuDescripteur; i++){
		e2->histogramme[i] = (int*)malloc(e2->nombreDesIntervalles*sizeof(int));
	}
  */
	e2->vectEndroit = (int*)malloc(e2->tailleDuDescripteur*sizeof(int));
	e2->vectNombre = (int*)malloc(e2->nombreDesIntervalles*sizeof(int));
	

  for(i=0; i<e1->tailleDuDescripteur; i++){
    e2->vectEndroit[i] = e1->vectEndroit[i];
    /*for(j=0; j<e1->nombreDesIntervalles; j++){ 
      e2->histogramme[i][j] = e1->histogramme[i][j];
    }*/
  }
  for(j=0; j<e1->nombreDesIntervalles; j++){  
    e2->vectNombre[j] = e1->vectNombre[j];
  }
}

// fonction d'AFFICHAGE d'histogramme
void afficheHistogramme (DescripteurAudio d){
  int i,j;
  /* affichage du histogramme */
  if (d.histogramme!=NULL) {//<-- verification si non-null
    for(i=0; i<d.tailleDuDescripteur; i++){
      for(j=0; j<d.nombreDesIntervalles; j++){
        printf("--");
      }
      printf("\n|");
      for(j=0; j<d.nombreDesIntervalles; j++){if(d.histogramme[i][j]==1){
					printf("\x1b[31m%d",d.histogramme[i][j]);
					printf("\x1b[0m|");
				}else
					printf("%d|",d.histogramme[i][j]);
      }
      printf("\n|");  
    }
    for(j=0; j<d.nombreDesIntervalles; j++)
        printf("___");
  } 
  else 
    printf("L'histogramme du descripteur %s est vide.\n",d.nom);
}

// affichage de vectNombre
void afficheVectNombre (DescripteurAudio d){
  for (int i=0; i<d.nombreDesIntervalles; i++){
    printf(" %d", d.vectNombre[i]);
  }
}

// affichage de vectEndroit
void afficheVectEndroit (DescripteurAudio d){
  for (int i=0; i<d.tailleDuDescripteur; i++){
    printf(" %d", d.vectEndroit[i]);
  }
}

// fonction d'AFFICHAGE de Descripteur - nom, Id et taille
void afficheDescripteurAudio(DescripteurAudio d){
	printf("*** Audio = %s | ID = %d | taille = %d ***",d.nom,d.ID, d.tailleDuDescripteur);
}

// fonction d'affichage 2
void afftest(DescripteurAudio d){
	printf("[Audio = %s | ID = %d]\n",d.nom,d.ID);
	printf("[taille = %d par %d]\n",d.tailleDuDescripteur,d.nombreDesIntervalles);
	if(d.tailleDuDescripteur>10){
		for(int i=0;i<d.tailleDuDescripteur;i++){
			printf("[");
			for(int j=0;j<d.nombreDesIntervalles;j++){
				if(d.histogramme[i][j]==1){
					printf("\x1b[31m%d",d.histogramme[i][j]);
					printf("\x1b[0m");
				}else{
					printf("%d",d.histogramme[i][j]);
				}
				
				if(j<d.nombreDesIntervalles-1){
					printf(",");
				}else{
					printf("]\n");
				}
			}
		}
	}
}


float distanceDescripteurAudio(DescripteurAudio* d1, DescripteurAudio* d2, float* endroitLePlusPertinant){
  /* initialisation des variables locales */
  int i,j;
  int n=100; //n=1024, 2048, 4096 ou 8192 points
  int diffEndroit=0;
  int start;
  float endroitDistanceMin;
  /* on initialise distance et min a un nombre tres grand afin de pouvoir le diminuer avec des nombres minimaux trouvés lors de l'iteration de vectEndroit */
  float distance = 1000000000;
  float min = 1000000000;
  /* comparaison de nombre des intervalles de chaque descripteur */
  if (d1->nombreDesIntervalles!= d2->nombreDesIntervalles){
    printf("\n\n\n&&&&& Il faut mettre a jour l'indexation ! &&&&&\n\n\n");
    EXIT_FAILURE; 
  }
  
  start = 0;
  // d1 plus petit | d2 plus grand
  if  (d2->tailleDuDescripteur >= d1->tailleDuDescripteur){
    for(i=0; (i < d2->tailleDuDescripteur/n) && (start + d1->tailleDuDescripteur <= d2->tailleDuDescripteur) ; i++){
      /* on calcule le decalage du plus grand fichier */
      start=n*i;
      
      // affichage de start, distance, min apres chaque itteration
      //printf("%d : start = %d   distance = %d    min = %d\n",i,start, distance, min);
      /* on verifie si le distance est minimal */
      if (distance<min){
        min=distance;
        endroitDistanceMin=i-1;
      }
        
      diffEndroit=0;
      distance=0;        
      /* on entre dans la boucle pour comparer directement les vecteurs "vectEndroit" de 2 fichiers */
      for (j=0; j < d1->tailleDuDescripteur  ; j++){
        // on arrete l'iteration quand on depasse la taille du plus grand fichier 
        if ( (start+j) > d2->tailleDuDescripteur){
          diffEndroit += d1->tailleDuDescripteur-j;
          distance+=diffEndroit;
          break;
        }
        /* calcule de differance entre la frequance de d1 et la frequance de d2 */
        diffEndroit = d2->vectEndroit[start+j] - d1->vectEndroit[j];
        /* si la differance est negative, on change le sign */
        if (diffEndroit<0)
          diffEndroit = - diffEndroit;
        /* on ajoute la differance a la distance */
        distance+=diffEndroit;
      }
	  }
    /* on verifie si le distance est minimal apres le dernier parcours */
    if (distance<min){
      min=distance;
      endroitDistanceMin=i;
    }
    distance = min;
    distance = (distance / (d1->nombreDesIntervalles/2*d1->tailleDuDescripteur)) * 100; 
  }
  // d1 plus grand | d2 plus petit
  else {
    for(i=0; (i <= d1->tailleDuDescripteur/n) && (start+d2->tailleDuDescripteur < d1->tailleDuDescripteur); i++){
      start=n*i;
      
      //printf("%d : start = %d   distance = %d    min = %d\n",i,start, distance, min);
      if (distance<min){
        min=distance;
        endroitDistanceMin=i-1;
      }
      diffEndroit=0;
      distance=0;
      for (int j=0; j < d2->tailleDuDescripteur ; j++){
        if ( (start+j)>d1->tailleDuDescripteur){
          diffEndroit += 5*(d2->tailleDuDescripteur-j);
          distance+=diffEndroit;
          //printf("!!!!!!!! BREAK !!!!!!!!!!\n");
          break;
        }
        diffEndroit = d1->vectEndroit[start+j] - d2->vectEndroit[j];
        if (diffEndroit<0)
          diffEndroit = - diffEndroit;
        distance+=diffEndroit;
      }
	  }
    if (distance<min){
      min=distance;
      endroitDistanceMin=i;
    }
    //printf("distance apres le dernier parcours = %d\n", distance);
    distance = min;
    distance = (distance / (d2->nombreDesIntervalles/2*d2->tailleDuDescripteur)) * 100;
  }
  endroitDistanceMin = endroitDistanceMin * n/16384;
  /* recuperation de l'endroit ou la distance est min dans un poiteur passe en parametre */
  *endroitLePlusPertinant = endroitDistanceMin;
	return distance;
}

  
  
//sauvegardage du descripteur dans un fichier txt
int sauvegarderDescripteurAudio(FILE* fichier,DescripteurAudio d){
  int i;
  // sauvegardage d'identifiant, du nom, de la taille et du nombre des intervalles
	fprintf(fichier," %d %s %d %d\n",d.ID,d.nom, d.tailleDuDescripteur, d.nombreDesIntervalles);
  // sauvegardage du vectNombre
	for (i=0; i<d.nombreDesIntervalles; i++){
	  fprintf(fichier, " %d", d.vectNombre[i]);
	}
	fprintf(fichier,"\n");
  // sauvegardage du vectEndroit
	for (i=0; i<d.tailleDuDescripteur; i++){
	  fprintf(fichier, " %d", d.vectEndroit[i]);
	}
	fprintf(fichier,"\n");
	return 0;
}

// charge un descripteur depuis un fichier de sauvegarde
DescripteurAudio chargerDescripteurAudio(FILE* fichier){
	int i;
	DescripteurAudio d;
	
  // charchement d'identifiant, du nom, de la taille et du nombre des intervalles
	fscanf(fichier," %d %s %d %d\n",&d.ID,d.nom, &d.tailleDuDescripteur, &d.nombreDesIntervalles);
	//printf("\nid = %d \nnom = %s  \ntailleDuDescripteur= %d   \nnombreDesIntervalles = %d\n",d.ID,d.nom, d.tailleDuDescripteur, d.nombreDesIntervalles);

	  // Reservation de la memoire pour vectNombre
	d.vectNombre = (int*)malloc(d.nombreDesIntervalles*sizeof(int));
  // initialisation des toutes ses valeurs à 0
  /*for(i=0; i<d.nombreDesIntervalles; i++){
		d.vectNombre[i] = 0;
	}*/
  // Reservation de la memoire pour vectEndroit
	d.vectEndroit = (int*)malloc(d.tailleDuDescripteur*sizeof(int));
	// initialisation des toutes ses valeurs à 0
  /*for(i=0; i<d.tailleDuDescripteur; i++){
    d.vectEndroit[i] = 0;
	}*/
	
	
	// charchement du vectNombre
	for (i=0; i<d.nombreDesIntervalles; i++){
	  fscanf(fichier, " %d", &d.vectNombre[i]);
	  //printf("%d : %d", i, d.vectNombre[i]);
	}
	fscanf(fichier,"\n");
	// charchement du vectEndroit
	for (i=0; i<d.tailleDuDescripteur; i++){
	  fscanf(fichier, " %d", &d.vectEndroit[i]);
	}
	fscanf(fichier,"\n");
	
	return d;
}


/* foncionnement de vectEndroit et de vectNombre
 |11|12|13|
  0   1   0
  1   0   0
  1   0   0
  1   0   0

3 1 0 - vectNombre
12 11 11 11 - vectEndroit
*/




/* Questions :
1) Les histogrammes daivraient etre de la meme taille ou peut-ils etre de la taille variable?
2) Meme question pour l'intervalle...
3) Qui les definie? Comment? Un changement du code ou un droit d'administrateur?

dans le fichier de modifications...
meme nombre de collones (intervalles - 4 ou plus)
nombre de lignes varient selon largeur du fichier
1 ligne = 1 valeur 
--> on met 1 dans une de collones correspondante a l'intervale dans lequel se trouve la valeur


commentaire :
utiliser les fichiers textes !
double floatant : lf 

Exemple du descripteur avec 5 intervalles qui comprendent des valeurs de 0 jusqu'a 1 :

********************************************
| 0-0.2 |0.2-0.4 |0.4-0.6 |0.6-0.8 | 0.8-1 |
********************************************
---------------------------------------------
|   0   |    0   |    0   |    0   |    1   | <-- 0.863
---------------------------------------------
|   1   |    0   |    0   |    0   |    0   | <-- 0
---------------------------------------------
|   0   |    0   |    1   |    0   |    0   | <-- 0.404
---------------------------------------------
|   0   |    0   |    0   |    1   |    0   | <-- 0.789
---------------------------------------------
|   1   |    0   |    0   |    0   |    0   | <-- 0.137
---------------------------------------------
|   0   |    1   |    0   |    0   |    0   | <-- 0.273
---------------------------------------------

*/

/*
Questions pour le seance de 17 decembre :

1) Comment calculer la distance ?
- la differance entre des numeros Id = un nouveau numero identifiant qui contienne l'info sur le contenue ?
- directement depuis l'histogramme
- a l'aide des vecteurs vectNombre et  vectEndroit

2) Cas d'un morceau du fichier audio (premier 10 s d'un chansons complet) 
--> est-ce que le contenue (memes frequances) est plus important que la taille du fichier? 

3) Gestion d'affichage des fichiers (les plus) similaires
- a partir de comparaison d'numero Id (qui contienne l'info sur le contenue)
- dans la gestion de la pile --> le fichier le plus racemblant en tete... comparaison des descripteurs directement dans la pile (on compare un descripteurs avec ses voisins...)

4) Importance de la taille (ou du contenu) des fichiers, doit-t-elle etre gere par administrateur depuis le terminal ? 

On compare le distance pour N lignes lignes du fichier plus petit. Ensuite en decale le fichier plus grand (d'un demi second ou moins) et on le compare encore une fois (jusqu'a le fin du fichier plus grand). On recupere le distance minimal.

On stocke pas les valeurs de distance. On n'a pas besoin de la variable ID2 ou de comparer des fichiers avant l'utilisateur le demander.

*/



// calcul distance - la vielle fonction
/*
int distanceDescripteurAudio(DescripteurAudio* d1,DescripteurAudio* d2){
  // a faire 
  int i,j;
  int differenceTaille;
  int diffVectNombre = 0;
  int diffVectEndroit = 0;
  int distance = 0;
  
  if (d1->tailleDuDescripteur >= d2->tailleDuDescripteur){
    differenceTaille = d1->tailleDuDescripteur - d2->tailleDuDescripteur; 
  }
  else {
    differenceTaille = d2->tailleDuDescripteur - d1->tailleDuDescripteur;
  }
  // comparaison de vectNombre :
  if (d1->nombreDesIntervalles!= d2->nombreDesIntervalles){
    printf("\n\n\n&&&&& Il faut mettre a jour l'indexation ! &&&&&\n\n\n");
    EXIT_FAILURE;
  }
  int* vectDifferenceNombre = (int*)malloc(d1->nombreDesIntervalles*sizeof(int));
  int carre;
  for(i=0; i < d1->nombreDesIntervalles; i++){
		vectDifferenceNombre[i] = d1->vectNombre[i]-d2->vectNombre[i];
    // carre pour ne pas avoir les nombres negatives
    carre = vectDifferenceNombre[i]*vectDifferenceNombre[i];
    // conditions - impact sur le distance
    if (carre<2)
      diffVectNombre +=0;
    else if (carre<10)
      diffVectNombre +=1;
    else if(carre<100)
      diffVectNombre +=5;
    else if(carre<1000)
      diffVectNombre +=10;
    else if(carre<10000)
      diffVectNombre +=50;
    else if(carre<100000)
      diffVectNombre +=100;
    else if(carre<1000000)
      diffVectNombre +=500;
    else if(carre<10000000)
      diffVectNombre +=1000;
    else 
      diffVectNombre +=10000;
    // affichage de diffVectNombre pour chaque etape : 
    //printf("\n%d --> diffVectNombre = %d", i, diffVectNombre);
	}
  
  
  / *
  frequances --> l'histogramme, contienne-il les memes frequances (memes valeurs dans l'histogramme)?
  
  taille --> la taille de l'histogramme est la meme?
  
  il faut attribuer un poids d'importance a la taille, a  l'exactitude des frequances etc. 
  *//*

  distance = diffVectNombre - 0 * differenceTaille + 0.25 * diffVectEndroit ;
	return distance;
};
*/