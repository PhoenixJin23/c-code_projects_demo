/*水仙花数：一个N位数，其各位数字的N次方之和等于该数本身
打印出100-999之间所有的“水仙花数”*/
#include <stdio.h>
int main(){
    int i;
    for (i=100;i<1000;i++){
        int b=i/100;
        int s=(i/10)%10;
        int g=i%10;
        if (b*b*b+s*s*s+g*g*g==i){
            printf("%d是水仙花数\n",i);
        }
    }
}
/*出现问题：定义的b、s、g写在了for循环外面，
此时i还未开始遍历，导致b、s、g全为无效值；
解决：将b、s、g定义在for循环内，遍历i时，每次循环都重新计算b、s、g*/