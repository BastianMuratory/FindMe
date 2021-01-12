#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "src/FonctionMain/fonction.h"
#include "src/chargement/chargement.h"
#include "src/audio/audio.h"
#include "src/texte/texte.h"
#include "src/image/image.h"
#include "src/Indexation/indexation.h"

//#include "src/recherche/recherche.c"

int main(void) {
	system("clear"); // nettoyage du terminal

	//===========
	// Variables
	//===========

	bool admin = true; // mode administrateur ou pas 
	int x; // sert pour le choix de la commande à effectuer

	// valeur courante coisie pour l'indexation
	int vT = -1; 
	int vI = -1;
	int vA = -1;
	// valeur des parramètres lors de la dernière indexation éfectuée
	int derniere_ind_text = -1;
	int derniere_ind_image = -1;
	int derniere_ind_audio = -1;
	// valeur des parrametres lors de la dernière sauvegarde 
	int derniere_sauvegarde_texte = 1;
	int derniere_sauvegarde_image = 1;
	int derniere_sauvegarde_audio = 1;

	// Nombre de résultats à afficher suite à une recherche 
	int nombre_resultats_texte = 5;
	int nombre_resultats_image = 5;
	int nombre_resultats_audio = 2; //nombre des fichiers dans la base de données - 1


	// booleans permettant de savoir si l'utilisateur peut faire les recherches
	// ou doit attendre une nouvelle indexation
	bool peut_chercher_texte = true;
	bool peut_chercher_image = true;
	bool peut_chercher_audio = true;

	//Piles de liens et de descripteurs 
	PileDescripteurTexte pile_descripteur_texte;
	PileDescripteurImage pile_descripteur_image;
	PileDescripteurAudio pile_descripteur_audio;
	PileLien Liens_Texte,Liens_Audio,Liens_Image;
	int idImage,idTexte,idAudio;
	// bool pour savoir si les sauvegardes dovent être écrasées suite à une nouvelle indexation.
	bool modifTexte = false;
	bool modifImage = false;
	bool modifAudio = false;

	//====================================
	// Chargement des données sauvegardées
	//====================================

	chargement_config(&vT,&vI,&vA,&peut_chercher_texte,&peut_chercher_image,&peut_chercher_audio);
	
	chargement_derniere_indexation(&derniere_ind_text,&derniere_ind_image,&derniere_ind_audio,&derniere_sauvegarde_texte,&derniere_sauvegarde_image,&derniere_sauvegarde_audio);
	
  
  idAudio = 0;
	puts("Chargement des fichiers audio");
	pile_descripteur_audio = chargePileDescripteurAudio(&idAudio);
	Liens_Audio = chargePileLien("./sauvegarde/Descripteur_audio/Liste_base_audio");
  
	idImage = 0;
	puts("Chargement des fichiers image");
	pile_descripteur_image = chargePileDescripteurImage(&idImage);
	Liens_Image = chargePileLien("./sauvegarde/Descripteur_image/liste_base_image");

	idTexte = 0;
	puts("Chargement des fichiers texte");
	pile_descripteur_texte = chargePileDescripteurTexte(&idTexte);
	Liens_Texte = chargePileLien("./sauvegarde/Descripteur_texte/liste_base_texte");


	//7affichePileDescripteurImage(pile_descripteur_image);
	//affichePileLien(Liens_Image);

	//affichePileDescripteurAudio(pile_descripteur_audio);
	//affichePileLien(Liens_Audio);

	//affichePileDescripteurTexte(pile_descripteur_texte);
	//affichePileLien(Liens_Texte);


	//===================================
	// Lancement de la boucle Principale
	//===================================
	logo();

	do{
		
		affichage(admin,&x,vT,vI,vA,peut_chercher_texte,peut_chercher_image,peut_chercher_audio,derniere_ind_text,derniere_ind_image,derniere_ind_audio);
		system("clear");
		switch (x){
			case 0:
				system("clear");
				merci();
				break;
			case 1:
				if(!admin){
					connection(&admin);
				}else{
					printf("Vous êtes déjà administrateur.\n");
				}
				break;
			case 2:
				if(peut_chercher_texte){
					color("jaune");
					printf("Recherche de mot en cours ...\n");
					color("reset");
					rechercher_mots_texte(&pile_descripteur_texte,nombre_resultats_texte);
				}else{
					erreur_relancer_indexation();
				}
				break;
			case 3:
				if(peut_chercher_texte){
					color("jaune");
					printf("Recherche de mot en cours ...\n");
					color("reset");
					rechercher_texte(&pile_descripteur_texte,&Liens_Texte,derniere_ind_text,nombre_resultats_texte);
				}else{
					erreur_relancer_indexation();
				}
				break;
			case 4:
				if(peut_chercher_image){
					color("jaune");
					printf("Recherche d'image en cours ...\n");
					color("reset");
          rechercher_image(&pile_descripteur_image,&Liens_Image,derniere_ind_image,nombre_resultats_image);
				}else{
					erreur_relancer_indexation();
				}
				break;
			case 5:
				if(peut_chercher_audio){
					color("jaune");
          printf("Recherche audio en cours\n");
          color("reset");
          rechercher_audio(&pile_descripteur_audio,&Liens_Audio,derniere_ind_audio,nombre_resultats_audio);
          
				}else{
					erreur_relancer_indexation();
				}
				break;
			case 6:
				if(admin){
					changer_param_text(&vT,&peut_chercher_texte);
					if(vT == derniere_ind_text && !peut_chercher_texte){
						peut_chercher_texte = true;
					}
				}
				break;
			case 7:
				if(admin){
					changer_param_image(&vI,&peut_chercher_image);
					if(vI == derniere_ind_image && !peut_chercher_image){
						peut_chercher_image = true;
					}
				}
				break;
			case 8:
				if(admin){
					changer_param_audio(&vA,&peut_chercher_audio);
					if(vA == derniere_ind_audio && !peut_chercher_audio){
						peut_chercher_audio = true;
					}
				}
				break;
			case 9:
				if(admin){
					if(vT == derniere_ind_text){
						printf("Vous avez déjà indexé les fichiers avec le parramètre %d !\n",vT);
					}else{
						printf("Indexation Texte en cour\n");
						indexation_fichiers_textes(&pile_descripteur_texte, &Liens_Texte,vT, &idTexte);
						//affichePileDescripteurTexte(pile_descripteur_texte);
						derniere_ind_text = vT;
						peut_chercher_texte = true;
						modifTexte = true;
				 		printf("Indexation terminée\n");
					}
				}
				break;
			case 10:
				if(admin){
					if(vI == derniere_ind_image){
						printf("Vous avez déjà indexé les fichiers avec le parramètre %d !\n",vI);
					}else{
				  	printf("Indexation Image en cour\n");
						indexation_fichiers_images(&pile_descripteur_image, &Liens_Image ,vI, &	idImage);
						//affichePileDescripteurImage(pile_descripteur_image);
						derniere_ind_image = vI;
						peut_chercher_image = true;
						modifImage = true;
				 		printf("Indexation terminée\n");
					}
				}
				break;
			case 11:
				if(admin){
					if(vA == derniere_ind_audio){
						printf("Vous avez déjà indexé les fichiers avec le parramètre %d !\n",vA);
					}else{
				  	printf("Indexation Audio en cour\n");
						indexation_fichiers_audio(&pile_descripteur_audio, &Liens_Audio ,vA, &idAudio);
						derniere_ind_audio = vA;
						peut_chercher_audio = true;
						modifAudio = true;
				 		printf("Indexation terminée\n");
					}
				}
				break;
			case 12:
				admin = false;
				puts("Vous n'avez plus accés aux fonctionnalitées Admin");
				break;
  		default:
      printf("============================================\n");
			printf("||            Action impossible           ||\n");
			printf("||        Problème : choix invalide       ||\n");
			printf("============================================\n");
		}
		color("reset");
	} while (x);



	sauvegarde_config(vT,vI,vA,peut_chercher_texte,peut_chercher_image,peut_chercher_audio);
	if(modifTexte && (derniere_sauvegarde_texte != derniere_ind_text)){
		puts("\nSauvegarde des Descripteurs texte");
		SauvegardePileDescripteurTexte(pile_descripteur_texte, Liens_Texte);
		derniere_sauvegarde_texte = derniere_ind_text;
	}
	if(modifImage && (derniere_sauvegarde_image != derniere_ind_image)){
		puts("\nSauvegarde des Descripteurs image");
		SauvegardePileDescripteurImage(pile_descripteur_image, Liens_Image);
		derniere_sauvegarde_image = derniere_ind_image;
	}
	if(modifAudio && (derniere_sauvegarde_audio != derniere_ind_audio)){
		puts("\nSauvegarde des Descripteurs audio");
		SauvegardePileDescripteurAudio(pile_descripteur_audio, Liens_Audio);
		derniere_sauvegarde_audio = derniere_ind_audio;
	}
	
	sauvegarde_derniere_indexation(derniere_ind_text,derniere_ind_image,derniere_ind_audio,derniere_sauvegarde_texte,derniere_sauvegarde_image,derniere_sauvegarde_audio);
  return 0;
}