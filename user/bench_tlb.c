// user/bench_tlb.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


// Helper: Formats 64-bit uint64 cycle counts for vanilla xv6 printf
//static void print_cycles(uint64 c) {
 // if (c >= 1000000000) {
   // printf("%d,%03d,%03d,%03d", 
     // (int)(c / 1000000000),
      //(int)((c % 1000000000) / 1000000),
      //(int)((c % 1000000) / 1000),
     // (int)(c % 1000));
 // } else if (c >= 1000000) {
   // printf("%d,%03d,%03d", 
     // (int)(c / 1000000),
      //(int)((c % 1000000) / 1000),
      //(int)(c % 1000));
//  } else if (c >= 1000) {
 //   printf("%d,%03d", (int)(c / 1000), (int)(c % 1000));
  //} else {
    //printf("%d", (int)c);
  //}
//}

#define MB (1024 * 1024)
#define BUFFER_SIZE (16 * MB)
#define STRIDE 4096       // Exactly one 4KB page boundary per access
#define NUM_ACCESSES 200000

int
main(int argc, char *argv[])
{
  printf("=========================================\n");
  printf("  xv6 TLB Thrashing Benchmark (bench_tlb) \n");
  printf("=========================================\n");
  printf("Allocating %d MB buffer via sbrk()...\n", BUFFER_SIZE / MB);

  char *buf = sbrk(BUFFER_SIZE);
  if(buf == (char*)-1){
    printf("sbrk failed\n");
    exit(1);
  }

  // Warm-up pass to fault in pages and initialize data
  for(int i = 0; i < BUFFER_SIZE; i += STRIDE){
    buf[i] = (char)(i & 0xFF);
  }

  printf("Running strided TLB access test (%d iterations)...\n", NUM_ACCESSES);

uint start_ticks = rdcycle();
  // volatile prevents GCC -O2 from optimizing away the loop
  volatile char dummy = 0;
  uint64 offset = 0;
  for(int i = 0; i < NUM_ACCESSES; i++){
    dummy += buf[offset];
    offset = (offset + STRIDE) % BUFFER_SIZE;
  }

uint end_ticks = rdcycle();
uint total_ticks = end_ticks - start_ticks;
printf("Total elapsed: %d ticks\n", total_ticks);

printf("Average access: %d ticks/access\n",
       total_ticks / NUM_ACCESSES);  printf("Dummy checksum: %d\n", (int)dummy);
  printf("=========================================\n");

  sbrk(-BUFFER_SIZE);
  exit(0);
}
