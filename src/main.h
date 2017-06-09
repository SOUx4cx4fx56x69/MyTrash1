#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
unsigned int port_web;
unsigned int port_stratum;

char * host_web;
char * host_stratum;

pthread_mutex_t getters;
#define MINSIZE 2056
void parse(int argCount,char**arguments);
typedef union
{
unsigned long long uvalue;
float svalue;
}valueDif;
