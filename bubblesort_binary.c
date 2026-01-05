#include <stdio.h>

void bubbleSort(int arr[],int n){
    for (int i=0;i<n-1;i++){
        for (int j=0;j<n-(i+1);j++){
            if (arr[j]>arr[j+1]){
                int temp=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=temp;
            }
        }
        //printf("第%d轮后：\n",i+1);
        printf("从小到大排序：");
        for (int k=0;k<n;k++){
            printf("%d ",arr[k]);
        }
        printf("\n");
    }   
}


int binarySearch(int arr[],int n,int target){
    int left=0;
    int right=n-1;
    int mid; //只定义，不初始化

    while (left<=right){
        mid=left+(right-left)/2; //在循环内更新mid
        printf("计算后：mid=%d，arr[mid]=%d|",mid,arr[mid]);
        if (arr[mid]==target)  return mid;
        else if (arr[mid]<target){
            left=mid+1;
        }
        else right=mid-1;
        printf("查找范围:left:%d,right:%d\n",left,right);
    }
    return -1;
}


int main(){
    int arr[100];
    int n;
    int target;

    printf("请输入数组长度:");
    scanf("%d",&n);
    printf("请输入数组中的数字：\n");
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("原始数组：\n");
    for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");

    bubbleSort(arr,n);
    
    printf("=====二分查找=====\n");
    printf("请输入你想查找的数字：");
    scanf("%d",&target);
    int index=binarySearch(arr,n,target);

    if (index!=-1){
        printf("已找到！数字%d在排序后的数组里索引为%d",target,index);
    }
    else printf("没找到数字%d",target);

}