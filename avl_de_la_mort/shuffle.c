#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

void print_tableau2(int t[][],int taille){
  printf("\n[");
  for (int i =0; i<taille-1; ++i){
    printf("[");
    for (int j = 0; j<taille-1; ++j){
      printf("%d,",t[i][j]);
    }
    printf("%d]\n",t[i][taille-1])
  }
  printf("%d]\n",t[taille-1][taille-1]);
}

void print_tableau(int t[],int taille){
  printf("\n[");
  for (int i = 0; i<taille-1; ++i){
    printf("%d,",t[i]);
  }
  printf("%d]\n",t[taille-1]);
}

int main(){
  time_t t2;
  srand((unsigned) time(&t2));
  int taille = 10;
  int g[taille][taille];
  
  int t[taille];
  for (int i = 0; i<taille; i++){
    t[i]=i;}

  for (int i = 0; i<taille; i++){
    for (int j = 0; i<taille; j++){
      g[i][j]=0;}
  }

  print_tableau2(g, taille);
  
  return 0;
}

