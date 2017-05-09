#include "socket.h"
#include "stratum.h"
#include "main.h"
#include"util.h"
#include "base64.h"
//For !(not)(less :) ) warning(lol bottom)
#include <string.h>
#include <string.h>
#include <unistd.h>
#warning This experemental/develop program!! 
#define SLEEPTHREAD 15
pthread_mutex_t getters;
//lol^^
static char * HOST;
static int PORT;
static char * USR;
static char * PSWRD;

static char * noError = "{\"error\": null, \"id\": 2, \"result\": true}";
static char * DiffiCulty = "{\"params\": [%f], \"id\": null, \"method\": \"mining.set_difficulty\"}";
static char * notify = "{\"params\": [\"0\", \"%s\", \"0\", \"0\", [\"%s\", \"%s\"], \"%s\", \"%s\", \"%s\", %s], \"id\": null, \"method\": \"mining.notify\"}";

unsigned int activeWorkers=0;
unsigned int maxWorkers;

information Info;

users * workers;
block latest;
/*
Parse
*/
void parse(int argCount,char**arguments)
{
 if(argCount < 6) return error("./programm rpcAddr rpcPort rpcUser rpcPass maxWorkers");
 HOST = strdup(arguments[1]);
 PORT = atoi(arguments[2]);
 USR = strdup(arguments[3]);
 PSWRD = strdup(arguments[4]);
 maxWorkers = atoi(arguments[5]);
 workers = (struct users*)malloc(sizeof(struct users*) * maxWorkers);
 printf("Max workers: %d\n",maxWorkers);
}
/*
End parse
*/

/*
for method
*/


void threadForGetInfoBlock(void)
{
while(1)
{
 pthread_mutex_lock(&getters);
 char * getinfo = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getinfo\", \"params\": [] }");
 getInfo(getinfo);
 printf(
"Version:%s\n"
"ProtocolVersion:%s\n"
"WalletVersion:%s\n"
"Blocks:%d\n"
"MoneySupply:%f\n"
"TimeOffset:%d\n"
"Connections:%d\n"
"Proxy:%s\n"
"IP:%s\n"
"Difficulty:%f\n"
"testnet:%d\n"
"keypololdest:%s\n"
"keypoolsize:%d\n"
"paytxfee:%f\n"
"mininput:%f\n"
"errors:%d\n"
,
Info.Version,
Info.ProtocolVersion,
Info.WalletVersion,
Info.Blocks,
Info.MoneySupply,
Info.Timeoffset,
Info.Connections,
Info.Proxy,
Info.IP,
Info.difficulty,
Info.testnet,
Info.keypololdest,
Info.keypoolsize,
Info.paytxfee,
Info.mininput,
Info.errors
);
 applog(DEBUG,"Restart");
 pthread_mutex_unlock(&getters);
 sleep(SLEEPTHREAD);
}//while

}


char * method(char*method)
{
int Coin = InitClient( HOST, PORT );
char * tmp = (char*)calloc(sizeof(char),MINSIZE);
if(tmp == NULL) error("Not can alloc memory");
sprintf(tmp,"%s:%s",USR,PSWRD);

char * token = b64_encode(tmp);
int ContentLength = strlen(method);

sprintf(tmp,
"POST / HTTP/1.1\r\n"
"Host: %s:%d\r\n"
"Authorization: Basic %s\r\n"
"Accept: */*\r\n"
"content-type: text/plain;\r\n"
"Content-Length: %d\r\n"
"\r\n"
"%s\r\n\r\n"
,HOST,PORT,token,ContentLength,method);
writeTo(Coin,tmp);
readFrom(Coin,tmp);
if(strstr(tmp,"401") != NULL) error("Not good pass or login for coin");
close(Coin);
return tmp;
}
//{\"id\": 1, \"result\": [[\"mining.notify\", \"ae6812eb4cd7735a302a8a9dd95cf71f\"], \"08000002\", 4], \"error\": null}

void SetBlock(void)
{
while(1)
{
 pthread_mutex_lock(&getters);
//
 latest.time = (unsigned)time(NULL);
 char * getwork = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getwork\", \"params\": [] }");
 getWork(getwork);
//
 free(getwork);

 ReverseString(latest.data);
 ReverseString(latest.hash1);
// ReverseString(latest.target);

 printf("data:%s\nhash1:%s\ntarget:%s\ndifficulty:%f\nversion:%s\ntimestamp:%d\nWorkers[0].login: %s\n",latest.data,latest.hash1,latest.target,latest.difficulty,latest.version,latest.time,workers[0].login);
pthread_mutex_unlock(&getters);
sleep(SLEEPTHREAD);
}

}
#warning this not correct worke!
void StratumReceiveClient(int * socket)
{

char tmp[MINSIZE];
int count =0 ; // shitcode228
while(1)
#warning not correctly!
{
/*
{"id": 1, "method": "mining.subscribe", "params": ["cpuminer/2.3.2"]}
{"id": 2, "method": "mining.authorize", "params": ["gostcoinrpc", ""]}
*/
 readFrom(*socket,tmp);
 if(strstr(tmp,"mining.authorize") != NULL) if(!getUser(tmp)) printf("Max workers:)\n");
 printf("Written: %s\n",tmp);
 if(*tmp == 0) count++;
 if(count > 15) break;
}
close(*socket);
}
void ToStratumClient(int socket)
{
 pthread_t recvFromUser;
 pthread_create(&recvFromUser,NULL,StratumReceiveClient,&socket);
 char tmp[MINSIZE];
 writeTo(socket,"{\"id\": 1, \"result\": [[\"mining.notify\", \"1\"], \"1\", 1], \"error\": null}");
 writeTo(socket,noError);
 sprintf(tmp,DiffiCulty,latest.difficulty); // setdifficulty
 writeTo(socket,tmp);
while(1)

{
char nbits[MINSIZE]; 
char ntime[MINSIZE]; 
sprintf(nbits,"%02X",latest.time);
sprintf(ntime,"%02X",latest.difficulty);
sprintf(tmp,notify,
latest.target,latest.data,latest.hash1,latest.version,nbits,ntime,"false");
sleep(15);


writeTo(socket,tmp);
}


pthread_mutex_destroy(&getters);
}
