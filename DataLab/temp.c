#include <stdio.h>
int logicalNeg(int x) {
    int a = x|(~x+1);
    int b = a>>31;
    int c = b^1;
    return c;
    }
int main(){
    int x = '0';
    printf("%d",(1<<30));
}