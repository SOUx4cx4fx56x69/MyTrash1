#define WITHOUTSQL 1
#define MAXLOGINSIZE 120
void closeserver(void);
void ToStratumClient(int socket);
char * method(char*method);
void SetBlock(void);
void threadForGetInfo(void);
int getWork(void);
int getInfo(void);
typedef const char* string;
typedef unsigned long long ull;
typedef enum
{
false,true
}bool;

typedef struct 
{
char*login;
char*password;
unsigned int id;
}users;

typedef struct
{
char*version;
char*previousblockhash;
char*coinbaseaux;
char*coinbasevalue;
char*target;
char*mintime;
char*noncerange;
char*curtime;
char*bits;
}block;

typedef struct 
{
char * Version;
char * ProtocolVersion;
char * WalletVersion;
ull Blocks;
float MoneySupply;
int Timeoffset;
unsigned int Connections;
char * Proxy;
char * IP;
float difficulty;
bool testnet;
char * keypololdest;
unsigned int keypoolsize;
float paytxfee;
float mininput;
bool errors;
float networkhashps;
}information;

unsigned int activeWorkers;
unsigned int maxWorkers;

block latest;
users * workers;
information Info;

#define initStratumServ(host,port,socket){\
socket=InitServer(host,port);\
}
