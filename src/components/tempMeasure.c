#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


void* tempMeasure(void* arg){
    float *temperatura = (float*) arg;
    system("sudo modprobe w1-gpio");
    system("sudo modprobe w1-therm");
    int i=0;
    float temp;
    FILE  *fp;
    char leitura[100];
    while(i<10)
    {
    system("cat /sys/bus/w1/devices/28-3c01a81664b5/w1_slave > temperature.txt");
    fp=fopen("temperature.txt","r");
    if(fp == NULL) return -1;
    fscanf(fp, "%*[^\n]\n");
    fscanf(fp,"%*29c%s",leitura);
    temp = strtof(leitura, NULL);
    temp /= 1000;;
    temp = temp - 5;
    fprintf(stderr, "temperatura :%f\n", temp);
    
    fclose(fp);
    i++;
    }
    *temperatura = temp;
}

