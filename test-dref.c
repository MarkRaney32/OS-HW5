#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
#define NULL ((void*) 0)

int
main(int argc, char *argv[])
{
  printf(1, "This test is successful if a trap occurs:\n\n");

  uint *p = (uint*)0;
  printf(1, "%d\n", *p);
  printf(1, "Test failed\n");

  exit();
}
