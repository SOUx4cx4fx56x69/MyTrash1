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

void SetBlock(int * socket)
{
 volatile float difficulty_tmp;
//
 char * getwork = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getwork\", \"params\": [] }");
 char * diff = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getinfo\", \"params\": [] }");
//
 getWork(getwork,*socket);
 getDifficulty(diff,&difficulty_tmp); 

 free(getwork);
 free(diff);

 latest.difficulty=difficulty_tmp;
 difficulty_tmp=0;
 printf("data:%s\nhash1:%s\ntarget:%s\ndifficulty:%f\n\n",latest.data,latest.hash1,latest.target,latest.difficulty);

 free(latest.data);
 free(latest.hash1);
 free(latest.target);

}

void ToStratumClient(int socket)
{
 while(1)
 {
 sleep(5);
 SetBlock(&socket);
 } 
}
