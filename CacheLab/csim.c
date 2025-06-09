#define _DEFAULT_SOURCE
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *optarg;

// typedef struct  Block
// {
//     int v;
//     int tag;
//     int b;
// };

// b 代表每一个缓存行读取的时候加载的字节数量为 2^b 
// s 代表的一共有 2^s 个缓存组
// E 代表每个缓存组有E个缓存行
// CPU向缓存发送的地址被拆分为 tag(t bits) + set index(s bits) + block offset(b bits)
// tag用于缓存行与发送地址的对应, set index用于快速确认数据所处的缓存组, block offset用于找到对应的缓存行后加载该偏移下的数据

int main(int argc,char* argv[])
{   
    int val_h = 0;
    int val_v = 0;
    int val_s = 0;
    int val_E = 0;
    int val_b = 0;
    char* trace_file = NULL;
    int opt;
    while ((opt = getopt(argc,argv,"hvs:E:b:t:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            val_h = 1;
            break;
        case 'v':
            val_v = 1;
            break;
        case 's':
            val_s = atoi(optarg);
            break;
        case 'E':
            val_E = atoi(optarg);
            break;
        case 'b':
            val_b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        default:
            break;
        }
    }//get hyper parameters
    
    // load file
    printf("%d %d %d %d %d %s\n",val_h,val_v,val_s,val_E,val_b,trace_file);
    FILE* fp = fopen(trace_file,"r");
    if (fp == NULL){
        printf("file open error");
        exit(1);
    }
    char buffer[256];
    while(fgets(buffer,sizeof(buffer),fp) != NULL){
        char operation;
        int address = 0;
        int size = 0;
        sscanf(buffer," %c %d,%d",&operation,&address,&size);
        // if (item_catch == 3){
            printf("操作: %c    | 地址: %d | 大小: %d\n", operation, address, size);
        // }
    }
    // printSummary(0, 0, 0);
    return 0;
}
