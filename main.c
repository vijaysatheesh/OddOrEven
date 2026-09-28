#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/sysinfo.h>

void set_led_byte(char byte);
int mem_usage();

char log = 0;

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        log = 1;
    }
    
    char byte = 0b10000000;
    while(1){
        mem_usage();
        usleep(200000);
        byte = byte>>1;
        if(byte == 0x00) byte = 0b10000000;
    }

    return 0;
}

void set_led_byte(char byte){
    FILE * fp = fopen("/dev/led","wb");
    if(fp == NULL){
        printf("Open Failed!! Make sure the driver is loaded\n");
        exit(1);
    }
    fwrite(&byte,1,1,fp);
    fclose(fp);
};

void read_led_byte(char * byte){
    FILE * fp = fopen("/dev/led","r");
    if(fp == NULL){
        printf("Open Failed!! Make sure the driver is loaded\n");
        exit(1);
    }
    fread(&byte,1,1,fp);
    fclose(fp);
};


int mem_usage() {
    struct sysinfo si;

    if (sysinfo(&si) == 0) {
        long long total_ram = (long long)si.totalram * si.mem_unit;
        long long free_ram  = (long long)si.freeram * si.mem_unit;
        long long used_ram  = total_ram - free_ram;
        float percentage_8 = ((double)used_ram / total_ram) * 8;
        char byte = 0;
        set_led_byte(byte);
        for(int i = 0;i<(int)percentage_8 + 1;i++){
            byte = (byte<<1) | 0x1;
        }
        set_led_byte(byte);
        if (log)
        {
            printf("%f\nUsed System RAM:  %lld MB\n",percentage_8, used_ram / (1024 * 1024));
        }
        
    } else {
        perror("sysinfo error");
        return 1;
    }
    return 0;
}
