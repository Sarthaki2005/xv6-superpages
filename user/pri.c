#include<kernel/types.h>
#include<user/user.h>
void sieve(int fd){
int p;
if(read(fd,&p,sizeof(int))!=sizeof(int)){
exit(0);
}
printf("prime %d\n",p);
int p0[2];
pipe(p0);
if(fork()==0){
close(p0[1]);
close(fd);
sieve(p0[0]);
close(p0[0]);
exit(0);
}
else{
int num;

close(p0[0]);
while(read(fd,&num,sizeof(int))==sizeof(int)){
if(num%p!=0){
write(p0[1],&num,sizeof(int));
}
}

close(fd);
close(p0[1]);
wait(0);
}
exit(0);
}
int main(){
int p[2];
pipe(p);
if(fork()==0){
close(p[1]);
sieve(p[0]);
close(p[0]);
exit(0);
}
else{
close(p[0]);
for(int i=2;i<=35;i++){
write(p[1],&i,sizeof(int));

}
close(p[1]);
wait(0);
}
exit(0);
}
