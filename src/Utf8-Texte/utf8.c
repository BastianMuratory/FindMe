#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// iconv -f iso-8859-1 -t ascii//TRANSLIT chemin/fichier.xml > temp 

int main(){
	char* init = "iso-8859-1";
	char* terminal  = "ascii//TRANSLIT";
	char debut[100] = "iconv -f ";
	strcat(debut,init);
	strcat(debut," -t ");
	strcat(debut,terminal);
	strcat(debut," ../../data/Textes/");
	


	system("ls ../../data/Textes | grep '.xml' > temp");
	system("wc -l temp > temp2");
	int max = 0;

	// récupération du nombre de fichiers à modifier
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
	for(int i = 0;i<max;i++){
		char commande[200] = "";
		char commande2[150] = "cat temp > ../../data/Textes/";
		

		//commande 1
		strcat(commande,debut);
		fscanf(fichier,"%s",fichierCourant);
		strcat(commande,fichierCourant);
		strcat(commande," > temp");

		//commande 2
		strcat(commande2,fichierCourant);

		// Execution
		//system(commande);
		//system(commande2);
	}
	return 0;
}