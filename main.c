#include "main.h"
#include "socket.h"
#include "stratum.h"
#include"util.h"
#warning This experemental/develop program!! 

int main(int argCount,char**arguments)
{ 
 parse(argCount,arguments);
 pthread_t stratum;
 int Stratum;
 initStratumServ(arguments[1],3333,Stratum);
 pthread_create(&stratum,0,AcceptClient,Stratum);
 printf("Start thread\n");
 pthread_join(stratum);
/*
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
 return 1;
}
