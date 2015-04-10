#include <stdio.h>
#include <stdlib.h>

void swap(double * a, double * b){
  double c = *a;
  *a=*b;
  *b=c;
}

double verrou(double cle,double i){
  if (cle == i){ return 0;} //ouvre
  else if (cle < i){ return 1;} //tourne
  else {return -1;}; //bloque
}

int test(double cle, double * array, size_t size){
  int i =0; int j = size-1; int emplacement = -1;
  while (i!=j){
    if (verrou(cle, array[i]) == 0){
      swap(array+i, array+i+1);
      emplacement=i;
    }
    else if (verrou(cle,array[i]) == -1){ //clé > verrou bloque
      ++i;;
    }
    else if(verrou(cle,array[i]) == 1){ // clé <verrou
      swap(array+j,array+i);
      --j;
    }
  }
  if (i==j){
    emplacement=i;
  }
  if (emplacement <= -1){
    printf("ERROR");
    return EXIT_FAILURE;}
  return emplacement;
}

void afficher(double * array, size_t size){
  printf("[");
  for (int i=0; i<size-1; ++i){
    printf("%d,",(int)array[i]);
  }
  printf("%d", (int)array[size-1]);
  printf("]\n");
}

/* void correspondance(double verrou,double * tdebut, double * tfin, size_t array){ //renvoie la place du verrou verrou de tfin dans tdebut */

/* } */

int main(void){
  double tcle[8]={7,3,5,6,4,1,0,2};
  double tverrou[8]={0,1,2,3,4,5,6,7};
  double tsolution[8]={-1,-1,-1,-1,-1,-1,-1,-1};

  printf("Valeurs Initiales : \n");
  printf("tclé : ");
  afficher(tcle, sizeof(tcle)/sizeof(double));
  printf("tverrou : ");
  afficher(tverrou, sizeof(tverrou)/sizeof(double));
  printf("tsolution : ");
  afficher(tsolution, sizeof(tsolution)/sizeof(double));
  
  int emplacement = -1;
  
  emplacement = test(tcle[0], tverrou, sizeof(tverrou)/sizeof(double));
  tsolution[0]=emplacement;

  for (int i =0; i<(sizeof(tverrou)/sizeof(double)); i++){
    if (verrou(i,tverrou[emplacement])==0){ //ouvre
      return EXIT_FAILURE;}
    else if (verrou(i,tverrou[emplacement])== 1){ //tourne
      int v=-1; int vmin=emplacement+1; int vmax=(sizeof(tverrou)/sizeof(double))-1;
      for (int j = 1; j < i; j++){
  	if (tcle[j] >tcle[0]){  //<== manque un test
  	  v=tcle[j];
  	  if (verrou(i,tverrou[v])==0){
  	    return EXIT_FAILURE;}
  	  if (verrou(i,tverrou[v])==1){
  	    vmin=v;}
  	  if (verrou(i,tverrou[v])==-1){
  	    vmax=v;}
  	}
      }
      tsolution[i]=test(tcle[i],tverrou+vmin, vmax+1);
    }
    else if (verrou(i,tverrou[emplacement]) == -1){ //bloque
      int v=-1; int vmin=0; int vmax=emplacement-1;
      for (int j = 1; j < i; j++){
  	if (tcle[j] <tcle[0]){  //<== manque un test
  	  v=tcle[j];
  	  if (verrou(i,tverrou[v])==0){
  	    return EXIT_FAILURE;}
  	  if (verrou(i,tverrou[v])==1){
  	    vmin=v;}
  	  if (verrou(i,tverrou[v])==-1){
  	    vmax=v;}
  	}
      }
      tsolution[i]=test(tcle[i],tverrou+vmin, vmax+1);
    }
    printf("\nje passe à i=%d\n",i);
    printf("tsolution : ");
    afficher(tsolution, sizeof(tsolution)/sizeof(double));
    printf("tverrou : ");
    afficher(tverrou, sizeof(tverrou)/sizeof(double));
  }
  
  printf("\n\nRéusltat :\n");
  printf("tclé : ");
  afficher(tcle, sizeof(tcle)/sizeof(double));
  printf("tverrou : ");
  afficher(tverrou, sizeof(tverrou)/sizeof(double));
  printf("tsolution : ");
  afficher(tsolution, sizeof(tsolution)/sizeof(double));
  return EXIT_SUCCESS;
}
