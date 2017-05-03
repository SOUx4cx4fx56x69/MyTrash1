#include "main.h"
#include "socket.h"
#include "base64.h"
#include "stratum.h"

//For !(not)(less :) ) warning(lol bottom)
#include <string.h>
#include <string.h>
#include <unistd.h>
#warning This experemental/develop program!! //lol^^

static char * HOST;
static int PORT;
static char * USR;
static char * PSWRD;
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
sprintf(tmp,"%s:%s",USR,PSWRD);
char * token = b64_encode(tmp);

int ContentLength = strlen(method);

//token = 
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
/*
end for method
*/


int main(int argCount,char**arguments)
{ 


 parse(argCount,arguments);

 char * buffer = (char*)malloc( sizeof(char) * MINSIZE);
 if(!buffer) error("Not can allocate memory");
 char * meth = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getinfo\", \"params\": [] }");

 char * meth1 = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getwork\", \"params\": [] }");
 float work; 
 getDifficulty(meth,&work); 
 printf("%f",work);
 char ** _work = getWork(meth1);
 printf("data:%s\nhash1:%s\ntarget:%s\n",_work[0],_work[1],_work[2]);
/*
 int Stratum;
 initStratumServ(HOST,3333,Stratum);
 // 
 int client = AcceptClient(Stratum);

//TEST
  readFrom(client,buffer); 
  char ** Answers = GetIdAndMethod(buffer);
 if( !Answers )printf("error");

  printf("%s\n",buffer);
  writeTo(client,"{\"id\": 1, \"result\": [[\"mining.notify\", \"ae6812eb4cd7735a302a8a9dd95cf71f\"], \"08000002\", 4], \"error\": null}");
  readFrom(client,buffer);
  printf("%s\n",buffer);
  writeTo(client,"{\"error\": null, \"id\": 2, \"result\": true}");
  writeTo(client,"{\"params\": [0.1], \"id\": null, \"method\": \"mining.set_difficulty\"}");
 while(1)
 {
  writeTo(client,"{\"params\": [\"b3ba\", \"7dcf1304b04e79024066cd9481aa464e2fe17966e19edf6f33970e1fe0b60277\", \"01000000010000000000000000000000000000000000000000000000000000000000000000ffffffff270362f401062f503253482f049b8f175308\", \"0d2f7374726174756d506f6f6c2f000000000100868591052100001976a91431482118f1d7504daf1c001cbfaf91ad580d176d88ac00000000\", [\"57351e8569cb9d036187a79fd1844fd930c1309efcd16c46af9bb9713b6ee734\", \"936ab9c33420f187acae660fcdb07ffdffa081273674f0f41e6ecc1347451d23\"], \"00000002\", \"1b44dfdb\", \"53178f9b\", true], \"id\": null, \"method\": \"mining.notify\"}");
sleep(5);
  readFrom(client,buffer);
  printf("%s\n",buffer);
 }
*/


 //

 free(meth);
 free(meth1);
 free(_work);
 free(buffer);
 //close(client);
 return 1;
}
