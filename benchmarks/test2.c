#include<stdio.h>
#include<assert.h>

int sum(int a, int b) {
    return a + b;
}

int main() {

    int a = 1;
    int b = 3;
    assert(sum(a,b) == 4);

    return 0;
}