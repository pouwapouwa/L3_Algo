#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

typedef struct splay_tree_t * splay_tree;

struct splay_tree_t{
  int data;
  splay_tree right;
  splay_tree left;
  int nb_left;
  int nb_right;
};

splay_tree create_tree(int data){
  splay_tree t =malloc(sizeof(*t));
  t->left=NULL;
  t->right=NULL;
  t->data=data;
  t->nb_right=0;
  t->nb_left=0;
  return t;
}

splay_tree copy_tree(splay_tree t1){
  splay_tree t2=create_tree(t1->data);
  t2->left=t1->left;
  t2->right=t1->right;
  t2->data=t1->data;
  t2->nb_left=t1->nb_left;
  t2->nb_right=t1->nb_right;
  if (t1->left !=NULL){
    t2->left=copy_tree(t1->left);}
  if (t1->right !=NULL){
    t2->right=copy_tree(t1->right);}
  return t2;
}

void destroy_tree(splay_tree t){
  if (t->right!=NULL){
    destroy_tree(t->right);}
  if (t->left!=NULL){
    destroy_tree(t->left);}
  if (t!=NULL){free(t);}
}

bool find_data_bool(splay_tree t, int data){
  assert(t!=NULL && "l'arbre est vide");
  if (data == t->data){ return true;}
  else if (data > t->data){
    if (t->right != NULL){
      return find_data_bool(t->right, data);}
    else { return false;
    }
  }
  else {
    if (t->left !=NULL){
      return find_data_bool(t->left, data);}
    else {
      return false;
    }
  }
}

splay_tree find_data(splay_tree t, int data){
  assert(t!=NULL && "l'arbre est vide");
  if (data == t->data){ return t;}
  else if (data > t->data){
    return find_data(t->right, data);}
  else {
    return find_data(t->left, data);}
}

splay_tree find_number_random(splay_tree t, int nb){
  if (t==NULL) {return NULL;}
  if (t->left != NULL && nb <= t->nb_left){ return find_number_random(t->left, nb);}
  else if (t->right != NULL && nb > (t->nb_right +1)){
    return find_number_random(t->right, nb-(t->nb_left)-1);
  }
  else{ //si nb = t->nb_left +1
    return t;
  }
}

splay_tree find_max(splay_tree t){
  assert(t!=NULL && "l'arbre est vide\n");
  if (t->right != NULL) {return find_max(t->right);}
  return t;
}

splay_tree rotation_left(splay_tree t){
  if (t->right==NULL){
    return t;}
  splay_tree v = t->right;
  t->nb_right=v->nb_left;
  t->right=v->left;
  v->left=t;
  v->nb_left=t->nb_right + t->nb_left +1;
  return v;
}

splay_tree rotation_right(splay_tree t){
  if (t->left==NULL){
    return t;}
  splay_tree v = t->left;
  t->nb_left=v->nb_right;
  t->left=v->right;
  v->right=t;
  v->nb_right=t->nb_left +t->nb_right +1;
  return v;
}

splay_tree rotation_to_root(splay_tree t, int data){
  assert(t!=NULL);
  if (t->data == data){ return t;}
  else if (data > t->data){
    if (t->right->data == data){
      return rotation_left(t);}
    else {
      splay_tree t_right = rotation_to_root(t->right,data);
      t->right=t_right;
      return rotation_left(t);
    }
  }
  else{
    if (t->left->data == data){
      return rotation_right(t);}
    else{
      splay_tree t_left=rotation_to_root(t->left,data);
      t->left=t_left;
      return rotation_right(t);
    }
  }
}

void insert_data2(splay_tree t, int data){
  assert(data!=t->data);
  if (data > t->data){
    if (t->right==NULL){
      t->right=create_tree(data);
      t->nb_right++;
    }
    else{
      insert_data2(t->right, data);}
  }
  else {
    if (t->left==NULL){
      t->left=create_tree(data);
      t->nb_left++;
    }
    else {
      insert_data2(t->left, data);}
  }
}

splay_tree insert_data(splay_tree t, int data){
  insert_data2(t, data);
  return rotation_to_root(t, data);
}

splay_tree delete_data(splay_tree t, int data){
  if (t->right == NULL && t->left == NULL){ destroy_tree(t); return NULL;}
  splay_tree u = rotation_to_root(t,data);
  splay_tree v = u->left;
  splay_tree w = u->right;

  if (v !=NULL){
    v=rotation_to_root(v,(find_max(v))->data);
    v->right=w;
    if (w==NULL){ v->nb_right=0;}
    else{ v->nb_right=w->nb_right + w->nb_left+1;}
    //free(t);
    return v;
  }
  else{
    //free(t);
    return w;
  }
}

void print_tree(splay_tree t){
  if (t==NULL){
    printf("()");
  }
  else{
    printf("(");
    print_tree(t->left);
    printf(" %d ", t->data);
    print_tree(t->right);
    printf(")");
  }
}

void test_insert(splay_tree* t, int data){
  print_tree(*t);
  printf("\n");
  *t =insert_data(*t, data);
  print_tree(*t);
  printf("\n");
}

void test_delete(splay_tree* t, int data){
  print_tree(*t);
  printf("\n");
  *t =delete_data(*t, data);
  print_tree(*t);
  printf("\n");
}

int mon_random(int arrivee){
  return rand()%arrivee;}

int random_number(splay_tree t){
  if (t->nb_right+t->nb_left == 0){
    return t->data;
  }
  return (int)(find_number_random(t, mon_random(t->nb_right + t->nb_left)))->data;
}

void swap(int * a, int * b){
  int c = *a;
  *a=*b;
  *b=c;
}

void print_tableau(int* t[],int taille){
  printf("\n[");
  for (int i = 0; i<taille-1; ++i){
    printf("%d,",t[i]);
  }
  printf("%d]\n",t[taille-1]);
}

int main(){
  time_t t2;
  srand((unsigned) time(&t2));
  int nb_node = rand()%10 ; //Pour avoir entre 1 et 10 opérations (entre 0 et 9 plus la racine)
  int taille = 50;

  int t[taille];
  for (int i = 0; i<taille; i++){
    t[i]=i;}

  printf("Tableau avant shuffle\n");
  print_tableau(t, taille);
  
  //shuffle();

  for (int i = 0; i <taille; i++){
    swap(&t[i], &t[i+rand()%(taille-i)]);
  }

  printf("Tableau après shuffle\n");
  print_tableau(t, taille);
  
  splay_tree random_tree = create_tree(t[0]);

  for (int i =1; i<nb_node; i++){
    random_tree=insert_data(random_tree,t[i]);
  }
  
  /* for (int i=0; i<nb_node; i++){ */
  /*   u =rand()%50; */
  /*   if (!find_data_bool(random_tree, u)){ */
  /* 	random_tree=insert_data(random_tree,u);} */
  /*   else { */
  /*     --i; */
  /*   } */
  /* } */
  
  printf("random tree:");
  print_tree(random_tree);
  splay_tree random_tree2 = copy_tree(random_tree);
  printf("\nrandom tree2:");
  print_tree(random_tree2);
  
  int r=random_number(random_tree);
  splay_tree tree = create_tree(r);
  random_tree = delete_data(random_tree, r);
  printf("\ntree : ");
  print_tree(tree);
  printf("\nrandom tree après création de l'arbre : ");
  print_tree(random_tree);
  printf("\n");

  while (random_tree != NULL){
    
    printf("\nle sommet est %d et à %d données à gauche et %d à droite\n", tree->data, tree->nb_left, tree->nb_right);
    r=random_number(random_tree);
    print_tree(tree);
    printf("\nJ'insère %d\n", r);
    tree = insert_data(tree,r);
    print_tree(tree);
    random_tree = delete_data(random_tree, r);
    printf("\nrandom tree:\n");
    print_tree(random_tree);
    printf("\n");
  }
  
  printf("\n\nNous avons donc random tree:\n");
  print_tree(random_tree);
  printf("\nRandom tree2:\n");
  print_tree(random_tree2);
  printf("\nEt notre arbre courant :\n");
  print_tree(tree);

  printf("\n\nOn passe à la suppression maintenant ! \n\n");

  while (random_tree2 != NULL){
    
    printf("\nle sommet est %d et à %d données à gauche et %d à droite\n", tree->data, tree->nb_left, tree->nb_right);
    r=random_number(random_tree2);
    print_tree(tree);
    printf("\nJe supprime %d\n", r);
    tree = delete_data(tree,r);
    print_tree(tree);
    random_tree2 = delete_data(random_tree2, r);
    printf("\nrandom tree2:\n");
    print_tree(random_tree2);
    printf("\n");
  }

  printf("%d\n", nb_node);
  printf("\n\nyoupi ça marche !\n");
  return 0;
}
