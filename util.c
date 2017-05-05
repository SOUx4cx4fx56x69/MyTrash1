#include "main.h"
#include <string.h>
void error(char*msg)
{
 fprintf(stderr,"%s\n",msg);
 exit(-1);
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
buffer=firstAddrBuf;
tmp=firstAddrTmp;

while(*tmp)
 *buffer++=*tmp++;

*buffer++='\0';

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
char * FindStartString(char*string,char*what)
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

