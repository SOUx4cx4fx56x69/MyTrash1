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
#define SLEEPTHREAD 120

#warning this value get from otebis without math podshetov
#define SIZETEMPLATEHASH 512

//lol^^
static char * HOST;
static int PORT;
static char * USR;
static char * PSWRD;
static short jobID __attribute__((aligned(4))) = 0;
static char * Message = "{\"id\": 0, \"method\": \"client.show_message\", \"params\": [\"%s\"]}";
static char * noError = "{\"error\": null, \"id\": 2, \"result\": true}";
static char * DiffiCulty = "{\"params\": [%f], \"id\": null, \"method\": \"mining.set_difficulty\"}";
static char * notify = "{\"id\":null,\"method\":\"mining.notify\",\"params\":[\"%04x\",\"%s\",\"%s\",\"\",[],\"%s\",\"%s\",\"%s\",%s]}";

unsigned int activeWorkers=0;
unsigned int maxWorkers;

information Info;

users * workers;
block latest;
/*
Parse
*/
void timer_for_new_info(void)
{
 sleep(0);
 pthread_mutex_unlock(&getters);
}

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

void SetBlock(void)
{
while(1)
{
//
 pthread_mutex_lock(&getters);
 puts("SetBlock");
 getWork();
//

// ReverseString(latest.data);
// ReverseString(latest.hash1);
// ReverseString(latest.target);

/*
 printf("data:%s\nhash1:%s\ntarget:%s\ndifficulty:%f\nversion:%s\ntimestamp:%d\nWorkers[0].login: %s\n",latest.data,latest.hash1,latest.target,Info.difficulty,latest.version,latest.time,workers[0].login);
*/
//sleep(SLEEPTHREAD);
}//while

}


void threadForGetInfo(void)
{
while(1)
{
 puts("GetInfo");
 getInfo();
/*
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
"Khash:%f\n"
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
Info.errors,
Info.networkhashps
);

 applog(DEBUG,"Restart");
*/
 sleep(SLEEPTHREAD);
 //pthread_mutex_lock(&getters);
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
if(strstr(tmp,"HTTP/1.0 401 Authorization Required") != NULL) error("Not good pass or login for RPC");
close(Coin);
return tmp;
}
//{\"id\": 1, \"result\": [[\"mining.notify\", \"ae6812eb4cd7735a302a8a9dd95cf71f\"], \"08000002\", 4], \"error\": null}

#define STRSTR(string,string1,function)\
{\
if(strstr(string,string1) != NULL)\
{\
function(string1);\
}\
}

#warning this not correct worke!
void StratumReceiveClient(int * socket)
{
char tmp[MINSIZE];
sprintf(tmp,Message,"Hello! This experemental server");
writeTo(*socket,tmp);
while(1)
#warning not correctly!
{
 readFrom(*socket,tmp);
 applog(DEBUG, "Written: %s\n",tmp);
 if(strstr(tmp,"mining.authorize") != NULL) 
  if(!getUser(tmp)) 
  {
   applog(INFO,"Max users on server\n");
   break;
  }
 else if(strstr(tmp,"mining.submit") != NULL)
 {
   puts("GetBlockHash");
   char * hash = (char*)calloc(sizeof(char),SIZETEMPLATEHASH);
   Json_Mining_Submit(hash,tmp);
   //sendresult
   //after
   jobID++;
   pthread_mutex_unlock(&getters);
 }
 if(*tmp == 0) break;
}
if(activeWorkers != 0)
 activeWorkers--;
close(*socket);
*socket=0;
}

void ToStratumClient(int socket)
{
 pthread_t recvFromUser;
 pthread_create(&recvFromUser,NULL,StratumReceiveClient,&socket);
 char tmp[MINSIZE];
 writeTo(socket,"{\"id\": 1, \"result\": [[\"mining.notify\", \"1\"], \"1\", 1], \"error\": null}");
 writeTo(socket,noError);
 sprintf(tmp,DiffiCulty,Info.difficulty); // setdifficulty
 writeTo(socket,tmp);
while(socket)

{
if(jobID == 65553) jobID=0;
sprintf(tmp,notify,jobID,latest.previousblockhash,latest.target,"02000000",latest.curtime,latest.bits,"false");
/*
Field Name	Purpose	Example
JobID	ID of the job. Used when submitting a solved shared to the server.	
76df
PrevHash	Hash of the previous block. Used when deriving work.	
7817c24aa99f3999a57dcfc8a7a834f9
2ebb442f8d519dbd000009e000000000
CoinBase1	Other part of the block header. Used when deriving work.	
d52f367013ddc74d61a4f50c0d47c4b8
e87b6d89a603a04447bcd2b110c508e3
1d37308253d38bbe0464508f4eb1f12b
92e6431d41b01f01518d2d9b9b64fe93
010098588e9b1c650500030052a90000
b778171a134e691e01000000b1c70000
ce0f0000d052a1570000000000000000
CoinBase2	Final part of the coinbase transaction. Not used.	Empty String
MerkleBranches	Array of merkle branches. Unused at this time.	Empty Array
BlockVersion	Decred block version. Already in CoinBase 1, not useful.	01000000
Nbits	Encoded current network difficulty. Already in CoinBase 1, not useful.	1a1778b7
Ntime	Server's time when the job was transmitted. Already in CoinBase 1, not useful.	57a152d0
CleanJobs	When true, discard current work and re-calculate derived work.	false


version:  00000002 --> 02000000
prevhash: 7dcf1304 b04e7902 4066cd94 81aa464e 2fe17966 e19edf6f 33970e1f e0b60277
        -->   0413cf7d 02794eb0 94cd6640 4e46aa81 6679e12f 6fdf9ee1 1f0e9733 7702b6e0 // 8 ints left to right, each one flipped
merkle:   0b1edc1c cf82d321 4423fc68 234f4946 119e39df 2cc2137e 31ebc186 191d5422 // nothing changed 
ntime:    53178f9b --> 9b8f1753
nbits:    1b44dfdb --> dbdf441b


*/
//applog(DEBUG,"WriteToClient: %s",tmp);
if(writeTo(socket,tmp) == -1) break;
}

close(socket);
pthread_mutex_destroy(&getters);
}
