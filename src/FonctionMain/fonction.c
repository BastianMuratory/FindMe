#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "fonction.h"

void clear (void){    // permet de vider le buffer après une saisie
  while ( getchar() != '\n' );
}

// Remet la couleur originelle du terminal 
void reset(){
	printf("\x1b[0m");
}

//  from 30 to 37
// black, red, green, yellow, blue, magenta, cyan and white.
void color(char* couleur){
	if(strcmp(couleur,"noir")==0){
		printf("\x1b[30m");
	}else if(strcmp(couleur,"rouge")==0){
		printf("\x1b[31m");
	}else if(strcmp(couleur,"vert")==0){
		printf("\x1b[32m");
	}else if(strcmp(couleur,"jaune")==0){
		printf("\x1b[33m");
	}else if(strcmp(couleur,"bleu")==0){
		printf("\x1b[34m");
	}else if(strcmp(couleur,"magenta")==0){
		printf("\x1b[35m");
	}else if(strcmp(couleur,"cyan")==0){
		printf("\x1b[36m");
	}else if(strcmp(couleur,"blanc")==0){
		printf("\x1b[37m");
	}else if(strcmp(couleur,"reset")==0){
		printf("\x1b[0m");
	}
}

void connection(bool* admin){ // gère la connection au mode administrateur
	char s[100];
	printf("Entrez le mdp 'Admin' pour vous connecter : ");
	scanf("%s",s);
	clear();
	if(strcmp( s, "Admin" ) == 0){
		printf("Vous avez maintenant accés aux fonctionnalitées Admin !\n");
		*admin = true;
	}else{
		color("rouge");
		printf("==============================\n");
		printf("||     Le MDP est erroné    ||\n");
		printf("|| Retour au menu principal ||\n");
		printf("==============================\n");
		color("reset");
	}
}


void affichage(bool admin,int *x,int vT,int vI,int vA,bool indT,bool indI,bool indA,int der_texte,int der_image,int der_audio){ // affiche le menu 
	*x = -1;
	color("vert");
	printf("\n===== FindMe =======\n");
	puts("[0] Quitter");
	puts("[1] Se connecter en admin");

	if(indT){
		puts("[2] Rechercher un mot");
		puts("[3] Rechercher un texte");
	}else{
		color("jaune");
		puts("[2] Indisponible, relancez l'indextaion des textes");
		puts("[3] Indisponible, relancez l'indextaion des textes");
		color("vert");
	}

	if(indI){
		puts("[4] Rechercher une image");
	}else{
		color("jaune");
		puts("[4] Indisponible, relancez l'indextaion des images");
		color("vert");
	}

	if(indA){
		puts("[5] Rechercher un fichier audio");
	}else{
		color("jaune");
		puts("[5] Indisponible, relancez l'indextaion des fichiers audio");
		color("vert");
	}

	if(admin){
		color("cyan");
		puts("--------------------");
		puts("[6] Changer les parramètres d'indexation Texte ");
		color("blanc");
		printf("(Paramètre courant : %d, dernière indexation : %d)\n",vT,der_texte);
		color("cyan");
		puts("[7] Changer les parramètres d'indexation image ");
		color("blanc");
		printf("(Paramètre courant : %d, dernière indexation : %d)\n",vI,der_image);
		color("cyan");
		puts("[8] Changer les parramètres d'indexation Audio ");
		color("blanc");
		printf("(Paramètre courant : %d, dernière indexation : %d)\n",vA,der_audio);
		color("cyan");
		puts("[9] Lancer l'indexation des Textes");
		puts("[10] Lancer l'indexation des Images");
		puts("[11] Lancer l'indexation des Sons");
		puts("[12] Quitter le mode administrateur");
		puts("--------------------");
	}
	puts("====================\n");
	color("reset");
	printf("Action à effectuer : ");
  scanf("%d",x);
	// 12 est la derniere et 5 est la derniere avant les commandes admin
  while( (*x<0) || (*x>12) || ( *x>5 && !admin) ) {
		clear();
		color("rouge");
		puts("=======================================");
		puts("||      La saisie est incorrecte     ||");
		puts("|| Merci de choisir un numéro valide ||");
		puts("=======================================");
		color("reset");
		
		printf("Action à effectuer : ");
		scanf("%d",x);
  }
	
}

void affichage2(bool admin,int *x,int vT,int vI,int vA,bool indT,bool indI,bool indA,int der_texte,int der_image,int der_audio,int ntexte,int nimage,int naudio){ // affiche le menu 
	*x = -1;
	color("vert");
	printf("\n===== FindMe =======\n");
	puts("[0] Quitter");
	puts("[1] Se connecter en admin");

	if(indT){
		puts("[2] Rechercher un mot");
		puts("[3] Rechercher un texte");
	}else{
		color("jaune");
		puts("[2] Indisponible, relancez l'indextaion des textes");
		puts("[3] Indisponible, relancez l'indextaion des textes");
		color("vert");
	}

	if(indI){
		puts("[4] Rechercher une image");
	}else{
		color("jaune");
		puts("[4] Indisponible, relancez l'indextaion des images");
		color("vert");
	}

	if(indA){
		puts("[5] Rechercher un fichier audio");
	}else{
		color("jaune");
		puts("[5] Indisponible, relancez l'indextaion des fichiers audio");
		color("vert");
	}

	if(admin){
		color("cyan");
		puts("--------------------");
		puts("[6] Changer les parramètres d'indexation Texte ");
		color("blanc");
		printf("(Paramètre courant : %d, dernière indexation : %d)\n",vT,der_texte);
		color("cyan");
		puts("[7] Changer les parramètres d'indexation image ");
		color("blanc");
		printf("(Paramètre courant : %d, dernière indexation : %d)\n",vI,der_image);
		color("cyan");
		puts("[8] Changer les parramètres d'indexation Audio ");
		color("blanc");
		printf("(Paramètre courant : %d, dernière indexation : %d)\n",vA,der_audio);
		color("cyan");
		puts("[9] Lancer l'indexation des Textes");
		puts("[10] Lancer l'indexation des Images");
		puts("[11] Lancer l'indexation des Sons");
		puts("--------------------");
		color("vert");
		printf("[12] Changer nombre de resultats textes = %d",ntexte);
		printf("[13] Changer nombre de resultats images = %d",nimage);
		printf("[14] Changer nombre de resultats audios = %d",naudio);
		puts("[15] Reccuperer affichage liste Texte");
		puts("[16] Reccuperer affichage liste Texte");
		puts("[17] Reccuperer affichage liste Texte");
		puts("[18] Quitter le mode administrateur");
		puts("--------------------");
	}
	puts("====================\n");
	color("reset");
	printf("Action à effectuer : ");
    scanf("%d",x);
	// 18 est la derniere et 5 est la premiere commande admin
  while( (*x<0) || (*x>18) || ( *x>5 && !admin) ) {
	color("rouge");
	printf("=======================================\n");
	printf("||      La saisie est incorrecte     ||\n");
	printf("|| Merci de choisir un numéro valide ||\n");
	printf("=======================================\n");
	color("reset");
	printf("Action à effectuer : ");
	scanf("%d",x);
  }
	clear();
}

void logo(){
	printf("\x1b[34m _____   _   __   _   _____   \x1b[31m    ___  ___   _____  \n");
	printf("\x1b[34m|  ___| | | |  \\ | | |  _  \\\x1b[31m     /   |/   | | ____| \n");
	printf("\x1b[34m| |__   | | |   \\| | | | | |\x1b[31m    / /|   /| | | |__   \n");
	printf("\x1b[34m|  __|  | | | |\\   | | | | | \x1b[31m  / / |__/ | | |  __|  \n");
	printf("\x1b[34m| |     | | | | \\  | | |_| | \x1b[31m / /       | | | |___  \n");
	printf("\x1b[34m|_|     |_| |_|  \\_| |_____/\x1b[31m /_/        |_| |_____| \n");
	color("reset");
}

void merci(){
	color("jaune");
	puts("\t\tÀ la prochaine !");
	printf("     ___  ___   _____   _____    _____   _       _ \n");
	printf("    /   |/   | | ____| |  _  \\  /  ___| | |     | |\n");
	printf("   / /|   /| | | |__   | |_| |  | |     | |     | |\n");
	printf("  / / |__/ | | |  __|  |  _  /  | |     | |     |_|\n");
	printf(" / /       | | | |___  | | \\ \\  | |___  | |      _ \n");
	printf("/_/        |_| |_____| |_|  \\_\\ \\_____| |_|     |_|\n");
	color("reset");
}

void erreur_relancer_indexation(){
	color("rouge");
	puts("===============================================================");
	puts("||           Le parammetre d'indexation à été changé         ||");
	puts("|| Veuillez relancer l'indexation du type de fichier choisit ||");
	puts("===============================================================");
	color("reset");
}

void message_erreur(){
	color("rouge");
	puts("=======================================");
	puts("||      La saisie est incorrecte     ||");
	puts("||     retour au menu principale     ||");
	puts("=======================================");
	color("reset");
}

void changer_param_text(int* param,bool* index){
	int min = 1;
	int max = 1000;
	int x = 0;
	puts("Le parammètre d'indexation de texte correspond au nombre de mots retenus dans un descripteur de texte.");
	printf("Veuillez entrer un nombre entre %d et %d : ",min,max);
	scanf("%d",&x);
	if(x<min || x>max){
		message_erreur();
	}else{
		*param = x;
		*index = false;
	}
}

void changer_param_image(int* param,bool* index){
	int min = 1;
	int max = 7;
	int x = 0;
	puts("Le parammètre d'indexation d'image correspond au nombre de bits pris en compte lors de la quantification."); 
	printf("Veuillez entrer un nombre entre %d et %d : ",min,max);
	scanf("%d",&x);
	if(x<min || x>max){
		message_erreur();
	}else{
		*param = x;
		*index = false;
	}
}

void changer_param_audio(int* param,bool* index){
	int min = 10;
	int max = 250;
	int x = 0;
	puts("Le parammètre d'indexation de fichier audio correspond au nombre d'intervales de l'echatillonnage.");
	printf("Veuillez entrer un nombre entre %d et %d : ",min,max);
	scanf("%d",&x);
	if(x<min || x>max){
		message_erreur();
	}else{
		*param = x;
		*index = false;
	}
}

void Indexation(){
	puts("");
}



