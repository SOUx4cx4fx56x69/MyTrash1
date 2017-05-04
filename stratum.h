void ToStratumClient(int socket);
char * method(char*method);
typedef struct 
{
char*login;
char*password;
unsigned int id;
}users;

typedef struct
{
char*data;
char*hash1;
char*target;
char*version;
float difficulty;
int time;
}block;

block latest;

#define initStratumServ(host,port,socket){\
socket=InitServer(host,port);\
}
