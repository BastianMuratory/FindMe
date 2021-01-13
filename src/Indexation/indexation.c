#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "indexation.h"


// fonction permettant de changer la couleur du terminal
void couleur(char* couleur){
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

// Fonction d'affichage de l'eereur dans le cas le nom de fichier entré par l'utilisateur est incorrecte
void error(){
	couleur("rouge");
	puts("======================================================");
	puts("||          Le fichier cherché n'éxiste pas         ||");
	puts("|| Vérifiez son nom ou rajoutez le dans le dossier :||");
	puts("||                Fichier_Recherche                 ||");
	puts("======================================================");
	couleur("reset");
}

int indexation_fichiers_images(PileDescripteurImage* p,PileLien* l,int nmb_bits,int* ID){
  int pourcentage = 0; // affichage de la barre de chargement 
	// vider la pile si elle est deja remplie
	if(p->taille > 0){
		freePileDescripteurImage(p);
		//puts("La pile de descripteur à été free");
	}
	// vider la pile de liens si deja remplie 
	if(l->taille > 0){
		freePileLien(l);
		//puts("La pile de liens à été free");
	}

	// récupération du nom des fichiers à indexer 
	system("ls ./data/TEST_NB | grep '.txt' > temp");
	system("ls ./data/TEST_RGB | grep '.txt' >> temp");
	system("wc -l temp > temp2");
	int max = 0;

	// récupération du nombre de fichiers à indexer
	FILE* fichier = NULL;
	fichier = fopen("temp2","r");
	fscanf(fichier,"%d",&max);
	fclose(fichier);
	/*
	printf("============================\n");
	printf("Il y a %d fichiers à indexer\n",max);
	printf("============================\n");
	*/

	// indexation de chacun de ces fichiers
	char fichierCourant[50];
	couleur("jaune");
	fichier = fopen("temp","r");
	for(int i = 0;i<max;i++){
		fscanf(fichier,"%s",fichierCourant);
		toutDescripteurImage(fichierCourant,p,l,nmb_bits,i);
    pourcentage = ((i+1)*100)/max;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	couleur("vert");
  printProgressBar(100);
  couleur("reset");
  printf("\n");
	*ID = max;

	// fermeture des fichier et suppression des fichiers inutiles
	fclose(fichier);
	remove("temp");
	remove("temp2");
	return 0;
}



int rechercher_image(PileDescripteurImage* p,PileLien* l,int nBits,int n_resultats){
	bool ajout_par_utilisateur = false;
	int id_fichier_a_ouvrir = -1;
	char nom[100];

	printf("Entrez le nom de votre fichier :");
	scanf("%s",nom);
	strcat(nom,".txt");
	
	if(strlen(nom)>50){
		printf("Ce nom de fichier est trop long, veuillez raccourcir le nom de votre fichier avant de réésayer !");
		return 1;
	}
	
	// fichier déjà dans la base de donnée ou ajouté par l'utilisateur
	DescripteurImage fichier_recherche;
	if(dejaVu(nom,*l)>=0){
		affectDescripteurImage(getDescripteurImageViaNom(*p,nom),&fichier_recherche);
	}else{
		char chemin[100] = "../../Fichier_Recherche/";
		char chemin_existe[100] = "./Fichier_Recherche/";
		strcat(chemin,nom);
		strcat(chemin_existe,nom);
		if( access( chemin_existe , F_OK ) == 0 ){
			fichier_recherche = creerDescripteurImage(chemin,nBits,-1);
			ajout_par_utilisateur = true;
		}else{
			error();
			return 2;
		}
	}
	if(ajout_par_utilisateur){
		puts("Le fichier est ajoute dans ./Fichier_Recherche");
	}
	//afficheDescripteurImage(fichier_recherche);
	
	int* id = NULL; // identificateur
	int* di = NULL; // distances
	free(di);
	free(id);
	di = (int*)malloc(p->taille*sizeof(int));
	id = (int*)malloc(p->taille*sizeof(int));;
	
	if(di != NULL && id != NULL){
		for(int i = 0;i<n_resultats;i++){
			di[i] = -1;
			id[i] = -1;
		}
	}else{
		puts("ERREUR, recherche impossible");
		return 2;
	}
	
	// calcul des distances 
	int distance = 0;
	DescripteurImage* autre_desc;
	for(int i = 0;i<p->taille;i++){
		autre_desc = getDescripteurImage(*p,i);
		distance = distanceDescripteurImage(fichier_recherche,*autre_desc);
		//printf("distance entre %s et %s = %d\n",getNomDescripteurImage(fichier_recherche),getNomDescripteurImage(*autre_desc),distance);
		di[i] = distance;
		id[i] = getIdDescripteurImage(*autre_desc);
	}
	puts("");

	printf("Les fichiers ressemblants sont :\n");
	int min;
	//int id_fichier_a_ouvrir = -1;
	int nombre_fichiers_trouves = 0;
	int indexe;
	for(int j = 0;j<n_resultats;j++){ // boucle sur le nombre de resultats définis
		min = -1;
		indexe = -1;
		for(int i = 0;i<p->taille;i++){ // boucle sur toutes les distances
			if(di[i]>-1 && (min == -1 || di[i]>min) ){ // si la distance est valide et que aucune distances n'a été trouvée
				min = di[i];
				indexe = i;
				if(j == 0) {
          id_fichier_a_ouvrir = i;
        }
			}
		}

		if(min!=0){
			char nom_sans_extension[10] = "";
			strncat(nom_sans_extension,getNomDescripteurImage(*getDescripteurImageViaId(*p,id[indexe])),strlen(getNomDescripteurImage(*getDescripteurImageViaId(*p,id[indexe])))-4);
			printf("[%d] %s ressemblance = %d\n",j+1,nom_sans_extension,di[indexe]);
		di[indexe] = -1;
		}
	}

	char commande[100] = "eog ./data/";
	if(getDescripteurImageViaId(*p,id[id_fichier_a_ouvrir])->histogramme.couleur){
		strcat(commande,"TEST_RGB/");
	}else{
		strcat(commande,"TEST_NB/");
	}
	strncat(commande,getNomDescripteurImage(*getDescripteurImageViaId(*p,id[id_fichier_a_ouvrir])),strlen(getNomDescripteurImage(*getDescripteurImageViaId(*p,id[id_fichier_a_ouvrir])))-3);
	if(getDescripteurImageViaId(*p,id[id_fichier_a_ouvrir])->histogramme.couleur){
		strcat(commande,"jpg");
	}else{
		strcat(commande,"bmp");
	}
	printf("\nCommande = %s\n",commande);

	free(id);
	free(di);
	return 0;
}



/* @@@@@@@@@@@@ Inexation et Recherche Audio @@@@@@@@@@@@@@ */

int indexation_fichiers_audio(PileDescripteurAudio* p,PileLien* l,int nombreDesIntervales,int* ID){
	int pourcentage;

	// vider la pile si elle est deja remplie
	if(p->taille > 0){
		freePileDescripteurAudio(p);
		//puts("La pile de descripteur a été free");
	}
	// vider la pile de liens si deja remplie 
	if(l->taille > 0){
		freePileLien(l);
		//puts("La pile de liens a été free");
	}

	// récupération du nom des fichiers à indexer 
	system("ls ./data/TEST_SON | grep '.txt' > tempSON");
	system("wc -l tempSON > tempSON2");
	int max = 0;

	// récupération du nombre de fichiers à indexer
	FILE* fichier = NULL;
	fichier = fopen("tempSON2","r");
	fscanf(fichier,"%d",&max);
	fclose(fichier);
	//printf("============================\n");
	//printf("Il y a %d fichiers à indexer\n",max);
	//printf("============================\n");

	// indexation de chacun de ces fichiers
	char fichierCourant[50];
	fichier = fopen("tempSON","r");
	couleur("jaune");
	for(int i = 0;i<max;i++){
		fscanf(fichier,"%s",fichierCourant);
		toutDescripteurAudio(fichierCourant,p,l,nombreDesIntervales,i);
    pourcentage = ((i+1)*100)/max;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	couleur("vert");
  printProgressBar(100);
  couleur("reset");
  printf("\n");
	*ID = max;

	// fermeture des fichier et suppression des fichiers inutiles
	fclose(fichier);
	remove("tempSON");
	remove("tempSON2");
	return 0;
}



int rechercher_audio(PileDescripteurAudio* p,PileLien* l,int nombreDesIntervales,int n_resultats){
	bool ajout_par_utilisateur = false;
	if(nombreDesIntervales==-1){
		puts("ERREUR, nombre d'intervalles negatif");
		return 1;
	}
	int* id = NULL; // identificateur
	float* di = NULL; // distances
	di = (float*)malloc(p->taille*sizeof(float));
	id = (int*)malloc(p->taille*sizeof(int));
	if(di != NULL && id != NULL){
		for(int i = 0;i<n_resultats;i++){
			di[i] = -1;
			id[i] = -1;
		}
	}
	// fichier déjà dans la base de donnée ou ajouté par l'utilisateur
	char nom[100];
	printf("Entrez le nom de votre fichier : ");
	scanf("%s",nom);
	strcat(nom,".txt");
	
	if(strlen(nom)>50){
		printf("Ce nom de fichier est trop long, veuillez raccourcir le nom de votre fichier avant de réésayer !");
		return 1;
	}
	
	DescripteurAudio fichier_recherche;
	if(dejaVu(nom,*l)>=0){
		affectDescripteurAudio(getDescripteurAudioViaNom(*p,nom),&fichier_recherche);
		//puts("\nLe fichier recherché est :");

	}else{
		char chemin[100] = "../../Fichier_Recherche/";
		char chemin_existe[100] = "./Fichier_Recherche/";
		strcat(chemin,nom);
		strcat(chemin_existe,nom);
		if( access( chemin_existe , F_OK ) == 0 ){
			fichier_recherche = creerDescripteurAudio(chemin,nombreDesIntervales,-1);
			ajout_par_utilisateur = true;
		}else{
			error();
			return 2;
		}
	}
	if(ajout_par_utilisateur){
		puts("Le fichier est ajoute dans ./Fichier_Recherche");
	}
	/*printf("•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••\n");
	afficheDescripteurAudio(fichier_recherche);
  printf("\n•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••\n");*/
	// calcul des distances 
	float distance = 0;
	float meilleurEndroit = -1.0;
  float* tableauMeilleurEndroit = NULL;
  tableauMeilleurEndroit = (float*)malloc(p->taille*sizeof(float));
	DescripteurAudio* autre_desc;
	for(int i = 0;i<p->taille;i++){
		autre_desc = getDescripteurAudio(*p,i);
		distance = distanceDescripteurAudio(autre_desc, &fichier_recherche, &meilleurEndroit);
		//printf("distance entre %s et %s = %f %\nmeilleurEndroit = %f seconde(s)\n-----------------------------------------------------------------\n",getNomDescripteurAudio(fichier_recherche),getNomDescripteurAudio(*autre_desc),distance, meilleurEndroit);
		
		di[i] = distance;
		id[i] = getIdDescripteurAudio(*autre_desc);
    tableauMeilleurEndroit[i]=meilleurEndroit;
	}
	puts("");
	printf("Les fichiers ressemblants sont :\n");
	float min;
	//int idmin;
	int indexe;
  int nb_resultatsAffiches=0;
  int nb_resultatsNegliges=0;
  // boucle sur le nombre de resultats définis + on prend en compte le fichier recherche (on ne l'affiche pas) 
	static int id_fichier_a_ouvrir;
  while ( (nb_resultatsAffiches+nb_resultatsNegliges)<=n_resultats && (nb_resultatsAffiches+nb_resultatsNegliges)<p->taille){
	//for(int j = 0 ; (j<n_resultats) && (nb_resultatsAffiches<=(n_resultats-nb_resultatsNegliges)) ;j++){ // boucle sur le nombre de resultats définis
		min = -1;
		//idmin = -1;
		indexe = -1;
		
		for(int i = 0;i<p->taille;i++){ // boucle sur toutes les distances
			if(di[i]>=0 && (min == -1 || di[i]<min) ){ // si la distance est valide et que soit aucune distances n'a été trouvée
				min = di[i];
				//idmin = id[i];
				indexe = i;
			}
		}
		
    // char* getNomDescripteurAudio(DescripteurAudio d)
    char* nomDescripteurCourant;
    nomDescripteurCourant = getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id[indexe]));
    //printf("Descripteur courant = %s\n",nomDescripteurCourant);
    if (strcmp(nomDescripteurCourant, nom)!=0){
			char nom_sans_extension[50] = "";
      strncat(nom_sans_extension, getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id[indexe])),strlen(getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id[indexe])))-4);
      printf("[%d] %s : différence = %.2f %%  \n",nb_resultatsAffiches+1,nom_sans_extension,di[indexe]);
			if(nb_resultatsAffiches==0){
				id_fichier_a_ouvrir = indexe;
			}
      
      //printf("######### indexe = %d\n######### nom = %s\n", indexe, getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id[indexe])));
      printf("    L'endroit le plus pertinant est : %.2f seconde(s)\n", tableauMeilleurEndroit[indexe]);
      nb_resultatsAffiches++;
    }
    else{
      //printf("\nLe fichier recherche --> %s n'est pas affiche\n\n",nomDescripteurCourant);
      if(nb_resultatsNegliges==0){
				id_fichier_a_ouvrir = indexe;
			}
      nb_resultatsNegliges++;
    }
		di[indexe] = -1;
	}

  // affichage de fichier audio
  //bool ouverture = true;
  char commandeAfficherAudio[80] = "play ./data/TEST_SON/";
  int lenghtNom = strlen(getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)));
    // if nom est conntenue dans base de recherche --> afficher le fichier de base de recherche a partir de 0:0 (car on cherche le meme fichier!)
  char cheminAudio[80] = "./data/TEST_SON/";
  strncat(cheminAudio, nom,lenghtNom-3);
  strcat(cheminAudio,"wav");
  //printf("cheminAudio = %s\n", cheminAudio);
  char play[80] = "play ";
  if (access(cheminAudio, F_OK)==0){
    //printf("Audio existe dans la base de donnee!\n");
    // on affiche le meme fichier sans trim
    strcat(commandeAfficherAudio, getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)));
    printf("\nExecution de : %s\n",commandeAfficherAudio);
  }
  else {
    strncat(commandeAfficherAudio, getNomDescripteurAudio(*getDescripteurAudioViaId(*p,id_fichier_a_ouvrir)),lenghtNom-3);
    strcat(commandeAfficherAudio,"wav trim ");
    char result[50]; 
    float num = tableauMeilleurEndroit[id_fichier_a_ouvrir];
    int num1 = (int) num/60;
    int num2 = (int) num;
    while (num2>=60){
      num2-=60;
    }
    sprintf(result, "%d:%d", (int)num/60, num2); 
    strcat(commandeAfficherAudio, result);
  	printf("\nExecution de : %s\n",commandeAfficherAudio);
  }
  //if (ouverture){
    //printf("\nCommande qu'on passera au system : %s\n", commandeAfficherAudio);
    //system(commandeAfficherAudio);
    // commande "play" --> lancer le fichier
    // trim
  //}
  
  // ********************

// 2 memes fichiers (verification du nom) : distance negative, distance a 100%
	free(id);
	free(di);
	return 0;
}


/////////////////////
// fichiers Textes //
/////////////////////


int indexation_fichiers_textes(PileDescripteurTexte* p,PileLien* l,int nmb_mots,int* ID){
	int pourcentage;

	// vider la pile si elle est deja remplie
	if(p->taille > 0){
		freePileDescripteurTexte(p);
		//puts("La pile de descripteur à été free");
	}
	// vider la pile de liens si deja remplie 
	if(l->taille > 0){
		freePileLien(l);
		//puts("La pile de liens à été free");
	}

	// récupération du nom des fichiers à indexer 
	system("ls ./data/Textes | grep '.xml' > temp");
	system("wc -l temp > temp2");
	int max = 0;

	// récupération du nombre de fichiers à indexer
	FILE* fichier = NULL;
	fichier = fopen("temp2","r");
	fscanf(fichier,"%d",&max);
	fclose(fichier);
	/*
	printf("============================\n");
	printf("Il y a %d fichiers à indexer\n",max);
	printf("============================\n");
	*/

	// indexation de chacun de ces fichiers
	char fichierCourant[100];
	fichier = fopen("temp","r");
	couleur("jaune");
	for(int i = 0;i<max;i++){
		fscanf(fichier,"%s",fichierCourant);
		toutDescripteurTexte(fichierCourant,p,l,nmb_mots,i);
    pourcentage = ((i+1)*100)/max;
    printProgressBar(pourcentage);
    fflush(stdout);
	}
	couleur("vert");
  printProgressBar(100);
  couleur("reset");
  printf("\n");
	*ID = max;

	// fermeture des fichier et suppression des fichiers inutiles
	fclose(fichier);
	remove("temp");
	remove("temp2");
	return 0;
}


int rechercher_texte(PileDescripteurTexte* p,PileLien* l,int n_mots,int n_resultats){
	//bool ajoute_par_utilisateur = false;
	char nom[100];
	printf("Entrez le nom de votre fichier :");
	scanf("%s",nom);
	strcat(nom,".xml");
	
	if(strlen(nom)>75){
		printf("Ce nom de fichier est trop long, veuillez raccourcir le nom de votre fichier avant de réésayer !");
		return 1;
	}

	// fichier déjà dans la base de donnée ou ajouté par l'utilisateur
	DescripteurTexte fichier_recherche;
	if(dejaVu(nom,*l)>=0){
		affectDescripteurTexte(getDescripteurTexteViaNom(*p,nom),&fichier_recherche);
		puts("Le fichier est présent dans la base de donnée.");
	}else{
		char chemin[100] = "../../Fichier_Recherche/";
		char chemin_existe[100] = "./Fichier_Recherche/";
		strcat(chemin,nom);
		strcat(chemin_existe,nom);
		if( access( chemin_existe , F_OK ) == 0 ){
			fichier_recherche = creerDescripteurTexte(chemin,n_mots,-2);
		}else{
			error();
			return 2;
		}
	}
	//afficheDescripteurImage(fichier_recherche);
	
	int* id = NULL; // identificateur
	int* di = NULL; // distances
	di = (int*)malloc(p->taille*sizeof(int));
	id = (int*)malloc(p->taille*sizeof(int));;
	
	if(di != NULL && id != NULL){
		for(int i = 0;i<n_resultats;i++){
			di[i] = -1;
			id[i] = -1;
		}
	}else{
		puts("ERREUR, recherche impossible");
		return 2;
	}
	
	// calcul des distances 
	int distance = 0;
	DescripteurTexte* autre_desc;
	for(int i = 0;i<p->taille;i++){
		autre_desc = getDescripteurTexte(*p,i);
		distance = distanceDescripteurTexte(fichier_recherche,*autre_desc);
		//printf("distance entre %s et %s = %d\n",getNomDescripteurTexte(fichier_recherche),getNomDescripteurTexte(*autre_desc),distance);
		di[i] = distance;
		id[i] = getIdDescripteurTexte(*autre_desc);
	}
	puts("");

	printf("Les fichiers ressemblants sont :\n");
	int min;
	//int idmin;
	int indexe;
	int nombre_fichiers_trouves = 0;
	for(int j = 0;j<n_resultats;j++){ // boucle sur le nombre de resultats définis
		min = -1;
		//idmin = -1;
		indexe = -1;
		for(int i = 0;i<p->taille;i++){ // boucle sur toutes les distances
			if(di[i]>-1 && (min == -1 || di[i]>min) ){ // si la distance est valide et que soit aucune distances n'a été trouvée
				min = di[i];
				//idmin = id[i];
				indexe = i;
			}
		}
		//
		// ATTENTION J'avais un problème avec une confusion entre IDmin et INDEXE
		// JE l'ai corrigée ... enfin je crois 
		// Mais elle n'est pas testées donc peut-etre qu'il y a encore un problème
		if(min!=0){
			nombre_fichiers_trouves++;
			printf("[%d] %s ressemblance = %d\n",j+1,getNomDescripteurTexte(*getDescripteurTexteViaId(*p,id[indexe])),di[indexe]);
		}
		
		//printf("[%d] différence = %d\n",j,di[indexe]);
		di[indexe] = -1;
	}
	if(nombre_fichiers_trouves==0){
		puts("\nAucun dossier dans la base de donnée ne traite du même sujet.");
	}

	free(id);
	free(di);
	return 0;
}


int rechercher_mots_texte(PileDescripteurTexte* p,int n_resultats){
	char motLu[100];
  char mot[100];
  char c;
  int i;
  int j;
  
	printf("Entrez le mot :");
	scanf("%s",motLu);
	
	/* Traitement du mot */
  i = 0;
  j = 0;
  c = motLu[i];
  while(c != '\0') {
    /* Si le caractère est une majuscule on le passe en minuscule */
    if('A' <= c && c <= 'Z') { 
      mot[j] = motLu[i] + 32; 
    }
    /* Si le caractère lu est accentué : À Â È É Ê Ë Î Ï Ù Û Ç (les minuscules aussi) on lui retire son accent */
    else if(c == '\xc3') {
      i++;
      c = motLu[i];
      if(c == '\x80' || c == '\x82' || c == '\xa0' || c == '\xa2') mot[j] = 'a'; 
      else if(c == '\x88' || c == '\x89' || c == '\x8a' || c == '\x8b' || c == '\xa8' || c == '\xa9' || c == '\xaa' || c == '\xab') mot[j] = 'e';
      else if(c == '\x8e' || c == '\xae' || c == '\x8f' || c == '\xaf') mot[j] = 'i';
      else if(c == '\x99' || c == '\x9b' || c == '\xb9' || c == '\xbb') mot[j] = 'u';
      else if(c == '\x87' || c == '\xa7') mot[j] = 'c';
      else { fprintf(stderr, "1.caractère inconnu\n"); return -1; }
    }
    /* Si le caractère est un e dans l'o : œ */
    else if(c == '\xc5') {
      i++;
      c = motLu[i];
      if(c == '\x92' || c == '\x93') {
        mot[j] = 'e';
        ++j;
        mot[j] = 'o';
      } else {
        fprintf(stderr, "2.caractère inconnu\n"); 
        return -2;
      }
    }
    else {
      mot[j] = motLu[i];
    }
    ++i;
    c = motLu[i];
    ++j;
  }

  mot[j] = c;

  int* id = NULL; // identificateur
	int* di = NULL; // distances
	di = (int*)malloc(p->taille*sizeof(int));
	id = (int*)malloc(p->taille*sizeof(int));;
	
	if(di != NULL && id != NULL){
		for(int i = 0;i<n_resultats;i++){
			di[i] = -1;
			id[i] = -1;
		}
	}else{
		puts("ERREUR, recherche impossible");
		return 2;
	}
	
	// calcul des distances 
	int distance = 0;
	DescripteurTexte* autre_desc;
	for(int i = 0;i<p->taille;i++){
		autre_desc = getDescripteurTexte(*p,i);
		distance = distanceDescripteurMotTexte(mot,*autre_desc);
		//printf("distance entre %s et %s = %d\n",mot,getNomDescripteurTexte(*autre_desc),distance);
		di[i] = distance;
		id[i] = getIdDescripteurTexte(*autre_desc);
	}
	


	puts("");

	printf("Les fichiers contenant le mot :%s\n",mot);
	int min;
	//int idmin;
	int indexe;
	int nombre_fichiers_trouves =0;
  int id_fichier_a_ouvrir = -1;
	for(int j = 0;j<n_resultats;j++){ // boucle sur le nombre de resultats définis
		min = -1;
		//idmin = -1;
		indexe = -1;
		for(int i = 0;i<p->taille;i++){ // boucle sur toutes les distances
			if(di[i]>-1 && (min == -1 || di[i]>min) ){ // si la distance est valide et que soit aucune distances n'a été trouvée
				min = di[i];
				//idmin = id[i];
				indexe = i;
        if(j == 0) {
          id_fichier_a_ouvrir = i;
        }
			}
		}
		
		if(min!=0){
			nombre_fichiers_trouves++;
			printf("[%d] %s occurence = %d\n",j+1,getNomDescripteurTexte(*getDescripteurTexteViaId(*p,id[indexe])),di[indexe]);
		}
		//printf("[%d] différence = %d\n",j,di[indexe]);
		di[indexe] = -1;
	}
	if(nombre_fichiers_trouves==0){
		printf("\nAucun fichier dans la base de donnée contient le mot : %s\n",motLu);
		puts("Vous pouvez essayer de demander à l'administrateur de relancer une indexation avec plus de mots");
	} else {
    char commande[100] = "cat ";
    char* nom_fichier_a_ouvrir = getNomDescripteurTexte(*getDescripteurTexteViaId(*p,id[id_fichier_a_ouvrir]));
		char chemin[100] = "./data/Textes/";
    strcat(commande, chemin);
		strcat(commande,nom_fichier_a_ouvrir);
		printf("\nAffichage de %s\n",getNomDescripteurTexte(*getDescripteurTexteViaId(*p,id[id_fichier_a_ouvrir])));
		system(commande);
  }


	free(id);
	free(di);
	return 0;
}