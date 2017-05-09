#include <string.h>
#include <stdlib.h>
#include "stratum.h"
#include "main.h"
#include "util.h"
#include"json.h"
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

int getInfo(char*buf)
{
char * buffer = getOnlyJson(buf);
if(*buffer != '{') return 0;
void * firstPtr = buffer;
int jumpTo;
char ** info;
applog(DEBUG,"Allocate\n");
info = (char**)malloc(sizeof(char*) * 15);
for(unsigned int i = 16;i--;)
 *(info+i) = (char*)malloc(sizeof(char)*SIZEBUFFER);
applog(INFO,"Get Info\n");

GET_STR(buffer,jumpTo,info,0,"version");

GET_NUMBER(buffer,jumpTo,info,1,"protocolversion");

GET_NUMBER(buffer,jumpTo,info,2,"walletversion");

GET_NUMBER(buffer,jumpTo,info,3,"blocks");

GET_NUMBER(buffer,jumpTo,info,4,"moneysupply");

GET_NUMBER(buffer,jumpTo,info,5,"timeoffset");

GET_NUMBER(buffer,jumpTo,info,6,"connections");

GET_STR(buffer,jumpTo,info,7,"proxy");

GET_STR(buffer,jumpTo,info,8,"ip");

GET_NUMBER(buffer,jumpTo,info,9,"difficulty");

GET_NUMBER(buffer,jumpTo,info,10,"testnet");

GET_NUMBER(buffer,jumpTo,info,11,"keypoololdest");

GET_NUMBER(buffer,jumpTo,info,12,"keypoolsize");

GET_NUMBER(buffer,jumpTo,info,13,"paytxfee");

GET_NUMBER(buffer,jumpTo,info,14,"mininput");

GET_STR(buffer,jumpTo,info,15,"errors");
//

applog(DEBUG,"SetPar");
free(Info.Version);
free(Info.ProtocolVersion);
free(Info.WalletVersion);

Info.Blocks=0;
Info.MoneySupply=0;
Info.Timeoffset=0;
free(Info.Proxy);
free(Info.IP);
Info.difficulty=0;
Info.testnet=0;
free(Info.keypololdest);
Info.keypoolsize=0;
Info.paytxfee=0;
Info.mininput=0;
Info.errors=0;

Info.Version = strdup(info[0]);

Info.ProtocolVersion = strdup(info[1]);

Info.WalletVersion = strdup(info[2]);

Info.Blocks = atoi(info[3]);

Info.MoneySupply = atof(info[4]);

Info.Timeoffset = atoi(info[5]);

Info.Connections = atoi(info[6]);

Info.Proxy = strdup(info[7]);

Info.IP = strdup(info[8]);

Info.difficulty = atof(info[9]);

Info.testnet = strcmp(info[10],"true") ? true : false;

Info.keypololdest = strdup(info[11]);

Info.keypoolsize = atoi(info[12]);

Info.paytxfee = atof(info[13]);

Info.mininput = atof(info[14]);

Info.errors = strcmp(info[15],"true") ? true : false;
//
applog(DEBUG,"Free");
for(unsigned int i = 15;i--;)
 free(*(info+i));
free(buf);
//free(firstPtr);
}


void getDifficulty(valueDif * work,char**info)
{
//printf("GetDifficulty:%s\n",info[9]);
//(*work).svalue = atof(info[9]);
}

int getP(char*buffer,char*data,char byEnding)
{
int count=0;
while(*buffer != byEnding && *buffer)

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
int getWork(char*buf)
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
buffer+=getP(buffer,data,'"');
Check1(buffer);
buffer+=2;
Jumping(jumpTo,buffer,"\"hash1");
buffer+=6;

Check(buffer);

char * hash1 = (char*)malloc(sizeof(char) * strlen(buffer));
buffer+=getP(buffer,hash1,'"');
Check1(buffer);
buffer+=2;

if(*buffer && *buffer != '"' || *(buffer+1) != 't' || *(buffer+2) != 'a' || *(buffer+3) != 'r' || *(buffer+4) != 'g' || *(buffer+5) != 'e' || *(buffer+6) != 't' || *(buffer+7) != '"') return 0;
buffer+=7;

Check(buffer);
char * target = (char*)malloc(sizeof(char) * strlen(buffer));
buffer+=getP(buffer,target,'"');
free(first);

free(latest.data);
free(latest.hash1);
free(latest.target);
//free(latest.version);

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

buffer+=getP(buffer,user,'"');
*buffer++;

while(*buffer != '"')*buffer++;
*buffer++;

char * pass = (char*)malloc(sizeof(char) * strlen(buffer));
buffer+=getP(buffer,pass,'"');

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
