#include "main.h"
#include "util.h"
#include <stdarg.h>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>


void error(char*msg)
{
 fprintf(stderr,"%s\n",msg);
 exit(-1);
}
void ASCIIToBin(char*ascii)
{
void * first = ascii;
while(*ascii)
{
 if(*ascii % 2)
   *ascii='1';
 else
   *ascii='0';
 *ascii++;
}
//ReverseString(ascii);
}
void ReverseString(char*buffer)
{
//#warning this function not does anyone testing
void * firstAddrBuf = buffer;
unsigned int c = strlen(buffer);
char * tmp = (char*)malloc( (sizeof(char)*c) +1);
if(tmp == NULL) error("Not can allocate memory");
void * firstAddrTmp = tmp;
while(*buffer)
  *buffer++;
for(int i = c;i--;)
{
 if(*buffer == '\0')*buffer--;
 *tmp++=*buffer--;
}
*tmp++='\0';
buffer=firstAddrBuf;
tmp=firstAddrTmp;

while(*tmp)
 *buffer++=*tmp++;
free(firstAddrTmp);
}

//int CheckStrings(char*where,int len,...)
int CheckString(char*one,char*two,size_t len)
{
for(int i = 0;i<len;i++)
 {
  if( (!*(one+i)) || (!*(two+i)) || *(one+i) != *(two+i) ) return 0;
 }
return 1;
}

//void findinstrings(char*what,...)
int FindStartString(char*string,char*what)
{
if( !*what || !*string ) return 0;
size_t sizeLen = strlen( what );
int counter = 0;

while(*string)

 {
 if(*string == *what)
  if( CheckString(string,what,sizeLen) ) return counter;
 
 counter++;
 *string++;
 }

return -1;
}

void applog(unsigned int type,const char*frmt,...)
{

time_t tim;
time(&tim);
struct tm* time_info;
time_info = localtime(&tim);

char time_tmp[26];
char buffer[36];
strftime(time_tmp, 26, "[%Y-%m-%d %H:%M:%S]", time_info);

va_list ap;
char * arg;
va_start(ap, frmt);
switch(type)
{
case INFO:
 sprintf(buffer,"%sINFO: ",time_tmp);
 fprintf(stdout,"%s",buffer);
 vfprintf (stdout,frmt, ap);
break;
case WARNING:
 sprintf(buffer,"%sWARNING: ",time_tmp);
 fprintf(stderr,"%s",buffer);
 vfprintf (stderr, frmt, ap);
break;
case ERROR:
 sprintf(buffer,"%sERROR: ",time_tmp);
 fprintf(stderr,"%s",buffer);
 vfprintf (stderr, frmt, ap);
break;
case DEBUG:
 sprintf(buffer,"%sDEBUG: ",time_tmp);
 fprintf(stdout,"%s",buffer);
 vfprintf (stdout, frmt, ap);
break;
}
puts("");
va_end(ap);

}

void help(void)
{
puts
(
"Test stratum server for gostcoin pool\n"
"-h get help\n"
"-a adress RPC\n"
"-p port RPC\n"
"-u UserName RPC\n"
"-w Password RPC\n"
"-m maxUsers\n"
"-i webInterface 'host:port' null/empty for disable"
);
exit(1);
}
