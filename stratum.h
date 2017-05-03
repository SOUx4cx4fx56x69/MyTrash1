void ToStratumClient(int socket);
char * method(char*method);

#define initStratumServ(host,port,socket){\
socket=InitServer(host,port);\
}
