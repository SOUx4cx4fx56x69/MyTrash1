int CheckString(char*one,char*two,size_t len);
char * FindStartString(char*string,char*what);
void ReverseString(char*buffer);
#define Jumping(jumpTo,buffer,string){\
jumpTo = FindStartString(buffer,string);\
if(jumpTo == -1) return 0;\
buffer+=jumpTo;\
}

#define TO_BRACKETS(buffer)\
while(*buffer != '"' && *buffer)*buffer++;\
if(*buffer != '"') return 0;\
*buffer++;

#define TO_CHAR(buffer,_char)\
while(*buffer != _char && *buffer)*buffer++;\
if(*buffer != _char) return 0;\
*buffer++;


#define GET_STR(buffer,jumpTo,ArrayInfo,indexForArray,aString)\
Jumping(jumpTo,buffer,aString);\
TO_BRACKETS(buffer); \
TO_BRACKETS(buffer);\
buffer+=getP(buffer,ArrayInfo[indexForArray],'"'); 

#define GET_NUMBER(buffer,jumpTo,ArrayInfo,indexForArray,aString)\
Jumping(jumpTo,buffer,aString);\
TO_BRACKETS(buffer); \
TO_CHAR(buffer,':');\
buffer+=getP(buffer,ArrayInfo[indexForArray],',');

