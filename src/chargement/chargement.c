#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./chargement.h"

/*
Nombre de mots dans un descripteur texte :10,0
Bit de poid fort dans une image :10,0
Nombre de fenêtres d'écoute dans un descripteur audio :10,0
*/

int chargement_config(int* parramTexte,int* parramImage,int* parramAudio,
bool* chercheTexte,bool* chercheImage,bool* chercheAudio){
	FILE* fichier = NULL;
	fichier = fopen("./sauvegarde/configuration.config","r");
	int param = 0,indexation = 0;
	if(fichier!=NULL){
		//puts("chargement réussi\n");
		//fichiers textes
		fscanf(fichier,"Nombre de mots dans un descripteur texte :%d,%d\n",&param,&indexation);
		* parramTexte = param;
		if(indexation == 0){
			* chercheTexte = true;
		}else{
			* chercheTexte = false;
		}
		// fichiers Images
		fscanf(fichier,"Bit de poid fort dans une image :%d,%d\n",&param,&indexation);
		* parramImage = param;
		if(indexation == 0){
			* chercheImage = true;
		}else{
			* chercheImage = false;
		}

		// fichiers audio
		fscanf(fichier,"Nombre de fenêtres d'écoute dans un descripteur audio :%d,%d\n",&param,&indexation);
		* parramAudio = param;
		if(indexation == 0){
			* chercheAudio = true;
		}else{
			* chercheAudio = false;
		}
		fclose(fichier);
	}else{
		puts("\nattention problème, parramètres défauts chargés\n");
		* parramTexte = 10;
		* parramImage = 10;
		* parramAudio = 10;
		* chercheTexte = true;
		* chercheImage = true;
		* chercheAudio = true;
	}
	
	return 0;
}


void sauvegarde_config(int parramTexte,int parramImage,int parramAudio,
bool chercheTexte,bool chercheImage,bool chercheAudio){
	FILE* fichier = NULL;
	//fichiers textes
	fichier = fopen("./sauvegarde/configuration.config","w");
	fprintf(fichier,"Nombre de mots dans un descripteur texte :%d,",parramTexte);
	if(chercheTexte){
		fprintf(fichier,"0\n");
	}else{
		fprintf(fichier,"1\n");
	}
	//fichiers images
	fprintf(fichier,"Bit de poid fort dans une image :%d,",parramImage);
	if(chercheImage){
		fprintf(fichier,"0\n");
	}else{
		fprintf(fichier,"1\n");
	}

	fprintf(fichier,"Nombre de fenêtres d'écoute dans un descripteur audio :%d,",parramAudio);
	if(chercheAudio){
		fprintf(fichier,"0\n");
	}else{
		fprintf(fichier,"1\n");
	}
	fclose(fichier);
	//puts("sauvegarde terminée");
}


void chargement_derniere_indexation(int* texte,int* image,int* audio,int* s_texte,int* s_image,int* s_audio){
	FILE* fichier = NULL;
	//fichiers textes
	fichier = fopen("./sauvegarde/save.save","r");
	if(fichier == NULL){
		puts("ERREUR chargement dernières valeures");
	}else{
		fscanf(fichier,"texte:%d,%d\n",texte,s_texte);
		fscanf(fichier,"image:%d,%d\n",image,s_image);
		fscanf(fichier,"audio:%d,%d\n",audio,s_audio);
	}
	fclose(fichier);
}

void sauvegarde_derniere_indexation(int texte,int image,int audio,int s_texte,int s_image,int s_audio){
	FILE* fichier = NULL;
	fichier = fopen("./sauvegarde/save.save","w");
	if(fichier != NULL){
		fprintf(fichier,"texte:%d,%d\n",texte,s_texte);
		fprintf(fichier,"image:%d,%d\n",image,s_image);
		fprintf(fichier,"audio:%d,%d\n",audio,s_audio);
		fclose(fichier);
	}
}


/**
*Cette fonction permet de récupérer une liste de dossier se trouvant dans un fichier passé en parramètre
*/
Pile* get_files(char* folder){ /* de base défini dans ./home*/
	Pile* p = new_Pile();
	printf("Récupération des fichiers dans :%s\n",folder);
	char commande[100] = "ls ../../" ;
	strcat(commande,folder);
	strcat(commande," > temp");
	
	
	//int status = system("ls ../../data/texte > temp");
	int status = system(commande);
	if(status != 0){
		printf("=========================\nLe dossier spécifié n'éxiste pas ou n'est pas accessible\nVous aurez une Pile vide\nErreur:%d\n=========================\n",status);
		return p;
	}else{
		status = system("wc -l temp > temp2");

		// Récupération du nombre de fichiers
		FILE* lignes = fopen("temp2","r");
		int nmb_fichiers;
		fscanf(lignes,"%d temp\n",&nmb_fichiers);
		fclose(lignes);
		// Operation terminée

		// Récupération des différents fichiers
		FILE* fichier = fopen("temp","r");
		fscanf(fichier,"temp/n"); // on enlève les restes de la commande ls

		for(int i = 0;i<nmb_fichiers;i++){
			char* buffer = (char*)malloc(100*sizeof(char)); // pas très optimal :(
			fscanf(fichier,"%s\n",buffer);
			empile(p,buffer);
		}

		fclose(fichier);
		status = system("rm temp temp2");
		return p;
	}
}
