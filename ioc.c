/*
預設已知
queue internal buffer size
send once size
iocid
*/


#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define LEN(a) (sizeof(a)/sizeof(a[0]))


typedef struct QCB{
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    uint32_t elements_in;
    uint32_t size;//item_size
    uint32_t* buffer;
}QCB;

typedef struct ref_cc{
    int a;
    short b;
    char c;
}ref_cc;


#define aa 0
#define bb 1
#define cc 2
#define dd 3

uint32_t QCB_0_buffer[10];
char QCB_1_buffer[10];
ref_cc QCB_2_buffer[10];
uint32_t* QCB_3_buffer[10];
QCB qcb[4] = {
        {0,0,10,0,4,(uint32_t*)QCB_0_buffer},
        {0,0,10,0,1,(uint32_t*)QCB_1_buffer},
        {0,0,10,0,sizeof(struct ref_cc),(uint32_t*)QCB_2_buffer},
        {0,0,10,0,sizeof(uint32_t*),(uint32_t*)QCB_3_buffer}
    };

//data copy
void* memcpy_j(void* dest,const void *src, uint32_t n){
    printf("size n = %d\n",n);
    printf("dest address = %p\n",dest);
    printf("src address = %p\n",src);
    char *d = dest;
    const char *s = src;
    for(size_t i = 0; i < n; i++){
        *d = *s;
        ++d;
        ++s;
    }
    return dest;
}

// 
// QCB_id.head = 0;
// tail = 0;
// capacity = 0;
// elements_in = 0;
// size = 0;
// buffer = QCB_id_buffer
void enqueue(int id, void* data){
    printf("enqueue data address = %p\n",data);
    printf("id = %d\n",id);
    QCB* qp = &qcb[id];
    if(qp->elements_in == qp->capacity){
        printf("buffer is full\n");
        return;
    }

    uint32_t* src = data;
    uint32_t* des = &(qp->buffer[qp->head]);
    uint32_t size = qp->size;
    memcpy_j(des,src,size);
    qp->elements_in++;
    qp->head++;
}
void dequeue(int id,void *data){
    printf("dequeue data address = %p\n",data);
    QCB* qp = &qcb[id];
    if(qp->elements_in == 0){
        printf("empty\n");
        return;
    }
    uint32_t* des = data;
    uint32_t* src = &(qp->buffer[qp->tail]);
    uint32_t size = qp->size;
    memcpy_j(des,src,size);
    qp->elements_in--;
    qp->tail++;//circle
}

void IocSend_aa(uint32_t data){
    printf("data address = %p\n",&data);
    enqueue(aa,&data);        
}
void IocReceive_aa(uint32_t* data){
    dequeue(aa,data);
}

void IocSend_bb(char data){
    enqueue(bb,&data);
}
void IocReceive_bb(char* data){
    dequeue(bb,data);
}

void IocSend_cc(int data1, short data2, char data3){
    ref_cc tmp;
    tmp.a = data1;
    tmp.b = data2;
    tmp.c = data3;
    enqueue(cc,&tmp);
}
void IocReceive_cc(int* data1, short* data2, char* data3){
    ref_cc tmp;
    dequeue(cc,&tmp);
    *data1 = tmp.a;
    *data2 = tmp.b;
    *data3 = tmp.c;
}
void IocSend_dd(int* data){
    enqueue(dd,&data);
}
void IocReceive_dd(int** data){
    dequeue(dd,data);
}

int main(void){
    /* send integer begin*/
    // IocSend_aa(10);
    // IocSend_aa(111);
    // int data = 0;
    // IocReceive_aa(&data);
    // IocReceive_aa(&data);
    // IocReceive_aa(&data);
    // printf("receive data is %d\n",data);    printf("%p %d %d\n",QCB_0_buffer,QCB_0_buffer[0],QCB_0_buffer[1]);  
    /* send integer end*/

    /* send char begin*/
    // IocSend_bb('b');
    // char out;
    // IocReceive_bb(&out);
    // printf("bb out char = %c\n",out);
    // ref_cc q = {87,87,"k"};
    /* send integer end*/

    /*send group start*/
    int a;
    short b;
    char c;
    IocSend_cc(87,87,'k');
    IocReceive_cc(&a,&b,&c);
    printf("%d %hd %c",a,b,c);
 
    /*send group end*/

    /*send reference begin*/
    int kk = 5;
    int lll = 9;
    int* ll = &lll;
    int** l = &ll;
    IocSend_dd(&kk);
    IocReceive_dd(l);
    printf("lll = %d\n",lll);
    printf("lll = %d\n",**l);
    /*send reference end*/
    return 0;

}