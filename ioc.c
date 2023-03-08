#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define LEN(a) (sizeof(a)/sizeof(a[0]))
typedef unsigned int size_t;

typedef struct QCB{
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    uint32_t elements_in;
    size_t size;
    size_t* buffer;
}QCB;
typedef struct ref{
    int a;
    char b;
    char* c;
}ref;

#define aa 0
#define bb 1
#define CC 2

uint32_t QCB_0_buffer[10];
char QCB_1_buffer[10];
ref QCB_2_buffer[10];
QCB qcb[3] = {
        {0,0,10,0,4,QCB_0_buffer},
        {0,0,10,0,1,QCB_1_buffer},
        {0,0,10,0,LEN(QCB_2_buffer),QCB_2_buffer}
    };

//data copy
void* memcpy_j(void* dest,const void *src, size_t n){
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
    size_t* src = data;
    size_t* des = &(qp->buffer[qp->head]);
    size_t size = qp->size;
    memcpy_j(des,src,size);
    qp->head++;
}

void IocSend_aa(uint32_t data){
    printf("data address = %p\n",&data);
    enqueue(aa,&data);        
}

int main(void){
    IocSend_aa(10);
    IocSend_aa(111);
    printf("%p %d %d",QCB_0_buffer,QCB_0_buffer[0],QCB_0_buffer[1]);
    return 0;
}