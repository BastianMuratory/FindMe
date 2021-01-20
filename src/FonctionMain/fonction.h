#ifndef __F_main_H__
#define __F_main_H__

#include <stdbool.h>

#define TAILLE_MAX 100

#define MIN_INDEXATION_AUDIO 10
#define MAX_INDEXATION_AUDIO 250
#define MIN_INDEXATION_IMAGE 1
#define MAX_INDEXATION_IMAGE 7
#define MIN_INDEXATION_TEXTE 1
#define MAX_INDEXATION_TEXTE 1000

void clear (void);

void color(char* couleur);

void connection(bool* admin);

void affichage(bool admin,int *x,int vT,int vI,int vA,bool indT,bool indI,bool indA,int der_texte,int der_image,int der_audio); // affiche le menu 


void logo();

void merci();
void erreur_relancer_indexation();


void changer_param_text(int* param,bool*); // renvoie false si le parramètre a été changé

void changer_param_image(int* param,bool*);

void changer_param_audio(int* param,bool*);



#endif

