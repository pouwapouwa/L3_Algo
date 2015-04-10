#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct cellAVL_t * cellAVL;

struct cellAVL_t{
  int data;
  cellAVL left;
  cellAVL right;
};

cellAVL create_avl(int data){
  cellAVL c = malloc(sizeof(*c));
  c->data=data;
  c->right=NULL;
  c->left=NULL;
  return c;
}

void destroy_avl(cellAVL c){
  if (c->right!=NULL){
    destroy_avl(c->right);}
  if (c->left!=NULL){
    destroy_avl(c->left);}
  free(c);
}

cellAVL get_left_son(cellAVL c){
  return c->left;}

cellAVL get_right_son(cellAVL c){
  return c->right;}

void set_left_son(cellAVL c, cellAVL son){
  c->left=son;}

void set_right_son(cellAVL c, cellAVL son){
  c->right=son;}

int get_data_avl(cellAVL c){
  return c->data;}

void set_data_avl(cellAVL c, int data){
  c->data=data;
}

int get_max_data(cellAVL c){
  if(get_right_son(c)!=NULL){
    return get_max_data(get_right_son(c));}
  return get_data_avl(c);
}

int get_min_data(cellAVL c){
  if(get_left_son(c)!=NULL){
    return get_min_data(get_left_son(c));}
  return get_data_avl(c);
}

bool feuille(cellAVL c){
  return get_right_son(c)==NULL && get_left_son(c)==NULL;
}

void insert_data(cellAVL c, int data){
  if (data>get_data_avl(c)){
    if (get_right_son(c)==NULL){
      set_right_son(c,create_avl(data));}
    else{
      insert_data(get_right_son(c),data);}
  }
  if (data<get_data_avl(c)){
    if (get_left_son(c)==NULL){
      set_left_son(c,create_avl(data));}
    else{
      insert_data(get_left_son(c),data);}
  }
}

void delete_data(cellAVL c, int data){
  if (data>get_data_avl(c)){
    delete_data(get_right_son(c),data);
  }
  else if (data<get_data_avl(c)){
    delete_data(get_left_son(c),data);
  }
  else {
    if (feuille(c)){destroy_avl(c);}
    else {
      if (get_left_son(c)!=NULL){
	set_data_avl(c,get_max_data(get_left_son(c)));
	delete_data(get_left_son(c),get_max_data(c));}
      else {
	set_data_avl(c, get_min_data(get_right_son(c)));
	delete_data(get_right_son(c),get_min_data(c));}
    }
  } 
}

void print_avl(cellAVL c){
 if (c==NULL){
    printf("()");
  }
  else{
    printf("(");
    print_avl(get_left_son(c));
    printf(" %d ", get_data_avl(c));
    print_avl(get_right_son(c));
    printf(")");
  }
}

int main(){
  time_t t;
  srand((unsigned) time(&t));
  
  cellAVL c = create_avl(8);
  int a = rand()%30;
  int b = rand()%30;
  int d = rand()%30;
  printf("a=%d, b=%d, d=%d\n",a,b,d);
  printf("min = %d, max = %d\n", get_min_data(c), get_max_data(c));
  print_avl(c);
  printf("\ninsertion de a %d\n",a);
  insert_data(c,a);
  print_avl(c);
  printf("\ninsertion de b %d\n",b);
  insert_data(c,b);
  print_avl(c);
  printf("\ninsertion de d %d\n",d);
  insert_data(c,d);
  print_avl(c);
  printf("\nmin = %d, max = %d\n", get_min_data(c), get_max_data(c));
  //delete_data(c,b);
  //print_avl(c);
  //delete_data(c,a);
  //print_avl(c);
  destroy_avl(c);
  return 0;
}
