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

int node_height(node n){
  if (n==NULL){
    return 0;}
  return 1 + node_height(n->left) + node_height(n->right);
}

int heap_height(heap h){
  return node_height(h->root);
}

void swap(node a, node b){
  node c = a;
  b = a;
  a = c;
}

void sift_up(node n){
  if (n==NULL){
    return ;}
  assert(node_height(n->left) >= node_height(n->right) && "La branche droite est plus lourde que la branche gauche");
  if (node_height(n->left) > node_height(n->right)){
    assert(!(node_height(n->left->left) < node_height(n->left->right)) && "Branche gauche->droite plus lourde que gauche->gauche");
    sift_up(n->left);
    if (n->left!=NULL && n->left->data < n->data){
      swap(n, n->left);}
    return ;
  }
  else{
    sift_up(n->right);
    if (n->right!=NULL && n->right->data < n->data){
      swap(n, n->right);}
    return ;
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
  sift_up(h->root);
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

int main(){
  printf("création du tas\n");
  heap h = create_heap();
  print_heap(h);
  printf("\nInsertion de 8, 12, 0, 14, 3, 1, 2\n");
  heap_insert(h, 8);
  print_heap(h);
  printf("\n");
  heap_insert(h, 12);
  print_heap(h);
  printf("\n");
  heap_insert(h, 0);
  print_heap(h);
  printf("\n");
  heap_insert(h, 14);
  print_heap(h);
  printf("\n");
  heap_insert(h, 3);
  print_heap(h);
  printf("\n");
  heap_insert(h, 1);
  print_heap(h);
  printf("\n");
  heap_insert(h, 2);

  printf("Affichage après ajout !\n");
  print_heap(h);
  printf("\nDestrouctiounes ! \n");
  destroy_heap(h);
  return 0;
}
