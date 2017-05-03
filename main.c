#include "main.h"
#include "socket.h"
#include "base64.h"
#define MINSIZE 2056

char * http_auth_string(char * path,char * host,char * usr,char*pswrd)
{
char * tmp = (char*)calloc(sizeof(char),MINSIZE);
sprintf(tmp,"%s:%s",usr,pswrd);
char * token = b64_encode(tmp);
//token = 
sprintf(tmp,
"GET %s HTTP/1.1\n"
"Content-Type: text/plain\n"
"Host: %s\n"
"Authorization: Basic %s\n"
"\r\n\r\n"
,path,host,token);
return tmp;
}

int main(int argCount,char**arguments)

{ // ./programm CoinAddr PortCoin coinUse CoinPass
 if(argCount < 5) return 0;
 int Coin = InitClient( arguments[1], atoi(arguments[2]) );

 char * buffer;
 buffer = (char*)malloc( sizeof(char) * MINSIZE);

 char * auth = http_auth_string("/",arguments[1],arguments[3],arguments[4]);
 writeTo(Coin,auth);
 //writeTo(Coin,"{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getinfo\", \"params\": [] }");
 readFrom(Coin,buffer);
 printf("%s\n",buffer);

 free(buffer);

 return 1;
}
