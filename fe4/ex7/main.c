#include <stdio.h>
#include <stdlib.h>

int global = 10; /* Uninitialized variable stored in bss */
int bssVar;

void afunc(void){
    static int level = 0;       /* recursion level */
    auto int stack_var;        /* automatic variable, on stack */

    if (++level > 3)           /* avoid infinite recursion */
        return;

    printf("Stack level %d: address of stack_var: %p\n",
            level, & stack_var);
    afunc();                    /* recursive call */
};

int main(int argc, char *argv[], char *envp[]) {    // Memory test
    static int i;    /* Uninitialized static variable stored in bss */
    
    printf("---Text Locations---\n");
    printf("Address of main: %p\n", main);
    printf("Address of afunc %p\n", afunc);

    


    printf("---Data Locations---\n");
    printf("Address of global %p\n", &global);

    printf("---BSS Locations---\n");
    printf("Address of bssVar: %p\n", &bssVar);

    printf("---Heap Locations---\n");
    char* dynamicArr = (char *) malloc(10);
    printf("Start Address of dynamicArr: %p\n", dynamicArr);
    printf("End Address of dynamicArr: %p\n", &dynamicArr[9] );

    printf("---Stack Locations---\n");
    afunc();
    int tempVar1 = 1;
    int tempVar2 = 1;
    printf("Address of tempVar1: %p\n", &tempVar1);
    printf("Address of tempVar2: %p\n", &tempVar2);

    return 0;
}