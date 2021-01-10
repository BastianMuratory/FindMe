#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#include "descripteurImage.h"

int main(int argc,char* argv[]){
	int ID = 10;
	int nb_bits = 2;
	/*
	DescripteurImage e = creerDescripteurImage("01.txt",nb_bits,ID);
	puts("AFF e");
	afficheDescripteurImage(e);
	
	puts("AFF d (affectdescripteur e)");
	DescripteurImage d;
	affectDescripteurImage(&e,&d,nb_bits);
	afficheDescripteurImage(d);



	puts("\n\n\n\n\n");

	FILE* fichier = NULL;
	fichier = fopen("TEMP","w");
	sauvegarderDescripteurImage(fichier,e);
	fclose(fichier);


	fichier = fopen("TEMP","r");
	DescripteurImage t = chargerDescripteurImage(fichier,nb_bits);
	afficheDescripteurImage(t);
	*/
	puts("Début programme");
	DescripteurImage nb1 = creerDescripteurImage("51.txt",nb_bits,ID);
	DescripteurImage nb2 = creerDescripteurImage("52.txt",nb_bits,ID);
	DescripteurImage nb3 = creerDescripteurImage("53.txt",nb_bits,ID);
	DescripteurImage nb4 = creerDescripteurImage("54.txt",nb_bits,ID);
	puts("===========================");
	DescripteurImage c1 = creerDescripteurImage("01.txt",nb_bits,ID);
	DescripteurImage c2 = creerDescripteurImage("02.txt",nb_bits,ID);
	DescripteurImage c3 = creerDescripteurImage("03.txt",nb_bits,ID);
	DescripteurImage c4 = creerDescripteurImage("04.txt",nb_bits,ID);
	puts("\n\n\n");

	afficheDescripteurImage(c1);puts("");
	afficheDescripteurImage(c2);puts("");
	afficheDescripteurImage(c3);puts("");
	afficheDescripteurImage(c4);puts("");
	
	puts("\n\n\n");
	printf("egales = %d\n",distanceDescripteurImage(nb1,nb1));
	printf("distance nb 51 52 = %d\n",distanceDescripteurImage(nb1,nb2));
	printf("distance nb 51 53 = %d\n",distanceDescripteurImage(nb1,nb3));
	printf("loin nb 51 54 = %d\n",distanceDescripteurImage(nb1,nb4));
	puts("\n");
	printf("egales = %d\n",distanceDescripteurImage(c1,c1));
	printf("distance c 01 02 = %d\n",distanceDescripteurImage(c1,c2));
	printf("distance c 01 03 = %d\n",distanceDescripteurImage(c1,c3));
	printf("loin c 01 04 = %d\n",distanceDescripteurImage(c1,c4));




	return EXIT_SUCCESS;
}
