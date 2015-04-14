#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_t * node;
int * t;
int m, n;
int a,b;

struct node_t{
  int value;
  int group;
};

int min(int a, int b){
  return ( a < b ) ? a : b;
}

bool ask(int a, int b){
  return t[a]==t[b];
}

void link(int a, int b){
  int u = t[a];
  int v = t[b];
  if (v < u){
    for (int i =0; i<n*m; ++i){
      if (t[i]==u){
	t[i]=v;
      }
    }
  }
  else{
    for (int i =0; i<n*m; ++i){
      if (t[i]==v){
	t[i]=u;
      }
    }
  }
}

void print(int * t){
  printf("[");
  for (int i = 0; i<n*m; ++i){
    if (i%2==0 && i!=0){
      printf("\n");
    }
    printf("%d,",t[i]);
  }
  printf("]\n");
}

int main(int argc, char * argv[]){
  int op = 0;
  FILE * input = fopen(argv[1], "r");
  fscanf(input,"%d %d\n", &m, &n);
  printf("tableau de taille %d x %d\n\n",m,n);
  t= malloc(m*n*sizeof(*t));
  for (int i =0 ; i< m*n; ++i){
    t[i]=i;
  }
  fscanf(input,"%d %d\n", &a, &b);
  while ((fscanf(input,"%d %d\n", &a, &b))==2){
    if (a==-1){
      op = (op+1)%2;}
    else if (op){
      printf("Ask entre %d et %d : %s\n\n",a,b,ask(a,b)?"true":"false");}
    else{
      link(a,b);
      print(t);
      printf("Link entre %d et %d\n\n",a,b);
    }
  }
  printf("\nTableau Final:\n");
  print(t);
  fclose(input);
  free(t);
  return 0;
}
