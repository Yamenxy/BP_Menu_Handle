#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    size_t Size, Capacity;
    int64_t *Array;
} vector;

vector *construct(vector *self, size_t _size, int64_t _value)
{
    self->Size=self->Capacity=_size;
    self->Array= (int64_t*)malloc(sizeof(int64_t) *
    self->Capacity);
    for(size_t i=0;i<_size;i++)
        self->Array[i] = _value;
    return self;
}

void push_back(vector *self,int64_t _data)
{
    if(!self->Size)
    {
        self->Size=self->Capacity=1;
        self->Array=(int64_t *)malloc(sizeof(int64_t)*self->Capacity);
        self->Array[0]=_data;
    }
    else if(self->Size == self->Capacity)
    {
        self->Capacity*=2;
        int64_t *pkr_mer_ko=(int64_t *)malloc(sizeof(int64_t) *self->Capacity);
        for(size_t i=0;i<self->Size;i++)
        {
            pkr_mery_ko[i]=self->Array[i];
        }
        free(self->Array);
        self->Array=pkr_mery_ko;
        self->Array[self->Size++]=_data;
    }
    else self->Array[self->Size++]=_data
}
