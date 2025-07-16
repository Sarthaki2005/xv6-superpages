#include<kernel/types.h>
#include<user/user.h>

int main(){
printf("Evilproc started");
fork();
fork();
char* arr=malloc(4096*10);
for(int i=0;i<4096*10;i++){
arr[i]=i%256;

}
unsigned int accessed=0;
pgaccess(arr,10,&accessed);
printf("pgaccess bitmap: 0x%x\n",accessed);
exec("ls",(char*[]){"ls",0});
exit(0);
}
