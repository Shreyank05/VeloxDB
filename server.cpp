#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h> //sock bind accept listen recv send etc
#include <netinet/in.h> // sockaddr htons ntohs etc
using namespace std;
#define PORT 1234
struct sockaddr_in addr;
int main()
{
    //socket initialization
    int soc = socket(AF_INET,SOCK_STREAM,0);
    if(soc<0)
    {
    cout<<"socket not opened"<<endl;
    exit(EXIT_FAILURE);
    }
    else cout<<"socket opened successfully"<<endl;
    
//initialize socket addr structure
/*struct sockaddr_in {
    short int          sin_family;  // Address family, AF_INET
    unsigned short int sin_port;    // Port number
    struct in_addr     sin_addr;    // Internet address
    unsigned char      sin_zero[8]; // Same size as struct sockaddr
};
*/
 // reuse address
int opt=1;
setsockopt(soc,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));


addr.sin_family=AF_INET;
addr.sin_port=htons(PORT);
addr.sin_addr.s_addr=INADDR_ANY;
int nret=0;
//bind the socket to local port
nret=bind(soc,(struct sockaddr*)&addr,sizeof(addr));
if(nret<0)
{
cout<<"failed to bind to local port"<<endl;
exit(EXIT_FAILURE);
}
else cout<<"successfully bind to local port"<<endl;
    

//listen the request from the client(queues the request)
nret=listen(soc,5);
if(nret<0)
{
    cout<<"failed to start listen to local port"<<endl;
exit(EXIT_FAILURE);
}
else cout<<"listening successfully"<<endl;


//accept generates new socket id this new socket id is used for communication with client
while(true)
{
int clientsocket=accept(soc,NULL,NULL);
if(clientsocket < 0)
{
    cout<<"failed to accept client"<<endl;
    continue;
}
else cout<<"client connected"<<endl;
char buffer[1024];
while(true) 
   {  
        nret=recv(clientsocket,buffer,sizeof(buffer),0);
        if(nret>0)
        {
            cout<<buffer<<endl;
        //response
        nret=send(clientsocket,"world",5,0);
        if(nret>0)
        cout<<"response sent successfully"<<endl;
        }
        else
        break;
        
    }
close(clientsocket);
}
close(soc);
return 0;

}
