#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
#define NULL ((void*) 0)

int
main(int argc, char *argv[])
{
  int *p;
  p = 0;
  printf(1, "%d\n", *p);

  exit();
}
