/*1,2,3,4组成没有重复数字的三位数，并统计数量*/
#include <stdio.h>
int main(){
    int b,s,g;
    int i;
    int count=0;
    printf("可以组成的数字各位不重复三位数为：\n");
    for (b=1;b<5;b++){
        for (s=1;s<5;s++){
            for (g=1;g<5;g++){
                i=100*b+10*s+g;
                if (b!=s&&s!=g&&g!=b){
                    printf("%d\n",i);
                    count++;
                }
            }
        }
    }
    printf("总数为：%d\n",count);
}