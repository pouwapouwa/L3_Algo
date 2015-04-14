#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct node_t * node;

struct node_t{
  int data;
  node right;
  node left;
};

typedef struct heap_t * heap;

struct heap_t{
  node root;
};

heap create_heap(){
  heap h = malloc(sizeof(*h));
  h->root = NULL;
  return h;
}

node create_node(int d){
  node n = malloc(sizeof(*n));
  n->right = NULL;
  n->left = NULL;
  n->data = d;
  return n;
}

void destroy_node(node n){
  if (n->left){
    destroy_node(n->left);}
  if (n->right){
    destroy_node(n->right);}
  free(n);
}

void destroy_heap(heap h){
  if (h->root){
    destroy_node(h->root);}
  free(h);
}

bool is_empty(heap h){
  if (h->root==NULL){
    return true;}
  return false;
}

int node_size(node n){
  if (!n){
    return 0;}
  return 1 + node_size(n->right) + node_size(n->left);
}

int heap_size(heap h){
  return node_size(h->root);
}

int heap_min(heap h){
  assert(!is_empty(h) && "Le tas est vide");
  return h->root->data;
}

int max(int a, int b){
  if (b>a){
    return b;}
  return a;
}

int node_max(node n){
  assert(n && "Le noeud n\'existe pas");
  if (n->right){
    if (n->left){
      return max(n->data,
		 max(node_max(n->right),
		     node_max(n->left)));
    }
    else{
      return max(n->data,
		 node_max(n->right));
    }
  }
  else{
    if (n->left){
      return max(n->data,
		 node_max(n->left));
    }
    else{
      return n->data;}
  }
}

int heap_max(heap h){
  assert(!is_empty(h) && "Le tas est vide");
  return node_max(h->root);
}

bool node_find_data(node n, int d){
  if (n==NULL){
    return false;}
  else if (d == n->data){
    return true;}
  else if (d < n->data){
    return false;
  }
  else{
    return node_find_data(n->right, d) || node_find_data(n->left,d);
  }
}

bool heap_find_data(heap h, int d){
  return node_find_data(h->root, d);
}

int node_height(node n){
  if (n==NULL){
    return 0;}
  return 1 + node_height(n->left) + node_height(n->right);
}

int heap_height(heap h){
  return node_height(h->root);
}

void swap(node a, node b){
   int t =a->data;
   a->data=b->data;
   b->data=t;
}

node node_merge(node n1, node n2){ //sans copie
  if (n1 == NULL){
    return n2;}
  else if (n2 == NULL){
    return n1;}
  else{
    if(n1->data < n2->data){
      node t = n1->right;
      n1->right=n2;
      n2->left=node_merge(n2->left,t);
      return n1;
    }
    else{ //n2->data < n1->data
      node t = n2->left;
      n2->left=n1;
      n1->right=node_merge(n1->right,t);
      return n2;
    }
  }
}

heap heap_merge(heap h1, heap h2){
  heap h = create_heap();
  h->root=node_merge(h1->root, h2->root);
  h1->root=NULL;
  h2->root=NULL;
  destroy_heap(h1);
  destroy_heap(h2);
  return h;
}

node sift_up(node n){
  if (n==NULL){
    return n;}
  assert(node_height(n->left) >= node_height(n->right) && "La branche droite est plus lourde que la branche gauche");
  if (node_height(n->left) > node_height(n->right)){
    assert(!(node_height(n->left->left) < node_height(n->left->right)) && "Branche gauche->droite plus lourde que gauche->gauche");
    n->left=sift_up(n->left);
    if (n->left!=NULL && n->left->data < n->data){
      swap(n->left, n);}
    return n;
  }
  else{
    n->right=sift_up(n->right);
    if (n->right!=NULL && n->right->data < n->data){
      swap(n->right, n);}
    return n;
  }
}

void node_insert(node n, int d){
  //assert(!(node_height(n->right) > node_height(n->left)) && "Arbre mal équilibré");
  
  if (node_height(n->right) < node_height(n->left)){
    if (n->right){
      node_insert(n->right, d);}
    else{
      n->right = create_node(d);
    }
  }
  else{
    if (n->left){
      node_insert(n->left,d);}
    else{
      n->left = create_node(d);
    }
  }
}

void heap_insert(heap h, int n){
  if (is_empty(h)){
      h->root=create_node(n);
    }
  else{
    node_insert(h->root, n);}
  h->root=sift_up(h->root);
}

node node_delete(node n, int d){
  if (n==NULL){
    return NULL;}
  else if (n->data == d){
    node u=node_merge(n->right, n->left);
    n->right=NULL;
    n->left=NULL;
    destroy_node(n);
    return u;
  }
  else if (n->data < d){
    if (node_find_data(n->right,d)){
      return node_delete(n->right, d);}
    else{
      return node_delete(n->left, d);}
  }
  else {
    return NULL;}
}

void print_node(node n){
  if (!n){
    printf("(vide)");
  }
  else{
    printf(" (");
    print_node(n->left);
    printf(" %d ", n->data);
    print_node(n->right);
    printf(") ");
  }
}

void print_heap(heap h){
  print_node(h->root);
}

void heap_delete(heap h, int d){
  if (is_empty(h)){
    return ;
  }
  else {
    h->root=node_delete(h->root,d);
  }
  print_heap(h);
  h->root=sift_up(h->root);
}

int main(){
  printf("création du tas\n");
  heap h = create_heap();
  print_heap(h);
  printf("\nInsertion de 8, 12, 0, 14, 3, 1, 2\n");
  heap_insert(h, 8);
  heap_insert(h, 12);
  heap_insert(h, 0); //
  heap_insert(h, 14);
  heap_insert(h, 3);
  heap_insert(h, 1);
  heap_insert(h, 2);
  printf("Affichage après ajout !\n");
  print_heap(h);

  printf("Suppression de 2!\n");
  heap_delete(h,2);
  print_heap(h);


  
  printf("\nDestrouctiounes ! \n");
  destroy_heap(h);
  return 0;
}
