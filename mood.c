#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Student{
    int id;
    char name[50];
    int mood;
};
struct Student class1[10];

void addStudent (int *count){//加指针参数int*count，接收main里count的地址,才能对局部变量count进行修改
    int id, mood;
    char name[50];
    char choice='y';
    //在 addStudent 里：要操作的是 “main里的 count”，但指针变量存的是地址，所以必须用*解引用，才能拿到地址对应的 “数字”
    do {
        if (*count>=10){
        printf("学生数组已满，无法继续添加！\n");
        break;
    }
        printf("请输入学生学号：");
        scanf("%d",&id);
        printf("请输入学生姓名：");
        scanf("%s",name);
        printf("心情指数为：");
        scanf("%d",&mood);

        while (getchar() != '\n');

        bool same=false;//初始不重复
        for (int i=0;i<*count;i++){
            if (class1[i].id==id){
                same=true;
                break;
            }
        }
        if (same) {
            printf("输入重复，请再次输入学生id\n");
            while (getchar() != '\n');
            continue;
        }
        if (mood < 0 || mood > 100) {
            printf("心情指数非法（0-100），添加失败！\n");
            while (getchar() != '\n');
            continue;
        }
        
        class1[*count].id=id;
        strcpy(class1[*count].name,name);
        class1[*count].mood=mood;    
        (*count)++;

        printf("是否继续添加？(y/n)：");
        scanf(" %c", &choice);
        while (getchar() != '\n');
    }while (choice=='y'||choice=='Y');
    printf("\n已添加学生:\n");
    for (int i=0;i<*count;i++) {
        printf("%d的%s,心情指数为%d\n",
            class1[i].id,class1[i].name, class1[i].mood);
    }    
}

void queryMood(int *count){//遍历完所有学生后，再判断是否找到（而不是遍历过程中反复判断）
    int choice,id;
    char name[50];
    printf("请输入要查找的学号：\n");
    scanf("%d",&id);
    int found=0;
    for (int i=0;i<*count;i++){
        if (class1[i].id==id){
            printf("已找到！\n");
            printf("学号：%d,姓名：%s,心情指数：%d\n",
            class1[i].id,class1[i].name, class1[i].mood);
            found=1;
            break;
        }
    }
    if (!found){
        printf("未找到该学号的学生！\n");
    }
}

float calcAvgMood(int *count){
    printf("=== 平均值函数已运行 ===\n");
    if (*count==0){
        printf("暂无学生数据");
        return 0;
    }
    int total=0;
    float average;
    for (int i=0;i<*count;i++){
        total+=class1[i].mood;
        average=(float)total/(*count);
    }
    return average;
}

void sortAndShow(int *count){
    if (*count<=1){
        printf("无需排序！");
        return;
    }
    for (int i=0;i<*count-1;i++){
        for (int j=0;j<*count-1;j++){
            if (class1[i].mood<class1[j].mood){
                struct Student temp=class1[i];
                class1[j]=class1[j+1];
                class1[j+1]=temp;
            }
        }
    }
    printf("按从大到小的顺序对心情指数进行排队：\n");
    for (int i=0;i<*count;i++){
        printf("姓名：%s,学号：%d,心情指数：%d\n",
            class1[i].name,class1[i].id,class1[i].mood);
    }   
}


int main(){
    int count=0;//定义的是局部变量，则函数要加int *count，通过指针参数接收地址修改count
    addStudent(&count);
    queryMood(&count);
    float avg = calcAvgMood(&count); // 用 avg 变量“接住”计算器递来的结果
    printf("同学们的心情指数平均值为：%.1f\n",avg);
    sortAndShow(&count);
}

    


    
