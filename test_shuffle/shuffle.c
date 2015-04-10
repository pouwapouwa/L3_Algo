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

double moyenne(int taille, int t[][taille]){
  double resultat = 0;
  for (int i =0; i<taille; ++i){
    for (int j = 0; j<taille; ++j){
      resultat+=t[i][j];
    }
  }
  return resultat/(taille*taille);
}

void variance(int taille, int t[][taille], double var[], double moyenne){
  for (int i =0; i<taille; i++){
    for (int j =0; j<taille; j++){
      printf("%d // %d \n",t[i][j]-moyenne,((t[i][j]-moyenne)*(t[i][j]-moyenne)));
      var[i]+=((t[i][j]-moyenne)*(t[i][j]-moyenne));
    }
    var[i]=var[i]/taille;
    printf("la variance de %d est de %d\n",i,var[i]);
  }
}

#define taille 10

int main(){
  time_t t2;
  srand((unsigned) time(&t2));
  // int taille = 10;
  int g[taille][taille];
  
  int t[taille];
  for (int i = 0; i<taille; i++){
    t[i]=i;}

  for (int i = 0; i<taille; i++){
    for (int j = 0; j<taille; j++){
      g[i][j]=0;}
  }

  /* print_tableau2(taille, g); */
  /* printf("\n"); */
  /* shuffle(t, taille); */
  /* remplir_g(taille, g, t); */
  /* print_tableau(t, taille); */
  /* print_tableau2(taille, g); */
  /* printf("\n"); */

  for (int u = 0; u<500; ++u){
    shuffle(t, taille);
    remplir_g(taille, g, t);
  }

  print_tableau2(taille, g);

  double moy=moyenne(taille,g);
  printf("\nLa moyenne est de %lf\n", moy);

  double var[taille];

  for (int i =0 ; i <taille; ++i){
    var[i]=0;
  }
  
  variance(taille, g, var, moy);
  for (int i =0 ; i <taille; ++i){
    printf("\nLa variance de %d est de %d.\n",i, var[i]);
  }

  for (int i =0 ; i <taille; ++i){
    printf("%d", var[i]);
    double w = sqrt((double)var[i]);
    printf("\nL'écart type de %d est de %lf.\n",i, w);
  }
  
  return 0;
}

