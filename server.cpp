#include<iostream> // standard I/O streams ( std::cout, std::cerr )
#include<sys/socket.h> // Main Socket API -> core socket definitions ( socket, bind, listen, accept )
#include<netinet/in.h> // IP structures for storing addresses ( sockaddr_in )
#include<unistd.h> // POSIX system API ( read, write, close )
#include<vector>
#include<cstring> // std::strerror ( coverts error codes to text )
#include<cerrno> // errno variable

// helper : kills app if system call fails as fail fast is better than continuing with a broken server
void chek(int result, const char* msg){
   if(result<0){
      std::cerr<<"SYSCALL ERROR: "<<msg<<" ("<<std::strerror(errno) <<")\n";
      exit(1);
   }
}
int main(){
   // 1. create socket
   int server_fd=socket(AF_INET,SOCK_STREAM,0);
   // checking 
   check(server_fd,"socket() failed");

   // configuring TCB to allow reusing port even if port busy. 
   int val=1;
   setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDDR,&val, sizeof(val));

   // 2. setup address
   struct sockaddr_in addr={};
   addr.sin_family = AF_INET;
   addr.sin_port = htons(1234); // Port 1234 (Big Endian)
   addr.sin_addr.s_addr= INADDR_ANY; // 0.0.0.0 any address, that is listen on all Interfaces

   // 3. bind and listen
   check(bind(server_fd, (sockaddr *)& addr, sizeof(addr)), "bind() failed");
   check(listen(server_fd,SOMAXCONN), "listen() failed");
   std::cout<<">>> Server is listening on port 1234."<<std::endl;

   while(true){
    // logic
   }
   return 0;

}