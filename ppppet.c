#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Pet{
    int id;
    char name[50];
    int health;
};
struct Pet pet[10];
int count=0;


/*将用户输入的宠物数据经过去重、判断合法性后存在数组里*/
void addPet(){
    int ip_id;
    char ip_name[50];
    int ip_health;
    char choice='y';
    do{
        if (count>=10){
            printf("该数组已满，请新建新的数组！");
            return;
        }
        printf("请输入宠物编号：");
        scanf("%d",&ip_id); 
        while (getchar()!='\n');
        printf("请输入宠物名字：");
        scanf("%s",ip_name); 
        while (getchar()!='\n');
        printf("请输入宠物健康指数：");
        scanf("%d",&ip_health);
        while (getchar()!='\n');

        bool same=false;
        for (int i=0;i<count;i++){
            if (pet[i].id==ip_id){ //ip_id是临时的变量，用于和已存宠物pet[i].id对比
                same=true;
                break;
            }
        }
        if (same==true){
            printf("宠物编号重复，请重新添加！");
            continue; //continue：输入重复编号后，跳出这次循环，不再将该组数据存入数组，而允许从头开始重新输入
        }             //如果没有continue，不合规的数据也会被存入数组，下同

        if (ip_health>100||ip_health<0){
            printf("请输入大于0小于100的数！");
            continue;
        }

        pet[count].id=ip_id; 
        strcpy(pet[count].name,ip_name);
        pet[count].health=ip_health;
        
        count++;

        printf("是否要继续添加宠物信息：");
        scanf(" %c",&choice);
    }while (choice=='y'||choice=='Y');
    printf("添加完毕！\n");
    for (int j=0;j<count;j++){
        printf("宠物编号为：%d\n",pet[j].id);
        printf("宠物名字为:%s\n",pet[j].name);
        printf("宠物健康指数为：%d\n",pet[j].health);
    }
}


/*没找到：让用户选y/n，选y就继续循环查，选n就退出；
  找到：直接把choice改成n，跳过询问步骤，循环条件不满足→直接退出。*/
void healthRequest(){
    int request_id;
    bool found=false; //使用found标记法，初始未找到
    char choice='y'; //控制是否重新查询，初始为'y'，保证循环至少执行一次
    do {
        found=false; 
        printf("请输入您要查询的宠物编号：\n");
        scanf("%d",&request_id); //使用临时变量，储存当次用户输入的数据
        for (int i=0;i<count;i++){
            if (pet[i].id==request_id){ //左：数组中存储的数据；右：用户输入的数据
                found=true; //标记为“已找到”
                printf("查询到！");
                printf("%d号的%s,健康指数为%d\n",pet[i].id,pet[i].name,pet[i].health);
                break; //找到直接跳出for循环
            }
        }
        if (found==false){ //置于for循环外面，否则会多次打印“未找到宠物”的提示
            printf("没找到宠物！是否要重新查询：\n");
            scanf(" %c",&choice);
        }
        else {
            choice='n'; //
        }
    }while (choice=='y'||choice=='Y');
}


float calAvgHealth(){
    int total=0; //初始化！初始化！！初始化！！！手动为0！！！！
    float average=0.0; //否则值都是随机的！！！！！
    if (count>0){
        for (int j=0;j<count;j++){
            total+=pet[j].health;
        }
        average=(float)total/(count);
        return average;
    }   
}


void sortHealth(){
    if (count<=1){
        printf("只有一组数据，不用排序！");
        return;
    }
    for (int i=0;i<count-1;i++){
        for (int j=0;j<count-i-1;j++){
            if (pet[j].health>pet[j+1].health){
                struct Pet temp=pet[j];
                pet[j]=pet[j+1];
                pet[j+1]=temp;
            }
        }
    }
    printf("宠物健康指数按从小到大顺序排列为：\n");
    for (int i=0;i<count;i++){
        printf("%d的%s,健康指数为%d\n",pet[i].id,pet[i].name,pet[i].health);
    }
}


int main(){
    addPet();
    healthRequest();
    float avg=calAvgHealth(); //需要用一个变量接住函数传来的值
    if (count>0){
        printf("宠物数据库中宠物的平均健康指数为:%.1f\n",avg);
    }
    sortHealth();
}