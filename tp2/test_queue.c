/* test_queue.c */

#include "queue.h"
#include "stdio.h"

int main (int argc, char* argv[]) 
{
  queue p=queue_create();
  int a=1, b=2, c=3;
  printf("push %d\n", a);
  queue_push(p, &a);
  printf("push %d\n", b);
  queue_push(p, &b);
  printf("push %d\n", c);
  queue_push(p, &c);

  void * front = queue_front(p);
  printf("front = %d\n", *((int*)front)); // = 1

  printf("pop\n");
  queue_pop(p);
  front = queue_front(p);
  printf("front = %d\n", *((int*)front)); // = 2

  printf("pop\n");
  queue_pop(p);
  front = queue_front(p);
  printf("front = %d\n", *((int*)front)); // = 3

  queue_destroy(p);
  return 0;  
}
