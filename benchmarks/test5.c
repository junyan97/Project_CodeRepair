#include<stdio.h>
#include<assert.h>

int fun(int a) {
    
   for(int i = 0; i < 10; i++) {

        if(i < 5) {
            a = a % 1;
        }else{
            a = a + 2;
        }
   }

    return a;
}