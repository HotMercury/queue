#include<stdio.h>
#include<stdlib.h>
void pri(void * path){
    printf("path %p\n",&path);
    printf("pointer to path %p\n",path);
}
int main(void){
    int** k;
    int* l;
    int g = 7;
    l = &g;
    k = &l;  

    pri(k);
    printf("%p\n",k);
    
    int gg = 9;
    printf("%p\n",&gg);
    printf("sizeof(int) = %ld\n",sizeof(int));
    printf("sizeof(int*) = %ld\n",sizeof(int*));
    


    return 0;
}