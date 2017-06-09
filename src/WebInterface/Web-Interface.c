#include "../socket/socket.h"
#include "../stratum.h"
#include "../main.h"
#include"../util.h"
#include "../base64.h"
#include <unistd.h>
void * startWeb(void)
{
 int Web_socket;
 pthread_t Web;
 printf("WEB: %s %d\n",host_web,port_web);
 initServ(host_web,port_web,Web_socket);
 pthread_create(&Web,0,(void*)AcceptClient_web,Web_socket);
 pthread_join(Web,NULL);
}
void * WebThread(int socket)
{
char buffer[2056];
readFrom(socket,buffer);
printf("Web: %s\n",buffer);
bzero(buffer,2056);
close(socket);
}
