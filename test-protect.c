#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

void increment_while_protected();
void protect_multiple_pages();
void protect_too_many_pages();
void fail_on_offset();
void fail_on_len_0();

int
main(int argc, char *argv[])
{

  increment_while_protected();
  protect_multiple_pages();
  protect_too_many_pages();
  fail_on_offset();
  fail_on_len_0();

  exit();
}

void increment_while_protected() {

  // sbrk returns a char* cast of uint sz (size of current process in bytes)
  // Also grows current proc mem by the parameter number of bytes.
  char* sz = sbrk(0);

  // grow proc mem by one page's worth of bytes
  sbrk(PGSIZE);

  // With the size of the current proccess (prior to expansion) we can set the
  // virtual address of this size to a value.
  *sz = 1;

  if(fork() == 0) {
    // Trying to increment while protected
    // Program should trap & exit prior to print statement
    printf(1, "\n\nA trap should occur here: \n\n");
    mprotect(sz, 1);
    *sz += 1;
    munprotect(sz, 1);
    printf(1, "This should not print!\n");
    exit();
  } else {
    wait();
    printf(1, "\n\nTest 1.) Increment while protected   : Passed!\n");
  }
}

void protect_multiple_pages() {
  int new_pages = 3;
  char* sz = sbrk(0);
  sbrk(PGSIZE * new_pages);

  *sz = 1;

  int prot_return = mprotect(sz, new_pages);
  int unprot_return = munprotect(sz, new_pages);

  // There should be no issue with quickly setting to read-only,
  // Then back to normal
  if (prot_return == 0 && unprot_return == 0){
    printf(1, "Test 2.) Basic protection            : Passed!\n");
  } else {
    printf(1, "Test 2.) Basic protection            : Failed!\n");
    exit();
  }

}

void protect_too_many_pages() {
  int new_pages = 3;
  char* sz = sbrk(0);
  sbrk(PGSIZE * new_pages);

  *sz = 1;

  int prot_return = mprotect(sz, new_pages+1);
  int unprot_return = munprotect(sz, new_pages+1);

  // We are trying to protect pages that aren't there
  // yet, this should cause an error.
  if (prot_return == -1 && unprot_return == -1){
    printf(1, "Test 3.) Too many pages              : Passed!\n");
  } else {
    printf(1, "Test 3.) Too many pages              : Failed!\n");
    exit();
  }

}

void fail_on_offset() {
  char* sz = sbrk(0);
  sbrk(PGSIZE);

  *(sz+1) = 1;

  int prot_return = mprotect(sz+1, 1);
  int unprot_return = munprotect(sz+1, 1);

  // We are trying to protect an address that is not aligned
  // Thus we want it to fail
  if (prot_return == -1 && unprot_return == -1){
    printf(1, "Test 4.) Fail on offset              : Passed!\n");
  } else {
    printf(1, "Test 4.) Fail on offset              : Failed!\n");
    exit();
  }

}

void fail_on_len_0() {
  char* sz = sbrk(0);
  sbrk(PGSIZE);

  *sz = 1;

  int prot_return = mprotect(sz, 0);
  int unprot_return = munprotect(sz, 0);

  // We are trying to protect with len = 0, thus we want
  // it to fail
  if (prot_return == -1 && unprot_return == -1){
    printf(1, "Test 5.) Fail on len 0               : Passed!\n");
  } else {
    printf(1, "Test 5.) Fail on len 0               : Failed!\n");
    exit();
  }
}
