#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("Enter a number: ");
    int num;
    scanf("%d",&num);
    if (num % 2 == 0)
    {
        printf("Even\n");
    }else{
        printf("Odd\n");
    }
    
    return 0;
}
