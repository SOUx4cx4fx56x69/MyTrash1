#include "socket.h"
#include "stratum.h"
#include "main.h"
#include "base64.h"
//For !(not)(less :) ) warning(lol bottom)
#include <string.h>
#include <string.h>
#include <unistd.h>
#warning This experemental/develop program!! 
//lol^^
static char * HOST;
static int PORT;
static char * USR;
static char * PSWRD;
static char * noError = "{\"error\": null, \"id\": 2, \"result\": true}";
static char * DiffiCulty = "{\"params\": [%f], \"id\": null, \"method\": \"mining.set_difficulty\"}";
block latest;
/*
Parse
*/
void parse(int argCount,char**arguments)
{
 if(argCount < 5) return error("./programm rpcAddr rpcPort rpcUser rpcPass");
 HOST = strdup(arguments[1]);
 PORT = atoi(arguments[2]);
 USR = strdup(arguments[3]);
 PSWRD = strdup(arguments[4]);
}
/*
End parse
*/

/*
for method
*/
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

void SetBlock(int * socket)
{
 volatile valueDif difficulty_tmp;
//
 char * getwork = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getwork\", \"params\": [] }");
 latest.time = (unsigned)time(NULL);
 char * diff = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getinfo\", \"params\": [] }");
//
 getWork(getwork,*socket);
 getDifficulty(diff,&difficulty_tmp); 

 free(getwork);
 free(diff);

 latest.difficulty=difficulty_tmp.svalue;
 difficulty_tmp.svalue=0;
 printf("data:%s\nhash1:%s\ntarget:%s\ndifficulty:%f\nversion:%s\ntimestamp:%d\n",latest.data,latest.hash1,latest.target,latest.difficulty,latest.version,latest.time);

 free(latest.data);
 free(latest.hash1);
 free(latest.target);

}
#warning this not correct worke!
void StratumReceiveClient(int * socket)
{
char tmp[MINSIZE];
int count =0 ; // shitcode228
while(1)

{
/*
{"id": 1, "method": "mining.subscribe", "params": ["cpuminer/2.3.2"]}
{"id": 2, "method": "mining.authorize", "params": ["gostcoinrpc", ""]}
*/
 readFrom(*socket,tmp);
 if(strstr(tmp,"mining.authorize") != NULL) if(getUser(tmp)) printf("Worked?\n");
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
 SetBlock(&socket);
 sprintf(tmp,DiffiCulty,latest.difficulty);
 writeTo(socket,tmp);
while(1)

{
sleep(15);
writeTo(socket,"{\"params\": [\"0\", \"7dcf1304b04e79024066cd9481aa464e2fe17966e19edf6f33970e1fe0b60277\", \"01000000010000000000000000000000000000000000000000000000000000000000000000ffffffff270362f401062f503253482f049b8f175308\", \"0d2f7374726174756d506f6f6c2f000000000100868591052100001976a91431482118f1d7504daf1c001cbfaf91ad580d176d88ac00000000\", [\"57351e8569cb9d036187a79fd1844fd930c1309efcd16c46af9bb9713b6ee734\", \"936ab9c33420f187acae660fcdb07ffdffa081273674f0f41e6ecc1347451d23\"], \"00000002\", \"1b44dfdb\", \"53178f9b\", true], \"id\": null, \"method\": \"mining.notify\"}");
writeTo(socket,tmp);
//
}

}
