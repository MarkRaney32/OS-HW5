#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
#define NULL ((void*) 0)

int
main(int argc, char *argv[])
{
  int new_pages = 3;

  // sbrk returns a char* cast of uint sz (size of current process in bytes)
  // Also grows current proc mem by the parameter number of bytes.
  //char* sz = sbrk(new_pages * PGSIZE);
  char* sz = sbrk(0);
  sbrk(PGSIZE);

  // With the size of the current proccess (prior to expansion) we can set the
  // virtual address of this size to a value, then protect it?
  *sz = 1;

  mprotect(sz, 1);
  *sz += 1;
  munprotect(sz, 1);

  printf(1, "Gabbagool\n");

  exit();
}
