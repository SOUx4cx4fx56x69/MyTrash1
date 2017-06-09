int CheckString(char*one,char*two,size_t len);
int FindStartString(char*string,char*what);
void ReverseString(char*buffer);
void applog(unsigned int type,const char*frmt,...);
void ASCIIToBin(char*ascii);
void help(void);
typedef enum
{
INFO,WARNING,ERROR,DEBUG
}infotype;


#define Jumping(jumpTo,buffer,string){\
jumpTo = FindStartString(buffer,string);\
buffer+=jumpTo;\
}

#define TO_BRACKETS(buffer)\
while(*buffer != '"' && *buffer)*buffer++;\
*buffer++;

#define TO_CHAR(buffer,_char)\
while(*buffer != _char && *buffer)*buffer++;\
*buffer++;


#define GET_STR(buffer,jumpTo,ArrayInfo,indexForArray,aString)\
Jumping(jumpTo,buffer,aString);\
TO_BRACKETS(buffer); \
TO_BRACKETS(buffer);\
jumpTo=getP(buffer,ArrayInfo[indexForArray],'"');\
if(jumpTo == 0) ArrayInfo[indexForArray][0]='\0';\
buffer+=jumpTo; 

#define GET_NUMBER(buffer,jumpTo,ArrayInfo,indexForArray,aString)\
Jumping(jumpTo,buffer,aString);\
TO_BRACKETS(buffer); \
TO_CHAR(buffer,':');\
jumpTo=getP(buffer,ArrayInfo[indexForArray],'"');\
if(jumpTo == 0) ArrayInfo[indexForArray][0]='\0';\
buffer+=jumpTo;

