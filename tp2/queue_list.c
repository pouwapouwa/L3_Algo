#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

typedef struct queue{
  struct cell* tail;
}*queue_t;

typedef struct cell{
  void * obj;
  struct cell* next;  
}*cell_t;

/* create an empty queue */
queue_t queue_create(void){
  queue_t q=malloc(sizeof(*q));
  q->tail=NULL;
  return q;
}

/* create an empty queue */
void queue_destroy(queue s){
  assert(s && "erreur queue_destroy1");
  assert(s->tail && "erreur queue_destroy2");
  free(s);
}

/* return true if and only if the queue is empty */
int queue_empty(queue s){
  assert(s);
  assert(s->tail);
  return !s->tail;
}

/* push an object on the back of the queue */
void queue_push(queue s, void *object){
  assert(s);
  cell_t cel = malloc(sizeof(*cel));
  cel->next=s->tail;
  s->tail=s;
}


/* return the front element of the queue.
   The queue must not be empty (as reported by queue_empty()) */
void * queue_front(queue s){
  
}

/* pop the front element off of the queue.
   The queue must not be empty (as reported by queue_empty()) */
void queue_pop(queue s){
  assert(s);
  assert(!queue_empty(s));
  cell_t cell_supp = s->tail;
  cell_t cell_before_supp = s->tail;
  while(cell_supp->next){
    cell_before_supp=cell_supp;
    cell_supp=cell_supp->next;
  }
  /* A continuer */
}
