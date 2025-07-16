#include<kernel/types.h>
#include<user/user.h>
int main(){
int n=5;
int sum=0;
while(n){
sum+=n;
n--;
}
printf(" sum = %d",sum);
exit(0);
}
