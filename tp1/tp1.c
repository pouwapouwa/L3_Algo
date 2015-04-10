#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct cell{
  void * obj;
  struct cell * next;
}*cell_t;

typedef struct stack{
  cell_t head;
}*stack_t;

stack_t create_stack(){
  stack_t s= malloc(sizeof(*s));  /* (*s) au lieu de la structure, cela permet 
				     de modifier la structure de s si besoin */
  s->head = NULL;
  return s;
}

void* destroy_stack(stack_t s){
  assert(s && "erreur sur destroy_stack");
  assert(!s->head && "erreur sur destroy_stack2");
  free(s);
}

void* stack_push(stack_t s, void * obj){
  assert(s && "erreur sur push");
  cell_t c = malloc(sizeof(*c));
  c->obj = obj;
  c->next=s->head;
  s->head=c;
}

void* stack_pop(stack_t s){
  assert(s && "erreur sur pop");
  assert(s->head && "erreur sur pop");
  cell_t cel = s->head;
  s->head=s->head->next;
  free(cel);
}

int stack_empty(stack_t s){
  assert(s && "erreur sur stack_emty");
  return !s->head;
}

void* stack_top(stack_t s){
  assert(s && "erreur sur stack_top");
  assert(s->head);
  return s->head->obj;
}

/* int max_stack(stack_t s){ */
/*   assert(s && "erreur sur le max_stack"); */
/*   assert(s->head && "erreur sur le max_stack"); */
/*   int max= (int)s->head->obj; */
/*   cell_t cel = s->head; */
/*   while (cel){ */
/*     if ((int)cel->obj > max){ */
/*       max= (int)cel->obj; */
/*     } */
/*     cel=cel->next; */
/*   } */
/*   return max; */
/* } */

void main(){
  stack_t s=create_stack();
  stack_push(s,(void *)8);
  //printf("Max stack ? %d\n", max_stack(s));
  stack_push(s,(void *)9);
  //printf("Max stack ? %d\n", max_stack(s));
  printf("Stack vide ? %d\n", stack_empty(s));
  stack_pop(s);
  //printf("Max stack ? %d\n", max_stack(s));
  stack_pop(s);
  printf("Stack vide ? %d\n", stack_empty(s));
  destroy_stack(s);
}
