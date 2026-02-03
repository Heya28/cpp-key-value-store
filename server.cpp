#include<iostream> // standard I/O streams ( std::cout, std::cerr )
#include<sys/socket.h> // core socket definitions ( socket, bind, listen, accept )
#include<netinet/in.h> // structures for storing addresses ( sockaddr_in )
#include<unistd.h> // POSIX system API ( read, write, close )

int main(){
   // 1. create socket
   int fd=socket(AF_INET,SOCK_STREAM,0);
   // AF_INET is for IPv4.
   // SOCK_STREAM is for TCP. 

   // 2. setup address
   struct sockaddr_in addr={};
   addr.sin_family = AF_INET;
   addr.sin_port = ntohs(1234);
   addr.sin_addr.s_addr= ntohl(0); // 0.0.0.0 any address

   // 3. bind and listen
   bind(fd, (const sockaddr *)& addr, sizeof(addr));
   listen(fd,SOMAXCONN);
   std::cout<<"Server is open on port 1234."<<std::endl;

   while(true){
    // logic
   }
   return 0;

}