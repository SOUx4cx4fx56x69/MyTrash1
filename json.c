#include <string.h>
#include <stdlib.h>
#include "stratum.h"
#include "main.h"
#include "util.h"
//shitcode228
#define SIZEBUFFER MINSIZE*1
#define Check(buffer) if(*buffer != '"' || *(buffer+1) != ':' || *(buffer+2) != '"' && *buffer) return 0;\
 buffer+=3;
#define Check1(buffer) if(*buffer != '"' || *(buffer+1) != ',' || *(buffer+2) != '"' && *buffer) return 0;
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

int getDifficulty(char*buf,valueDif * work)
{

char * buffer = getOnlyJson(buf);
void * first = buffer;
if(*buffer != '{') return 0;
int jumpTo;
Jumping(jumpTo,buffer,"protocolversion");


while(*buffer && *buffer != '"')*buffer++;
if(!*buffer) return 0;
*buffer++;
*buffer++;

char * version = (char*)malloc(sizeof(char)*strlen(buffer));
buffer+=getP(buffer,version);
latest.version=strdup(version);
free(version);
if(*buffer == 0) return 0;

while(*buffer && *buffer != 'd' || *(buffer+1)!='i' || *(buffer+2)!='f' || *(buffer+3)!='f' || *(buffer+4)!='i'
|| *(buffer+5)!='c' || *(buffer+6)!='u' || *(buffer+7)!='l' || *(buffer+8)!='t' || *(buffer+9)!='y')
 *buffer++;
if(*buffer != 'd' || *(buffer+1)!='i' || *(buffer+2)!='f' || *(buffer+3)!='f' || *(buffer+4)!='i'
|| *(buffer+5)!='c' || *(buffer+6)!='u' || *(buffer+7)!='l' || *(buffer+8)!='t' || *(buffer+9)!='y')
return 0;
buffer+=12;
(*work).svalue = atof(buffer);
free(first);
}

int getP(char*buffer,char*data)
{
int count=0;
while(*buffer != '"' && *buffer)

{
if(*buffer != ',')

{
 count++;
 *data=*buffer;
 *data++;
}
 *buffer++;
}

if(!*buffer) return 0;
*data++='\0';
return count;
}

/*
this should send to socket ~ 
  
writeTo(client,"{\"params\": [\"b3ba\", \"7dcf1304b04e79024066cd9481aa464e2fe17966e19edf6f33970e1fe0b60277\", \"01000000010000000000000000000000000000000000000000000000000000000000000000ffffffff270362f401062f503253482f049b8f175308\", \"0d2f7374726174756d506f6f6c2f000000000100868591052100001976a91431482118f1d7504daf1c001cbfaf91ad580d176d88ac00000000\", [\"57351e8569cb9d036187a79fd1844fd930c1309efcd16c46af9bb9713b6ee734\", \"936ab9c33420f187acae660fcdb07ffdffa081273674f0f41e6ecc1347451d23\"], \"00000002\", \"1b44dfdb\", \"53178f9b\", true], \"id\": null, \"method\": \"mining.notify\"}");

*/
int getWork(char*buf,int socket)
{
int jumpTo;
latest.data=NULL;
latest.hash1=NULL;
latest.target=NULL;
char * buffer = getOnlyJson(buf);
if(*buffer == 0) return 0;
if(*buffer != '{') return 0;
void * first = buffer;
Jumping(jumpTo,buffer,"\"data");
buffer+=7;
if(*buffer != '"') return 0;
*buffer++;

char * data = (char*)malloc(sizeof(char) * strlen(buffer));
buffer+=getP(buffer,data);
Check1(buffer);
buffer+=2;
Jumping(jumpTo,buffer,"\"hash1");
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

latest.data=strdup(data);
latest.hash1=strdup(hash1);
latest.target=strdup(target);

free(data);
free(hash1);
free(target);
}

int getUser(char*buf)
{
int jumpTo;
char * buffer = getOnlyJson(buf);
if(*buffer == 0) return 0;
void * first = buffer;
if(*buffer != '{') return 0;
if(activeWorkers+1 > maxWorkers) return 0;
Jumping(jumpTo,buffer,"mining.authorize");
Jumping(jumpTo,buffer,"params");
buffer+=6;
Jumping(jumpTo,buffer,"[");

while(*buffer != '"' && *buffer) *buffer++;
if(!*buffer)return 0;
*buffer++;


char * user = (char*)malloc(sizeof(char) * strlen(buffer));

buffer+=getP(buffer,user);
*buffer++;

while(*buffer != '"')*buffer++;
*buffer++;

char * pass = (char*)malloc(sizeof(char) * strlen(buffer));
buffer+=getP(buffer,pass);

//
// set to struct with id user bla-bla-bla
//

workers[activeWorkers].login=strdup(user);
workers[activeWorkers].password=strdup(pass);
workers[activeWorkers].id=activeWorkers++;

return 1;
}
#ifdef Check
#undef Check
#endif
#ifdef Check1
#undef Check1
#endif
