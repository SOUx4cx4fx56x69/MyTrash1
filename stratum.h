void ToStratumClient(int socket);

#define initStratumServ(host,port,socket){\
socket=InitServer(host,port);\
}
