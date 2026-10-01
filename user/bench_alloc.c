// user/bench_alloc.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MB (1024 * 1024)
#define TEST_SIZE (32 * MB)

int
main(int argc, char *argv[])
{
  printf("=========================================\n");
  printf("  xv6 Allocation Benchmark (bench_alloc)\n");
  printf("=========================================\n");
  printf("Testing sbrk(%d MB) allocation latency...\n",
         TEST_SIZE / MB);

  uint start = rdcycle();

  char *p = sbrk(TEST_SIZE);

  uint end = rdcycle();

  if(p == (char*)-1){
    printf("sbrk failed\n");
    exit(1);
  }

  printf("sbrk() allocation elapsed: %d ticks\n",
         end - start);

  printf("Touching first byte of each 2MB chunk...\n");

  start = rdcycle();

  for(int i = 0; i < TEST_SIZE; i += 2 * MB){
    p[i] = 1;
  }

  end = rdcycle();

  printf("First-touch elapsed:       %d ticks\n",
         end - start);

  start = rdcycle();

  sbrk(-TEST_SIZE);

  end = rdcycle();

  printf("Deallocation elapsed:      %d ticks\n",
         end - start);

  printf("=========================================\n");

  exit(0);
}
