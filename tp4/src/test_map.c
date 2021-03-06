/* test_map.c */

#include "map.h"
#include "stdio.h"

int f(void * object) { return *((int*)object); }

int main (int argc, char* argv[]) 
{
  map m = map_create(f);  
  int a=10, b=6, c=13, d=19, e=14, f=20, g=11;
  map_insert(m, &a);
  map_insert(m, &b);
  map_insert(m, &c);
  map_insert(m, &d);
  map_insert(m, &e);
  map_insert(m, &f);
  map_insert(m, &g);
  
  map_dump(m);

  void * fb2 = map_find(m, b);
  printf("apres find\n");
  printf("find %d: %s\n", b, (fb2 != NULL)?"true":"false");

  /* delete a leaf */
  // map_delete(m,f); 
  /* delete a node with a single child */
  // ???

  /* delete a node with two children */
  // map_delete(m,d);
  
  map_delete(m,a);

  /* delete the root node */
  // map_delete(m,a); 

  map_dump(m);
  
  return 0;
  
}
