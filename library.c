#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> //用于日期计算


int MAX_BOOKS=100;
int MAX_BORROW=5;
int LIMITED_DAY=30;

struct Book {
    int book_id;
    char book_name[50];
    char author[50];
    int stock;
};
struct Book book[100];
struct History {
    int borrower_id;
    int isborrowed_id;
    time_t date;
    bool is_returned;
};
struct History history[5];

int book_count=0;
int borrow_count=0;

void introBooks(){
    char book_name[50];
    char author[50];
    int book_id;
    int stock;
    bool same=0; //初始是不同的，0表示False
    char choice='y';
    do {
        if (book_count>=MAX_BOOKS){
            printf("图书馆已达最大存书量上限！\n");
            return;
        }
        printf("请输入您引进的书的名字：\n");
        scanf("%s",book_name);
        printf("该书的作者是:\n");
        scanf("%s",author);
        printf("书编号:\n");
        scanf("%d",&book_id);
        printf("该书的库存数量为：\n");
        scanf("%d",&stock);

        for (int i=0;i<book_count;i++){
            if (book[i].book_id==book_id){
                same=1;
                break;
            }
        }
        if (same==1){
            printf("已存过该书！请换一本书！\n");
            continue;
        }
        book[book_count].book_id=book_id;
        strcpy(book[book_count].book_name,book_name);
        strcpy(book[book_count].author,author);
        book[book_count].stock=stock;
        book_count++;
        printf("书籍添加成功！\n");

        printf("是否要继续添加书籍：\n");
        scanf(" %c",&choice);
    }while (choice=='y'||choice=='Y');
    printf("书籍添加完毕！\n");
}


void borrowBooks(){
    int wantid;
    int stuid;
    char borrow_choice='y';
    int current_borrows=0;

    printf("请输入您的学号：\n");
    scanf("%d",&stuid);

    for (int i=0;i<borrow_count;i++){
        if (history[i].borrower_id==stuid && !history[i].is_returned){
            current_borrows++;
        }
    }
    printf("您当前已借%d/%d本书！\n",current_borrows,MAX_BORROW);
    if (current_borrows>=MAX_BORROW){
            printf("您已达到借书上限，不能再借了！\n");
            return;
        }

    do {
        bool found=false;
        bool can_borrow=false;
        int index=-1;
        printf("请输入您要借的书的编号：\n");
        scanf("%d",&wantid);
        for (int i=0;i<book_count;i++){
            if (book[i].book_id==wantid){
                found=true;
                index=i;
                if (book[i].stock>0){
                    printf("该书可借！\n");
                    can_borrow=true;
                }
                break;
            }
        }
        if (!found){
            printf("没有找到编号为%d的书！\n",wantid);
        }
        else if (!can_borrow){
            printf("%s库存不足，无法借阅！\n",book[index].book_name);
        }
        else{
            history[borrow_count].isborrowed_id = wantid;
            history[borrow_count].borrower_id = stuid;
            history[borrow_count].date = time(NULL);
            history[borrow_count].is_returned = false;
            borrow_count++;

            book[index].stock--;
            current_borrows++;
            printf("借书成功！已借%d/%d本书。\n",current_borrows,MAX_BORROW);
        }
        if (current_borrows>=MAX_BORROW){
            printf("您已达借阅上限！\n");
            break;
        }
        printf("还要借书吗？\n");
        scanf(" %c",&borrow_choice);

    }while (borrow_choice=='y'||borrow_choice=='Y');
    printf("借书操作结束！\n");
}


struct Book* idGetBook(int isborrowed_id){ //根据书号，返回对应book结构体指针
    for (int i=0;i<book_count;i++){
        if (book[i].book_id==isborrowed_id){
            return &book[i]; //返回该书籍的地址
        }
    }
    return NULL;
}


void queryBorrow(){
    int stuid;
    printf("请输入要查询的学号：\n");
    scanf("%d",&stuid);
    printf("=====学号%d的借阅记录如下=====\n",stuid);
    int stu_borrow_count=0;
    int found=0;
    for (int i=0;i<borrow_count;i++){
        if (history[i].borrower_id==stuid){
            found++;
            printf("记录%d:\n",found);
            printf("书籍编号:%d\n",history[i].isborrowed_id);

            struct Book* p_book=idGetBook(history[i].isborrowed_id);
            if (p_book!=NULL){
                printf("书籍:%s\n",p_book->book_name);
            }
            printf("借阅时间：%s",ctime(&history[i].date));
            printf("状态:%s\n",history[i].is_returned?"已归还":"未归还");

            if (!history[i].is_returned){
                stu_borrow_count++;
            }
        } 
    }

    if (found==0){
        printf("未找到该学生的借阅记录！\n");
    }
    else {
        printf("统计：\n");
        printf("总借阅记录%d条\n",found);
        printf("当前未归还%d本\n",stu_borrow_count);
        printf("还能借%d本\n",MAX_BORROW-stu_borrow_count);
    }
}

void returnBooks(){
    int stuid;
    char wannareturn;
    int returncount=0;
    printf("请输入您的学号：\n");
    scanf("%d",&stuid);

        printf("您当前未归还的书籍：\n");
    int unreturned_count = 0;
    int unreturned_ids[5];
    
    for (int i=0;i<borrow_count;i++) {
        if (history[i].borrower_id==stuid && !history[i].is_returned) {
            struct Book* p_book=idGetBook(history[i].isborrowed_id);
            if (p_book != NULL) {
                printf("%d.《%s》(书号:%d)\n", 
                       unreturned_count+1, 
                       p_book->book_name, 
                       history[i].isborrowed_id);
                unreturned_ids[unreturned_count] = history[i].isborrowed_id;
                unreturned_count++;
            }
        }
    }
    
    if (unreturned_count == 0) {
        printf("您没有待归还的书籍！\n");
        return;
    }

    printf("您现在要还书吗？\n");
    scanf(" %c",&wannareturn);
    if (wannareturn=='y'||wannareturn=='Y'){
        for (int i=0;i<borrow_count;i++){
            if (history[i].borrower_id==stuid && !history[i].is_returned){
                struct Book* p_book=idGetBook(history[i].isborrowed_id);
                if (p_book!=NULL){
                    p_book->stock++;
                }
                history[i].is_returned=true;
            }
    
        }
        printf("已成功归还%d本书！\n",returncount);
    }
    else {
        int first_index=-1;
        for (int i=0;i<borrow_count;i++){
            if (history[i].borrower_id==stuid && !history[i].is_returned){
                first_index=i;
                break;
            }
        }
        if (first_index!=-1){
            time_t borrow_time=history[0].date;
            time_t return_time=borrow_time+LIMITED_DAY*86400;
            struct tm* deadline_time=localtime(&return_time);
            printf("您选择暂不还书~ \n");
            printf("借阅期限：%d天\n", LIMITED_DAY);
            printf("请在 %d年%d月%d日 前归还书籍，避免逾期！\n",
                deadline_time->tm_year+1900,
                deadline_time->tm_mon+1,
                deadline_time->tm_mday);
        }
    }
}


void saveBooks(){
    //FILE*是C语言的文件指针
    FILE* fp=fopen("books.txt","w");
    if (fp==NULL){ //检查文件是否打开成功！
        printf("文件打开失败！\n");
        return;
    }
    //写入数据
    for (int i=0;i<book_count;i++){
        fprintf(fp,"%d,%s,%s,%d\n",
                book[i].book_id,
                book[i].book_name,
                book[i].author,
                book[i].stock);
    }
    //关闭文件！
    fclose(fp);
    printf("书籍信息已保存到books.txt!\n");
}


void loadBooks(){
    //打开文件，“r”只读模式
    FILE* fp=fopen("books.txt","r");
    if (fp==NULL){
        printf("没找到保存的书籍文件，将新建！\n");
        return;
    }
    struct Book temp;
    while(fscanf(fp,"%d,%[^,],%[^,],%d\n",
                &temp.book_id,
                &temp.book_name,
                &temp.author,
                &temp.stock)!=EOF){
        book[book_count]=temp;
        book_count++;
    }

    //关闭文件
    fclose(fp);
    printf("成功加载%d本图书信息！\n",book_count);
}


void saveHistory(){
    FILE* fp=fopen("history.txt","w");
    if (fp==NULL) return;
    for (int i=0;i<borrow_count;i++){
        fprintf(fp,"%d,%d,%lld,%d\n",
                history[i].borrower_id,
                history[i].isborrowed_id,
                (long long)history[i].date, //time_t转long long避免溢出
                history[i].is_returned);
    }
    fclose(fp);
    printf("已保存%d条借阅记录\n",borrow_count);
}


void loadHistory(){
    FILE* fp=fopen("history.txt","r");
    if (fp==NULL) return;
    struct History temp;
    long long date;
    while (fscanf(fp,"%d,%d,%lld,%d\n",
            &temp.borrower_id,
            &temp.isborrowed_id,
            &date,
            &temp.is_returned)!=EOF){
        temp.date=(time_t)date;
        history[borrow_count]=temp;
        borrow_count++;
    }
    fclose(fp);
}


int main(){
    //程序启动，加载保存的数据
    loadBooks();
    loadHistory();

    introBooks();
    borrowBooks();
    queryBorrow();
    returnBooks();

    //退出程序前，保存数据
    saveBooks();
    saveHistory();
    return 0;
}