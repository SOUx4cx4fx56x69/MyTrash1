int CheckString(char*one,char*two,size_t len);
char * FindStartString(char*string,char*what);

#define Jumping(jumpTo,buffer,string){\
jumpTo = FindStartString(buffer,string);\
if(jumpTo == -1) return 0;\
buffer+=jumpTo;\
}
