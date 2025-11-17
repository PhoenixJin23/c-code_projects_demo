/*一个整数，加上100是完全平方数，再加上168又是一个完全平方数，求该数*/
#include <stdio.h>
int main(){
    int i,j,a,b,x;
    for (i=1;i*i<=168;i++){
        if (168%i==0) {
            j=168/i;
            // 必须满足i和j同奇偶
            if ((i+j)%2==0) {
                a=(j-i)/2;
                b=(i+j)/2;
                x=a*a-100; // 由x+100=a²推导
                printf("该整数是：%d\n", x);
            }
        }
    }
    return 0;
}
/*困难：数学过程*/