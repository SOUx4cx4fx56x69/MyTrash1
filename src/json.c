#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "stratum.h"
#include "main.h"
#include "socket.h"
#include "util.h"
#include"json.h"
#include "gost.h"
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

int getInfo(void)
{
char * tmp = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getinfo\", \"params\": [] }");
char * buffer = getOnlyJson(tmp);

if(*buffer != '{') return 0;
void * firstPtr = buffer;
int jumpTo;
char ** info;
//applog(DEBUG,"Allocate\n");
info = (char**)malloc(sizeof(char*) * 16);
for(unsigned int i = 17;i--;)
 *(info+i) = (char*)malloc(sizeof(char)*SIZEBUFFER);
//applog(INFO,"Get Info\n");
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

//applog(DEBUG,"SetPar");
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
Info.networkhashps = 0;

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

char * tmp1 = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getnetworkhashps\", \"params\": [] }");
char * buffer1 = getOnlyJson(tmp1);
void * firstPtr1 = buffer1;


GET_NUMBER(buffer1,jumpTo,info,16,"result");
Info.networkhashps = (float)atoi(info[16]) / 1024;

//
//applog(DEBUG,"Free");
for(unsigned int i = 15;i--;)
 free(*(info+i));
free(tmp);
free(tmp1);

//free(firstPtr);
free(firstPtr1);
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
#warning Did not check

#define CATENATION(string,what)\
while(*what){\
 *string++=*what++;\
}

void Json_Mining_Submit(char*buf,const char*asq,int*socket)
{
puts("GetBlockHash");
int jumpTo;
char * buffer = asq;
void * tmp_adrr=buf;
printf("%s\n",buf);
unsigned int tmp_counter=0;
#if WITHOUTSQL == 1
char wallet[35];
#else
char wallet[MAXLOGINSIZE];
#endif
Jumping(jumpTo,buffer,"params");
TO_BRACKETS(buffer);
TO_BRACKETS(buffer);
if(!*buffer) goto out;
while(*buffer != '"')
 wallet[tmp_counter++]=*buffer++;
wallet[tmp_counter]='\0';
tmp_counter=0;

#if WITHOUTSQL == 0
if(!check_exist_wallet(wallet))
{
if(!*socket) goto out;
char tmp[17];
sprintf(tmp,"{\"error\": %s, \"id\": 2, \"result\": false}","Not valide adress");
writeTo(*socket,tmp);
close(*socket);
*socket=0;
}
#else
/*
if(!check_exist_user(wallet))
{

}
*/
#endif

//puts("GetOtherPar");
TO_BRACKETS(buffer);
TO_BRACKETS(buffer);
TO_BRACKETS(buffer);
TO_BRACKETS(buffer);
char ** work = (char**)malloc(sizeof(char*)*3);

for(unsigned int i = 4;i--;)
 *(work+i) = (char*)malloc(sizeof(char)*SIZEBUFFER);
const char * ver = "02000000";

CATENATION(buf,ver);
//CATENATION(buf,latest.previousblockhash);



for(unsigned int i = 0;i<3;i++)
{
void *fisrtbuf = work[i];
while(*buffer && *buffer != '"')
{
 *work[i]++=*buffer++;
}
*buffer++;
TO_BRACKETS(buffer);
*work[i]++='\0';
work[i]=fisrtbuf;
CATENATION(buf,work[i]);
work[i]=fisrtbuf;
}
//puts("All");
if(!*buffer) 
{
free(work[2]);
free(work[1]);
free(work);
goto out;
}
//printf("SSS: %s %s %s\n",work[0],work[1],work[2]);
//puts("Catenation");


*buf++='\0';
buf=tmp_adrr;
ASCIIToBin(buf); 
//ReverseString(buf); not reversed before, what for two reverse or im not understood?




puts(buf);


uint32_t digest[16] __attribute__((aligned(64)));
sph_gost512(buf,digest,80);
sph_gost256(digest,buf,64);



free(work[0]);
free(work[1]);
free(work[2]);

out:
asm(
"nop"
);
//
}
int getWork(void)
{
int jumpTo;
free(latest.version);
free(latest.previousblockhash);
free(latest.coinbaseaux);
free(latest.target);
free(latest.mintime);
free(latest.noncerange);
free(latest.curtime);
free(latest.bits);


char * tmp = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getblocktemplate\", \"params\": [] }");
char**work = (char**)malloc(sizeof(char*) * 8);


/*****/
//getPrevHash();
/*****/

char * buffer = getOnlyJson(tmp);

for(unsigned int i = 9;i--;)
 *(work+i) = (char*)malloc(sizeof(char)*SIZEBUFFER);

void * fbuffer = buffer;
if(*buffer == 0) return 0;
if(*buffer != '{') return 0;

GET_NUMBER(buffer,jumpTo,work,0,"version");

GET_STR(buffer,jumpTo,work,1,"previousblockhash");

GET_STR(buffer,jumpTo,work,2,"coinbaseaux");

GET_NUMBER(buffer,jumpTo,work,3,"coinbasevalue");

GET_STR(buffer,jumpTo,work,4,"target");

GET_NUMBER(buffer,jumpTo,work,5,"mintime");

GET_STR(buffer,jumpTo,work,6,"noncerange");

GET_NUMBER(buffer,jumpTo,work,7,"curtime");

GET_STR(buffer,jumpTo,work,8,"bits");

latest.version=strdup(work[0]);
//ReverseString(work[1]);
latest.previousblockhash=strdup(work[1]);

latest.coinbaseaux=strdup( work[2] );

latest.coinbasevalue=strdup(work[3]);

latest.target=strdup(work[4]);

latest.mintime=strdup(work[5]);

latest.noncerange=strdup(work[6]);
sprintf(work[7],"%08x",atoi(work[7]));
latest.curtime=strdup(work[7]);

latest.bits=strdup(work[8]);

for(unsigned int i = 9;i--;)
 free(*(work+i));

free(tmp);
free(fbuffer);
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
