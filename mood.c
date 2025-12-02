#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Student{
    int id;
    char name[50];
    int mood;
};
struct Student class1[10];


void addStudent (int *count){ //加指针参数int*count，接收main里count的地址,才能对局部变量count进行修改
                              //若没有指针，函数只能拿到count的“值拷贝”,不能操作main里的count
    struct Student temp; //尝试创建一个临时储存输入值的数组
    //int id, mood;
    //char name[50];
    char choice='y';
    //在addStudent里：要操作的是 “main里的count”，但指针变量存的是地址，所以必须用*解引用，才能拿到地址对应的 “数字”
    
    do { //用do-while循环是因为想至少添加一个学生的信息，再询问是否继续
        if (*count>=10){
        printf("学生数组已满，无法继续添加！\n");
        break;
        }
        printf("请输入学生学号：");
        scanf("%d",&temp.id);
        while (getchar() != '\n');
        printf("请输入学生姓名：");
        scanf("%s",temp.name); //数组名代表了数组的起始地址,name即为&name[0]
        while (getchar() != '\n');
        printf("心情指数为：");
        scanf("%d",&temp.mood);
        while (getchar() != '\n'); //清空缓冲区，避免读取换行符
        
        //学号不重复添加
        bool same=false; //初始不重复
        for (int i=0;i<*count;i++){
            if (class1[i].id==temp.id){
                same=true; //如果添加到学号重复，same为真，
                break; //直接终止内层的for循环（不再继续遍历后面的学生），但不影响外层的do-while循环
            }
        }
        if (same) {
            printf("输入重复，请再次输入学生id\n");
            continue; //跳过外层do-while循环当前轮的剩余代码（心情校验、添加数组、询问是否继续）
                      //直接进入do-while的条件判断（choice=='y'||choice=='Y'）choice仍为'y'，条件成立，
                      //重新执行外层循环（让用户重新输入学号等信息）
        }             
        
        //输入心情指数要合法
        //printf("mood的实际值：%d\n", temp.mood);
        if (temp.mood<0||temp.mood>100) {
            printf("心情指数非法（0-100），添加失败！\n");
            continue; //跳过当前do-while循环的剩余代码（添加到数组,询问继续）,不改变choice='y',所以直接从头开始
                      //当if判断为非法时，阻止后续错误操作，并触发do-while循环重试
        }else {
        printf("判断为合法，继续添加\n");
        }
        
        class1[*count]=temp; //把temp里的临时数据，存入class1数组（整体赋值，不用逐个成员）
        //class1[*count].id=id;
        //strcpy(class1[*count].name,name);
        //class1[*count].mood=mood;    
        (*count)++;

        printf("是否继续添加？(y/n)：");
        scanf(" %c", &choice); //%c前的一个空格！
        while (getchar() != '\n');

    }while (choice=='y'||choice=='Y'); //大小写都可以，真·循环，假·退出do-while循环
    
    printf("\n已添加学生:\n");
    for (int i=0;i<*count;i++) {
        printf("%d的%s,心情指数为%d\n",
            class1[i].id,class1[i].name, class1[i].mood);
            //class1[i]是数组里的第i个学生，是 “仓库里的已有数据”，必须用数组下标访问
    }    
}


void queryMood(int *count){ //遍历完所有学生后，再判断是否找到（而不是遍历过程中反复判断）
    char choice;
    int id;
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
    if (!found){ //可以是if (found==0)但不是if (found=0):=是赋值用0把初始的1覆盖，表达式结果为0导致if条件永远为假，跳过printf
                 //if不关心括号里是 “赋值” 还是 “比较”，只关心「表达式最终的结果值」
        printf("未找到该学号的学生！\n");
    }
}


float calcAvgMood(int *count){
    printf("平均值函数已运行\n");
    if (*count==0){
        printf("暂无学生数据");
        return 0;
    }
    int total=0;
    float average;
    for (int i=0;i<*count;i++){
        total+=class1[i].mood;
    }
    average=(float)total/(*count); //强制数据类型转换，需要得到一个float型
    return average; //返回average，给main函数使用
}

void sortAndShow(int *count){
    if (*count<=1){
        printf("无需排序！");
        return;
    }
    for (int i=0;i<*count-1;i++){ //外层循环:排序一共进行n-1轮
        for (int j=0;j<*count-1-i;j++){ //内层循环:i为已经排好元素个数,后要比较(n-1-i)次           
            if (class1[j].mood<class1[j+1].mood){ //前面如果比后面小，交换
                struct Student temp=class1[j]; //以第一个元素为基准逐个和后面元素比较
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
    float avg = calcAvgMood(&count); // 用avg变量“接住”计算器递来的结果
    printf("同学们的心情指数平均值为：%.1f\n",avg);
    sortAndShow(&count);
}

    


    
