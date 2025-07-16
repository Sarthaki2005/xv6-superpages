#include<kernel/types.h>
#include<user/user.h>
int main(int argc,char* argv[]){
int p0[2],p1[2];
char buf[]={'x'};
pipe(p0);
pipe(p1);
if(fork()==0){
close(p0[1]);
close(p1[0]);
if(read(p0[0],buf,1)==1){
printf("%d : received ping\n",getpid());
write(p1[1],buf,1);
close(p0[0]);
close(p1[1]);
exit(0);
}
}
else{
close(p0[0]);
close(p1[1]);
write(p0[1],buf,1);
wait(0);
if(read(p1[0],buf,1)==1){
printf("%d : received pong\n",getpid());
}
close(p0[1]);
close(p1[0]);

}
exit(0);
}
