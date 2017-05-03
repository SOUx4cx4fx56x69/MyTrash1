void ToStratumClient(int socket)
{
char buffer[2056];
readFrom(socket,buffer);
printf("%s",buffer);
}
void main(void)
{
int sck = InitServer("127.0.0.1",9290);
AcceptClient(sck);
close(sck);
}
