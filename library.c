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
    printf("请输入您的学号：\n");
    scanf("%d",&stuid);
    do {
        bool found=false;
        if (borrow_count>=MAX_BORROW){
            printf("您已达到最大借书上限！");
            return;
        }
        printf("请输入您要借的书的编号：\n");
        scanf("%d",&wantid);
        for (int i=0;i<book_count;i++){
            if (book[i].book_id==wantid){
                if (book[i].stock>0){
                    printf("该书可借！\n");
                    found=true;

                    history[borrow_count].isborrowed_id = wantid;
                    history[borrow_count].borrower_id = stuid;
                    history[borrow_count].date = time(NULL);
                    history[borrow_count].is_returned = false;
                    borrow_count++;

                    printf("借书成功！\n");
                    book[i].stock--;

                }else {
                    printf("该书已被借出！\n");
                    found=true;
                }
                break;
            }
        }
        if (!found){
            printf("没找到该书！\n");
        }
        printf("还要借书吗？\n");
        scanf(" %c",&borrow_choice);

    }while (borrow_choice=='y'||borrow_choice=='Y');
}


char* idGetBook(int isborrowed_id){
    for (int i=0;i<book_count;i++){
        if (book[i].book_id==isborrowed_id){
            return book[i].book_name;
            return book[i].author;
        }
    }
    return "未知书籍";
}


void queryBorrow(){
    if (borrow_count==0){
        printf("暂无借阅记录！\n");
        return;
    }
    printf("==============\n");
    printf("以下是借阅记录：\n");
    printf("借阅人：%d\n",history[0].borrower_id);
    printf("一共借阅了%d本书\n",borrow_count);
    for (int i=0;i<borrow_count;i++){
        printf("--------------\n");
        printf("借阅书编号：%d\n",history[i].isborrowed_id);
        char* book_name=idGetBook(history[i].isborrowed_id);
        printf("书名：%s\n",book_name);
        char* author=idGetBook(history[i].isborrowed_id);
        printf("作者：%s\n",author);
    }
    printf("--------------\n");
    printf("借阅时间：%s", ctime(&history[0].date));
}


void returnBooks(int borrow_count){
    char wannareturn;
    if (borrow_count==0){
        return;
    }
    printf("您现在要还书吗？\n");
    scanf(" %c",&wannareturn);
    if (wannareturn=='y'||wannareturn=='Y'){
        for (int i=0;i<borrow_count;i++){
            book[i].stock++;
        }
        printf("已成功归还！\n");
    }
    else {
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

int main(){
    introBooks();
    borrowBooks();
    queryBorrow();
    returnBooks(borrow_count);
}