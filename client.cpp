#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
#define port 1234
struct sockaddr_in addr;
int main()
{
int soc=socket(AF_INET,SOCK_STREAM,0);
if(soc<0)
{
    cout<<"socket not opened"<<endl;
    exit(EXIT_FAILURE);
}
addr.sin_family=AF_INET;
addr.sin_port=htons(port);
addr.sin_addr.s_addr=inet_addr("127.0.0.1");

int nret=connect(soc,(struct sockaddr*)&addr,sizeof(addr));
if(nret<0)
{
    cout<<"connection failed"<<endl;
    exit(EXIT_FAILURE);
}
while(true)
{
    string msg;
    cout<<"enter the message"<<endl;
    getline(cin, msg);
   nret=send(soc, msg.c_str(), msg.length(), 0);
    if(nret<0)
    {
        cout<<"send failed"<<endl;
        exit(EXIT_FAILURE);
    }
    else
    cout<<"message sent successfully"<<endl;
    //recive response
    char buffer[1024];
    nret=recv(soc,buffer,sizeof(buffer),0);
    if(nret>0)
    {   cout<<"recived from server"<<endl;
        cout<<buffer<<endl;
    }
    
}
    close(soc);
    return 0;
}