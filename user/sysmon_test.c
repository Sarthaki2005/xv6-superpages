#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include  "user/fcntl.h"
#define PAGE_SIZE 4096

int main(){
int i;

 printf("Testing hazardous syscalls..\n");
for( i=0;i<5;i++){
//Test kill syscall (sending signal 0 to self which is harmless)
kill(9999);
}
//Test unlink syscall
int fd=open("textfile.txt",O_CREATE | O_WRONLY);
if(fd>=0){
write(fd,"test",4);
close(fd);
for(i=0;i<5;i++ ){
//Exceed threshold 
unlink("testfile.txt");
}
}
exit(0);
}

