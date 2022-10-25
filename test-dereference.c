#include "types.h"
#include "stat.h"
#include "user.h"
#define NULL ((void*) 0)

int
main(int argc, char *argv[])
{

  int a, b, c; // some integers
  int *pi;     // a pointer to an integer

  a = 5;
  pi = &a; // pi points to a
  b = *pi; // b is now 5
  pi = NULL;
  c = *pi; // this is a NULL pointer dereference
  printf("%d\n", c);

  exit();
}
