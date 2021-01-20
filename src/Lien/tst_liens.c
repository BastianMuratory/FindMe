// Bastian : Fichier de test unitaire de la pile de liens.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./liens.h"


int main(int argc, char* argv[]){
	PileLien p = chargePileLien("base_donnee");
	affichePileLien(p);

	/*
	Lien d = creerLien("test.txt",10);
	affichePileLien(p);

	p = empileLien(p, d);
	affichePileLien(p);

	Lien d2 = creerLien("manger.txt",1610);
	p = empileLien(p, d2);
	affichePileLien(p);

	Lien d3 = creerLien("desert.txt",945);
	p = empileLien(p, d3);
	affichePileLien(p);
	*/
	sauvegardePileLien(p,"Temp");
	/*
	puts("récupération du descriptzeur à la place 1");
	Lien* test = getLien(p,1);
	afficheLien(*test);

	puts("\nrécupération du descripteur avec id = 10");
	Lien* test2 = getLienViaId(p,10);
	afficheLien(*test2);

	puts("\nrécupération du descripteur avec nom = 26.txt");
	Lien* test3 = getLienViaNom(p,"desert.txt");
	afficheLien(*test3);

	puts("\n=== Test depilement ===");
	p = depileLien(p);
	affichePileLien(p);

	int x = dejaVu("test.txt",p);
	printf("test.txt appartient a la pile %d \n",x);
	x = dejaVu("manger",p);
	printf("manger n'appartient pas a la pile %d \n",x);
	*/


	/*
	puts("\n=== Test Free ===");
	freePileLien(&p);
	affichePileLien(p);
	*/
	return EXIT_SUCCESS;
}