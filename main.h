#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
pthread_mutex_t getters;
#define MINSIZE 2056
void parse(int argCount,char**arguments);
typedef union
{
unsigned long long uvalue;
float svalue;
}valueDif;
