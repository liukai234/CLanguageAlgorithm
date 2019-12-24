#include <stdio.h>

int main(int args, char *argv[])
{
    printf("open test2.dat\n");
    for(int i = 0; i < 100; i++){
        printf("treeInput father %d %d sex age spouse\n", i - 1, i);
    }
    printf("printTreeNode\n");
    printf("exit\n");
}