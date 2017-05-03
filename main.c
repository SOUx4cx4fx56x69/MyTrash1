#include "main.h"
#include "socket.h"
#include "base64.h"
#define MINSIZE 2056

char * method(char*method,char * host,int port,char * usr,char*pswrd)
{
char * tmp = (char*)calloc(sizeof(char),MINSIZE);
sprintf(tmp,"%s:%s",usr,pswrd);
char * token = b64_encode(tmp);
//token = 
sprintf(tmp,
"POST / HTTP/1.1\r\n"
"Host: %s:%d\r\n"
"Authorization: Basic %s\r\n"
"Accept: */*\r\n"
"content-type: text/plain;\r\n"
"Content-Length: 67\r\n"
"\r\n"
"%s\r\n"
,host,port,token,method);
return tmp;
}

int main(int argCount,char**arguments)

{ // ./programm CoinAddr PortCoin coinUse CoinPass
 if(argCount < 5) return 0;
 int Coin = InitClient( arguments[1], atoi(arguments[2]) );

 char * buffer;
 buffer = (char*)malloc( sizeof(char) * MINSIZE);

 char * meth = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getinfo\", \"params\": [] }",arguments[1],atoi(arguments[2]),arguments[3],arguments[4]);

 writeTo(Coin,meth);

 readFrom(Coin,buffer);
 printf("%s\n",buffer);

 free(meth);
 free(buffer);
 close(Coin);
 return 1;
}
