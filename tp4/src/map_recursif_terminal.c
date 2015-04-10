/* map.c */

#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct tree_t{
  tree left;
  tree right;
  void * object;
};

struct map_t{
  keyfunc f;
  tree root;
};

int max(int x, int y){
  if(x<y)
    return y;
  else
    return x;
}

tree tree_create(void *);
void tree_destroy(tree);
int tree_height(tree);
void * map_find_tree(tree, int, keyfunc);
void * map_insert_tree(tree, void *,keyfunc);
void * map_delete_tree(tree, int,keyfunc);
void * reequilibrage_tree(tree);
void * reequilibrage_map(map);
void remonter_info(tree,int,keyfunc);

/* create an empty map */
map map_create(keyfunc f){
  map m = malloc(sizeof(struct map_t));
  m->f=f;
  m->root=NULL;
  return m;
}

tree tree_create(void * obj){
  tree t=malloc(sizeof(struct tree_t));
  t->right=NULL;
  t->left=NULL;
  t->object=obj;
  return t;
}

/* destroy a map */
void map_destroy(map f){
  if (f->root != NULL){
    tree_destroy(f->root);}
  free(f);
}

void tree_destroy(tree t){
  if (t->left != NULL){
    tree_destroy(t->left);}
  if (t->right != NULL){
    tree_destroy(t->right);}
  free(t);
}

/* return the height of a map */
int map_height(map f){
  return tree_height(f->root);
}

/* find an object in the map and return it or NULL if not found */
void * map_find(map m, int key){
  return map_find_tree(m->root, key, m->f);
}

/* find an object in the map and return it or NULL if not found */
void * map_find_tree(tree t, int key, keyfunc k){
  if(t==NULL){
    return NULL;
  }
  if (k(t->object)<key){
    return map_find_tree(t->right,key,k);
  }
  else{
    if((k(t->object))>key){
      return map_find_tree(t->left,key,k);
    }
    else {
      return t->object;
    }
  }
  return NULL;
}

/* insert an object in a map and return it or NULL in case of
   failure (NULL object or object already inside the map) */
void * map_insert(map m, void * object){
  if (object == NULL){
    return NULL;
  }
  if (m->root==NULL){
    m->root=tree_create(object);
    return m->root->object;
  }
  return map_insert_tree(m->root,object,m->f);
}

/* insert an object in a map and return it or NULL in case of
   failure (NULL object or object already inside the map) */
void * map_insert_tree(tree t, void * object,keyfunc k){
  if (t==NULL){
    t=tree_create(object);
    return object;
  }
  if (k(t->object)<k(object)){
    if (t->right==NULL){
      t->right=tree_create(object);
      return t->right->object;
    }
    return map_insert_tree(t->right,object,k);
  }
  else{
    if (t->left==NULL){
      t->left=tree_create(object);
      return t->left->object;
    }
    return map_insert_tree(t->left,object,k);
  }
  return NULL;
}

/* delete an object from a map and return it or NULL if not found */
void * map_delete(map m, int key){
  if (m==NULL){
    return NULL;}
  return map_delete_tree(m->root,key,m->f);
}

void * map_delete_tree(tree t, int key,keyfunc k){
  if(t==NULL){
    return NULL;
  }
  if (k(t->object)<key){
    return map_delete_tree(t->right,key,k);
  }
  else{
    if((k(t->object))>key){
      return map_delete_tree(t->left,key,k);
    }

    else{
      void * u=t->object;
      if((t->left==NULL)&&(t->right==NULL)){ //Si feuille
	tree_destroy(t);
	printf("je detruit tout\n");
	return u;
      }
      remonter_info(t,key,k);
      return u;
    }
  }
return NULL;
}

tree trouver_minimal(tree t){
  if (t->left != NULL){
    return trouver_minimal(t->left);}
  return t;
}

tree trouver_maximal(tree t){
  if (t->right != NULL){
    return trouver_maximal(t->right);
  }
  return t;
}

void remonter_info(tree t,int key,keyfunc k){
  if (t->left){
    t->object=trouver_maximal(t->left)->object;
    t->left=NULL;
    map_delete_tree(t->left,k(t->object),k);
  }
  else{
    t->object=trouver_minimal(t->right)->object;
    t->right=NULL;
    map_delete_tree(t->right,k(t->object),k);
  }
}

/* void * reequilibrage_tree(tree t){ */
/*   if (t==NULL){ */
/*     return NULL;} */
/*   if (fabs(tree_height(t->left)-tree_height(right))<2){ */
/*     return NULL;} */
/*   if (tree_height(t->left)<tree_height(right)){ */
    
/*   } */
  
/* } */

/* void * reequilibrage_map(map m){ */
/*   return reequilibrage_tree(m->root); */
/* } */

//------------------AFFICHAGE D'ARBRE BINAIRE--------------

int tree_height(tree node)
{
  if(node == NULL) return 0;   /* the height of a void tree is 0. */
  return 1 + max(tree_height(node->left),tree_height(node->right));
}

void tree_traverse_and_mark(map m,
			    tree node,   /* current node */
			    int height,  /* tree height */
			    int * array, /* 2d array of marks */
			    int h,       /* node depth */
			    int w)       /* node lateral position */
{
  // traverse...
  if(node->left != NULL) 
    tree_traverse_and_mark(m,node->left,height,array,h+1,2*w);    
  if (node->right != NULL) 
    tree_traverse_and_mark(m,node->right,height,array,h+1,w*2+1);
  
  // mark...
  int width = (2 << (height-1)) - 1; /* width = 2^height - 1*/
  int j = h;
  int delta = (2 << (height-h-1)); /* delta =  2^(height-h) */
  int offset = delta/2-1;          /* offset = 2^(height-h-1) - 1*/
  int i = w*delta+offset; 
  int key = (*m->f)(node->object);   
  assert(key > 0); /* we assume it is > 0 */
  array[j*width+i] = key;
  // printf("mark: h=%d, w=%d, delta=%d, offset=%d\n", h, w, delta, offset); 
}

void map_dump(map m) 
{
  int height = tree_height(m->root);
  int width = (2 << (height-1)) - 1; /* width = 2^height - 1*/
  // printf("tree height: %d\n", height);
  // printf("tree width: %d\n", width);
  
  int array[height][width];
  int i, j;
  
  // reset array
  for(j = 0 ; j < height ; j++)
    for(i = 0 ; i < width ; i++) 
      array[j][i] = -1;
  
  // traverse tree and mark nodes
  if(m->root != NULL) 
    tree_traverse_and_mark(m,m->root,height,(int*)array,0,0);
  
  // dump array
  for(j = 0 ; j < height ; j++) {    
    printf("|");
    for(i = 0 ; i < width ; i++) {
      if(array[j][i] < 0) printf("  ");
      else printf("%.2d",array[j][i]);
    }
    printf("|\n");
  }
  
}
