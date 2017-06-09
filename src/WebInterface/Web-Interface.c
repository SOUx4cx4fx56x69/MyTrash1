#include "../socket/socket.h"
#include "../stratum.h"
#include "../main.h"
#include"../util.h"
#include "../base64.h"
#include <string.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>


static const char HTTP_OK[] = "HTTP/1.1 200 OK\n"
			"Content-type: text/html\n"
			"\r\n";
static const char HTTP_NOTFOUND[] = "HTTP/1.1 404 Not Found text/html";
#define HTTP_DIR "stratum_http_interface"
void * startWeb(void)
{
 int Web_socket;
 pthread_t Web;
 //printf("WEB: %s %d\n",host_web,port_web);
 initServ(host_web,port_web,Web_socket);
 pthread_create(&Web,0,(void*)AcceptClient_web,Web_socket);
 pthread_join(Web,NULL);
}
void * WebThread(int socket)
{
int file;
char * buffer = (char*)malloc(sizeof(char)*MINSIZE);
void * firstbuffer = buffer;
char page[2056];
unsigned int counter=0;
readFrom(socket,buffer);
int startGet = FindStartString(buffer,"GET ");
if(startGet == -1) goto out;

//printf("Web: %s\n",buffer);

buffer+=startGet;
buffer+=4;

while(*buffer == ' ' && *buffer)*buffer++;
if(!*buffer) goto out;
while(*buffer && *buffer != ' ') page[counter++]=*buffer++; 
counter=0;

if(strcmp(page,"/") == 0)
{
 sprintf(page,"%s/%s",HTTP_DIR,"index.html");
 file = open(page,O_RDONLY);
 if(file == -1) writeTo(socket,HTTP_NOTFOUND);
 else
 {
   writeTo(socket,HTTP_OK);
   do
   {
    buffer = firstbuffer;
    bzero(buffer,MINSIZE);
    read(file,buffer,MINSIZE-1);
    writeTo(socket,buffer);
    writeTo(socket,"\r\n");
    printf("%s\n",buffer);
   }while(*buffer);
    writeTo(socket,"\r\n\r\n");
 }

}else{
sprintf(page,"%s/%s",HTTP_DIR,page);
file = open(page,O_RDONLY);
if(file == -1) writeTo(socket,HTTP_NOTFOUND);
else
{
   writeTo(socket,HTTP_OK);
   do
   {
    buffer = firstbuffer;
    bzero(buffer,MINSIZE);
    read(file,buffer,MINSIZE-1);
    writeTo(socket,buffer);
    writeTo(socket,"\r\n");
   // printf("%s\n",buffer);
   }while(*buffer);
   writeTo(socket,"\r\n\r\n");
}

}
buffer = firstbuffer;
bzero(buffer,2056);
free(buffer);
close(file);
out:
close(socket);
}
