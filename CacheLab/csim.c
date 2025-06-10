#define _DEFAULT_SOURCE
#define ADDRLEN 36
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


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

void hexTObinary(char* addr);

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
        char addr[36];
        char set_index[val_s];
        char block_offset[val_b];
        char tag[ADDRLEN - val_b - val_s];
        int size = 0;
        int item_catch = sscanf(buffer," %c %49[^,],%d",&operation,addr,&size);
        hexTObinary(addr);
        memcpy(block_offset,&addr[ADDRLEN - val_b],val_b);
        memcpy(set_index,&addr[ADDRLEN - val_b - val_s],val_s);
        set_index[val_s] = '\0';
        memcpy(tag,&addr,ADDRLEN - val_b - val_s);
        if (item_catch == 3){
            printf("操作: %c    | tag: %s | set index: %s | block offset: %s | 大小: %d\n", operation,tag, set_index,block_offset, size);
        }
    }
    // printSummary(0, 0, 0);
    return 0;
}

void hexTObinary(char *addr){
    char hex_addr[ADDRLEN];
    strcpy(hex_addr,addr);
    int str_len = strlen(addr);
    for(int i=0;i<ADDRLEN;++i){
        addr[i] = '0';
    }
    addr[ADDRLEN] = '\0';//make addr as a zero default
    for(int idx = str_len-1;idx >= 0;idx--){
        char digit = tolower(hex_addr[idx]);
        int index = -1;
        const char *hex_to_bin_lookup[16] = {
        "0000", "0001", "0010", "0011",
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100", "1101", "1110", "1111"
    };
        if(digit >= '0' && digit <= '9'){
            index = digit - '0';
        }
        if(digit >= 'a' && digit <= 'f'){
            index = digit - 'a' + 10;
        }
        if(index == -1){
            printf("index conversion error");
            exit(1);
        }
        memcpy(&addr[ADDRLEN - (str_len - idx) * 4],hex_to_bin_lookup[index],4);
    }
}
