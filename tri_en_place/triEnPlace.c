#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void afficher(double * t,size_t size0, size_t size){
  printf("[");
  for (int i=size0; i<size-1; i++){
    printf("%lf,",t[i]);
  }
  printf("%lf]\n",t[size-1]);
}

void sort(double * array,size_t size0, size_t size2){
  if (size2-size0<=1){
    return ;}

  sort(array,size0,(size2-size0)/2+size0);
  sort(array,(size2-size0)/2+size0,size2);
  int i=size0; int j=(size2-size0)/2+size0; double var=-1;
  while((i!=j)&&(j<size2)){
    if (array[i]<=array[j]){
      ++i;
    }
    else{  //array[i]>array[j]
      var=array[j];
      for (int u=j; u>i;--u){
	array[u]=array[u-1];
      }
      array[i]=var;
      ++i; ++j;
    }
  }
}

int main(int argc, char* argv[]){ //On part du principe que l'utilisateur n'est pas idiot, et ne va rentrer que des nombres

  /* double t[6]={1,2,4,3,6,5}; */
  /* double t2[6]={1,2,4,3,4,5}; */
  /* afficher(t,0, sizeof(t)/sizeof(double)); */
  /* printf("%d\n",(sizeof(t)/sizeof(double))/2); */
  /* afficher(t2,0, sizeof(t2)/sizeof(double)); */
  /* printf("%d\n",(sizeof(t2)/sizeof(double))/2); */
  /* printf("\n"); */  
  /* sort(t,0,sizeof(t)/sizeof(double)); */
  /* sort(t2,0,sizeof(t2)/sizeof(double)); */

  if(argc==1){
    return EXIT_FAILURE;
  }
  double * tableau=malloc(sizeof(double)*(argc-1));
  for(int i=0; i<argc-1;++i){
    tableau[i]=atof(argv[i+1]);
  }
  afficher(tableau,0,argc-1);
  printf("Voici le tableau trié: \n");
  sort(tableau,0,argc-1);
  afficher(tableau,0,argc-1);
  free(tableau);
  return EXIT_SUCCESS;
}
