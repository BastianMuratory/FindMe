#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ICI
// le mot ICI précédent va devenir LA après l'execution (voir tests sur ftell et fseek en fin de fichiers)



// https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-lire-et-ecrire-dans-des-fichiers

// http://paristech.institutoptique.fr/site.php?id=469&fileid=2739



int main() {
/*	// ///////////////////////////////////////////////
	// CAS 1 : fichiers textes
	// ///////////////////////////////////////////////
	printf("// ///////////////////////////////////////////////\n");
	printf("// CAS 1 : fichiers textes\n");
	printf("// ///////////////////////////////////////////////\n");

	// commandes basiques : ouverture/fermeture et lecture
 	// //////////////////////////////////////////////
	printf("// commandes basiques : ouverture/fermeture et lecture \n // puis affichage de ce qui est lu\n");
 	printf("// //////////////////////////////////////////////\n");

	// etape 1 : declaration d'une variable qui permettra l'accès au fichier
	// type FILE (défini ds stdio.h)
	FILE * fictxt = NULL ; // init permettra de faire des verif

	// etape 2 : ouverture du fichier en mettant à jour la variable lefichier
	// cette ouverture se fait avec la fonction fopen qui prend deux parametres :
	//    le nom du fichier et le mode d'ouverture (lecture, écriture, ...)
	// (faire "man fopen" dans un terminal pour avoir la doc de cette fonction)
	// ici on ouvre le fichier qui s'appelle fichier.c en mode lecture uniquement
	fictxt = fopen("ex2.c", "r") ; 

	// etape 3 : verifier que l'ouverture est OK
	if (fictxt == NULL)
		// ouverture NOK 
		printf("Ouverture NOK\n\n");
		// on ne peut rien faire => arrêt
	else {
		// ouverture OK 
		printf("ouverture OK\n\n");
		// on peut continuer

	// etape 4 : lecture
		// chaine par chaine jusqu'à la fin du fichier
		char str [256] = "" ;
		while (fgets(str, 256, fictxt) != NULL) {
			printf("%s",str) ;
		}
	}
	// etape finale : refermer le fichier
	fclose (fictxt) ;
		
		
	// les petits plus : se deplacer dans les fichiers
	// ///////////////////////////////////////////////
	printf("// les petits plus : se deplacer dans les fichiers\n// puis modif d'une partie du texte et affichage du resultat \n");
	printf("// ///////////////////////////////////////////////\n");

	// Etape 1 : savoir où on est
	// mise en place du test : on reouvre le fichier et on cherche la position qui nous interesse
	fictxt = fopen("ex2.c","r+") ;   // on ouvre en mode lecture-ecriture
	if (fictxt != NULL) {
		// ouverture OK 
		printf("\n ouverture OK\n\n");
		// lecture chaine par chaine jusqu'à la fin du fichier
		// en memorisant la position de celle de la ligne commençant par // ICI 
		char str [256] = "" ;
		long posICI ;
		while (fgets(str, 256, fictxt) != NULL) {
			if (strncmp (str,"// ICI",6) == 0) posICI = ftell(fictxt)  ;
		}
		printf("posICI = %ld\n",posICI);  // on attend 68 (le nb de caractères depuis 
						  // le début du fichier jusqu'au début de la 
						  // ligne qui suit celle qui contenait "// ICI"
	// etape 2 : aller a posICI et ecrire LA a la place de ICI
		fseek(fictxt, posICI-7, SEEK_SET);  // 7 = 6 + 1 RC
						    // SEEK_SET constante donnant l'origine du fichier
		fputs("// LA \n",fictxt);	

	// verif :
		rewind(fictxt) ; // retour au debut du fichier
		while (fgets(str, 256, fictxt) != NULL) {
			printf("%s",str) ;
		}		

		fclose(fictxt);
	}	

*/
printf("\n\n\n");
	// //////////////////////////////////////////////////////
	// CAS 2 : fichiers binaires
	// //////////////////////////////////////////////////////
	printf("// ///////////////////////////////////////////////\n");
	printf("// CAS 2 : fichiers binaires\n");
	printf("// ///////////////////////////////////////////////\n");

	// commandes basiques : ouverture/fermeture et lecture
 	// //////////////////////////////////////////////
	printf("// commandes basiques : ouverture/fermeture et lecture \n // puis affichage de ce qui est lu\n");
 	printf("// //////////////////////////////////////////////\n");

	// etape 1 : idem
	FILE * ficbin = NULL ;

	// etape 2 : idem mais avec un mode d'ouverture precisant l'aspect binaire 
	// donc "rb" au lieu de "r"
	ficbin = fopen("jingle_fi.txt", "rb");

	// etape 3 : idem	
	if (ficbin == NULL)
		// ouverture NOK 
		printf("\n Ouverture NOK\n\n");
		// on ne peut rien faire => arrêt
	else {
		// ouverture OK 
		printf("\n ouverture OK\n\n");
		// on peut continuer

	// etape 4 : lecture
	// il faut savoir comment les données sont organisées ds le fichier 
	// pour pouvoir les lire par bloc
		// ici, on choisit : 1 bloc = 10000 int
		int tabbin[1000000] ;
		int nb = fread(tabbin, sizeof(double), 1000000, ficbin);
		// la ligne precedente permet de lire le contenu accessible
		// depuis ficbin par bloc de 10000 int au max
		// et range cela dans le tableau tabbin
		// s'il y a moins de 10000 int ds le fichier, alors nb 
		// contiendra le nb d'int lus
		printf("nb = %d", nb);
    printf("\n\n");
     fseek(ficbin,0,SEEK_END);
   long  taille= ftell(ficbin);
   printf("%ld",taille);
  
		// pour savoir si on s'est arrêté sur une erreur ou 
		// sur la fin du fichier on peut faire :
		if (feof(ficbin))
			printf("\n arret : fin fichier\n") ;
		if (ferror(ficbin))
			printf("\n arret : erreur lecture\n") ;
		
		// affichage contenu du fichier binaire sous la forme d'int
	/*	for (int i = 0 ; i < nb ; i++) 
			printf("%d - ", tabbin[i]) ;
      printf("\n");
	*/

	}

	// etape finale : idem
	fclose (ficbin) ;
		
/*		
	// les petits plus : se deplacer dans les fichiers
	// ///////////////////////////////////////////////
	printf("// les petits plus : se deplacer dans les fichiers\n// puis modif d'une partie du texte et affichage du resultat \n");
	printf("// ///////////////////////////////////////////////\n");

	// CAS 2 : fichier binaire (attention les positions se comptent 
	// en nb d'octets

	// Etape 1 : savoir où on est
	// mise en place du test : on ouvre le fichier et on cherche la position qui nous interesse
	ficbin = fopen("corpus_fi.bin","rb+") ;   // on ouvre en mode lecture-ecriture
	if (ficbin != NULL) {
		// ouverture OK 
		printf("\n ouverture OK\n\n");
		// il faut savoir comment les données sont organisées ds le fichier 
		// pour pouvoir les lire par bloc
		// ici, on choisit : 1 bloc = 10 int 
		int tabbin2[10] ;
		int nb = fread(tabbin2, sizeof(int), 10, ficbin);
		printf("premier bloc de %d int : \n",nb) ;
		for (int i = 0 ; i < nb ; i++) 
			printf("%d - ", tabbin2[i]) ;
		int v1 = tabbin2[0];
		long pos1 = ftell(ficbin) ;
		printf("\n\tpos1 = %ld\n",pos1) ;  // on attend 40 (car 10 * 4, un int étant sur 4 octets sur ma machine
		nb = fread(tabbin2, sizeof(int), 10, ficbin);
		printf("\nsecond bloc de %d int : \n",nb) ;
		for (int i = 0 ; i < nb ; i++) 
			printf("%d - ", tabbin2[i]) ;
		int v2 = tabbin2[0];
		long pos2 = ftell(ficbin) ;
		printf("\n\tpos2 = %ld\n",pos2) ;  // on attend 80 (car (10 * 4)*2, car second bloc de 10 int

	// etape 2 : echanger les premières valeurs entre les deux blocs lus
		fseek(ficbin, pos1 - (10* sizeof(int)), SEEK_SET);  
		fwrite(&v2,sizeof(int),1,ficbin);	
		fseek(ficbin, pos2 - (10* sizeof(int)), SEEK_SET);  
		fwrite(&v1,sizeof(int),1,ficbin);

	// verif 
		rewind(ficbin) ; // retour au début
		nb = fread(tabbin2, sizeof(int), 10, ficbin);
		printf("\npremier bloc apres modif : \n") ;
		for (int i = 0 ; i < nb ; i++) 
			printf("%d - ", tabbin2[i]) ;
		nb = fread(tabbin2, sizeof(int), 10, ficbin);
		printf("\n\nsecond bloc apres modif : \n") ;
		for (int i = 0 ; i < nb ; i++) 
			printf("%d - ", tabbin2[i]) ;

		fclose (ficbin) ;

	}
	printf("\n");
 */
}


