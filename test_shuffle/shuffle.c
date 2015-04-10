#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

void print_tableau2(int taille, int t[][taille]){
  printf("\n[");
  printf("[");
  for (int j = 0; j<taille-1; ++j){
      printf("%d,",t[0][j]);
    }
  printf("%d],\n",t[0][taille-1]);
  
  for (int i =1; i<taille-1; ++i){
    printf("[ ");
    for (int j = 0; j<taille-1; ++j){
      printf("%d,",t[i][j]);
    }
    printf("%d],\n",t[i][taille-1]);
  }

  printf("[ ");
  for (int j = 0; j<taille-1; ++j){
      printf("%d,",t[taille-1][j]);
    }
  printf("%d]",t[taille-1][taille-1]);
  printf("]\n");
}

void print_tableau(int t[],int taille){
  printf("\n [");
  for (int i = 0; i<taille-1; ++i){
    printf("%d,",t[i]);
  }
  printf("%d]\n",t[taille-1]);
}

void remplir_g(int taille, int g[][taille], int t[]){
  for (int i =0; i<taille; i++){
    g[t[i]][i]+=1;
  }
}

void swap(int * a, int * b){
  int c = *a;
  *a=*b;
  *b=c;
}

void shuffle(int t[], int taille){
  for (int i = 0; i <taille; i++){
    swap(&t[i], &t[i+rand()%(taille-i)]);
  }
}

void F(int taille, int t[][taille], double F[], double e){
  for (int i =0; i<taille; i++){
    for (int j =0; j<taille; j++){
      F[i]+=((t[i][j]-e)*(t[i][j]-e)/e);
    }
  }
}

//#define taille 10

int main(int argc, char * argv[]){
  assert(argv[1]!=NULL);

  printf("On lance le test avec %d essais\n", atoi(argv[1]));

  /* Initialisation pour le random */
  time_t t2;
  srand((unsigned) time(&t2));

  /*Initialisation des variables */
  int taille = 10; // Variable pour le nb d'elements dans le tableau 
  int g[taille][taille];  
  int t[taille];
  double F1[taille];
  double e = (atoi(argv[1]))/10;

  /* Initialisation des tableaux à 0 */
  for (int i = 0; i<taille; i++){
    for (int j = 0; j<taille; j++){
      g[i][j]=0;}}

  for (int i =0 ; i <taille; ++i){
    F1[i]=0;}

  /*Initialisation du tableau que l'on shuffle */
  for (int i = 0; i<taille; i++){
    t[i]=i;}

  /* Shuffle du tableau (argv[1]) fois, puis remplissage du double tableau */
  for (int u = 0; u<atoi(argv[1]); ++u){
    shuffle(t, taille);
    remplir_g(taille, g, t);
  }

  print_tableau2(taille, g);

  /*Calcul et affichage de la distributivité */
  F(taille, g, F1, e); 
  for (int i =0 ; i <taille; ++i){
    printf("\nLa distribution selon X² de %d est de %lf.\n",i, F1[i]);
  }
  
  return 0;
}

