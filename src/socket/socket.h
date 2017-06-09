//#define SIZEBUFFER 2056
int writeTo(int socket,char*msg);
int readFrom(int socket,char*buffer);
void error(char*msg);
int InitClient(char*host,int portno);
int
AcceptClient(int socket);
int 
InitServer(char*host,int portno);
