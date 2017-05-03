void ToStratumClient(int socket);
char * method(char*method,int*socket);
#define initStratumServ(host,port,socket){\
socket=InitServer(host,port);\
}
