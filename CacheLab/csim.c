#define _DEFAULT_SOURCE
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *optarg;

int main(int argc,char* argv[])
{
    int val_s = 0;
    int val_E = 0;
    int val_b = 0;
    char* trace_file = NULL;
    int opt;
    while ((opt = getopt(argc,argv,"s:E:b:t:")) != -1)
    {
        switch (opt)
        {
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
    
    

    // printSummary(0, 0, 0);
    return 0;
}
