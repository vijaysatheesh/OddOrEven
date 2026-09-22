#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    FILE * fp = fopen("/dev/led","w");
    char byte = 0;
    while(1){
        putc(byte,fp);
        sleep(1);
        byte++;
    }
    
    return 0;
}
