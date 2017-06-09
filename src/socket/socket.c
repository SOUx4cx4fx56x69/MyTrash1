#include "socket.h"
#include "../stratum.h"
#include "../main.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#ifdef WIN32
   #include <winsock.h>
   #include <winsock2.h>
   #include <ws2tcpip.h>
   #define MSG_NOSIGNAL 0
   #pragma comment(lib, "ws2_32.lib")
#else
 #include <arpa/inet.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
#endif

#define SIZEBUFFER 2056

int 
InitServer(char*host,int portno)
{
    #ifdef WIN32
     WSADATA wsaData;
     DWORD dwError;
    // Initialize Winsock
    if ( (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) )
        error("WSAStartup failed\n");
    #endif
     int sockfd;
    struct sockaddr_in serv_addr;
     if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0))  < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = inet_addr(host);
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen( sockfd, 1 );
//....
     struct timeval timeout;
     timeout.tv_sec = 500;
     timeout.tv_usec = 5;
//...
///
    if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                sizeof(timeout)) < 0)
        error("setsockopt failed timeout");
    if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                sizeof(timeout)) < 0)
        error("setsockopt failed timeout");
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
     error("setsockopt(SO_REUSEADDR) failed");
///
   return sockfd;
}

int 
InitClient(char*host,int portno)
{
    #ifdef WIN32
     WSADATA wsaData;
     DWORD dwError;
    // Initialize Winsock
    if ( (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) )
        error("WSAStartup failed\n");
    #endif
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if(sockfd == -1) error("No can create socket");
    server = gethostbyname(host);
    if (server == NULL)error("No such host");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    return sockfd;
}



int
AcceptClient(int socket)
{
//
pthread_t client;
struct sockaddr_in cli_addr;
while(1)
{
int clientlen = sizeof(cli_addr);
////
int newsockfd = accept(socket,
				  (struct sockaddr *) &cli_addr, 
								 &clientlen);
////
if (newsockfd < 0) 
  close(newsockfd);
else
{
printf("Opened new connection with %d.%d.%d.%d\n",
  (int)(cli_addr.sin_addr.s_addr&0xFF),
  (int)((cli_addr.sin_addr.s_addr&0xFF00)>>8),
  (int)((cli_addr.sin_addr.s_addr&0xFF0000)>>16),
  (int)((cli_addr.sin_addr.s_addr&0xFF000000)>>24));
  pthread_create(&client,NULL,(void*)ToStratumClient,newsockfd);
}//ELSE
}//while

}//function

int inline
writeTo(int socket,char*msg)
{

if(send(socket,msg,strlen(msg),MSG_NOSIGNAL) == -1)
{
fprintf(stderr,"No can write to socket. ");
return -1;
}

if(send(socket,"\n",1,MSG_NOSIGNAL) == -1)
{
fprintf(stderr,"No can write to socket. ");
return -1;
}

}

int inline 
readFrom(int socket,char*buffer)
{
memset(buffer,0,SIZEBUFFER);
#ifdef WIN32
if((recv(socket, buffer, SIZEBUFFER-1, 0)) <=0 )
{
fprintf(stderr,"No can read from socket");
return -1;
}
#else
if(read(socket,buffer,SIZEBUFFER-1) == -1)
{
fprintf(stderr,"No can read from socket");
return -1;
}
#endif
}
#undef SIZEBUFFER

