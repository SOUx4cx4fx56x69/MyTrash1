#include <string.h>
#include <stdlib.h>
#include "main.h"

//shitcode228
#define SIZEBUFFER MINSIZE*1
#define Check(buffer) if(*buffer != '"' || *(buffer+1) != ':' || *(buffer+2) != '"' && *buffer) return 0;\
 buffer+=3;
#define Check1(buffer) if(*buffer != '"' || *(buffer+1) != ',' || *(buffer+2) != '"' && *buffer) return 0;
#define crete_arguments()\
char ** arguments;\
arguments=(char**)malloc(sizeof(char*)*3);\
*arguments=(char*)malloc(sizeof(char)*strlen(data)); \
*arguments=(char*)malloc(sizeof(char)*strlen(hash1)); \
*arguments=(char*)malloc(sizeof(char)*strlen(target));
char * getOnlyJson(char*buffer)
{

while(*buffer != '{' && *buffer)
 *buffer++;
if(*buffer != '{')return 0;
int jsonSize = strlen(buffer);
char * buf = (char*)malloc(sizeof(char)*jsonSize+1);
buf = strdup(buffer);
return buf;
}

void getDifficulty(char*buf,float*work)
{
char * buffer = getOnlyJson(buf);
if(*buffer == 0) return 0;
void * first = buffer;
while(*buffer && *buffer != 'd' || *(buffer+1)!='i' || *(buffer+2)!='f' || *(buffer+3)!='f' || *(buffer+4)!='i'
|| *(buffer+5)!='c' || *(buffer+6)!='u' || *(buffer+7)!='l' || *(buffer+8)!='t' || *(buffer+9)!='y')
 *buffer++;
if(*buffer != 'd' || *(buffer+1)!='i' || *(buffer+2)!='f' || *(buffer+3)!='f' || *(buffer+4)!='i'
|| *(buffer+5)!='c' || *(buffer+6)!='u' || *(buffer+7)!='l' || *(buffer+8)!='t' || *(buffer+9)!='y')
return 0;
buffer+=12;
*work = atof(buffer);
free(first);
}

int getP(char*buffer,char*data)
{
int count=0;
while(*buffer != '"' && *buffer)

{
count++;
*data=*buffer;
*data++;
*buffer++;
}
if(!*buffer) return 0;
return count;
}

/*
this should send to socket ~ 
  
writeTo(client,"{\"params\": [\"b3ba\", \"7dcf1304b04e79024066cd9481aa464e2fe17966e19edf6f33970e1fe0b60277\", \"01000000010000000000000000000000000000000000000000000000000000000000000000ffffffff270362f401062f503253482f049b8f175308\", \"0d2f7374726174756d506f6f6c2f000000000100868591052100001976a91431482118f1d7504daf1c001cbfaf91ad580d176d88ac00000000\", [\"57351e8569cb9d036187a79fd1844fd930c1309efcd16c46af9bb9713b6ee734\", \"936ab9c33420f187acae660fcdb07ffdffa081273674f0f41e6ecc1347451d23\"], \"00000002\", \"1b44dfdb\", \"53178f9b\", true], \"id\": null, \"method\": \"mining.notify\"}");

*/
void getWork(char*buf,int socket)
{
char * buffer = getOnlyJson(buf);
if(*buffer == 0) return 0;
void * first = buffer;
if(*buffer != '{') return 0;
while(
*buffer && 
*buffer != '"' 
|| *(buffer+1) != 'd' 
|| *(buffer+2) != 'a' 
|| *(buffer+3) != 't' 
|| *(buffer+4) != 'a'  
) *buffer++;
if(*buffer != '"')return 0;
buffer+=7;
if(*buffer != '"') return 0;
*buffer++;
char * data = (char*)malloc(sizeof(char) * strlen(buffer));
buffer+=getP(buffer,data);
Check1(buffer);
buffer+=2;
if(*(buffer) != '"' ||  *(buffer+1) != 'h' ||  *(buffer+2) != 'a' ||  *(buffer+3) != 's' ||  *(buffer+4) != 'h' ||  *(buffer+5) != '1' || *(buffer+6) != '"' && *buffer) return 0;
buffer+=6;

Check(buffer);

char * hash1 = (char*)malloc(sizeof(char) * strlen(buffer));
buffer+=getP(buffer,hash1);
Check1(buffer);
buffer+=2;

if(*buffer && *buffer != '"' || *(buffer+1) != 't' || *(buffer+2) != 'a' || *(buffer+3) != 'r' || *(buffer+4) != 'g' || *(buffer+5) != 'e' || *(buffer+6) != 't' || *(buffer+7) != '"') return 0;
buffer+=7;

Check(buffer);
char * target = (char*)malloc(sizeof(char) * strlen(buffer));
buffer+=getP(buffer,target);
free(first);
crete_arguments();
printf("data:%s\nhash1:%s\ntarget:%s\n",data,hash1,target);
arguments[0]=strdup(data);
arguments[1]=strdup(hash1);
arguments[2]=strdup(target);
free(arguments);
}
