#include<stdio.h>
#include<assert.h>

int inc(int a) {
    a++;
    return a;
}

int main() {

    int a = 1;
    
    assert(inc(a) == 2);

    return 0;
}