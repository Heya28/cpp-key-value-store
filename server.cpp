#include<iostream> // standard I/O streams ( std::cout, std::cerr )
#include<sys/socket.h> // core socket definitions ( socket, bind, listen, accept )
#include<netinet/in.h> // structures for storing addresses ( sockaddr_in )
#include<unistd.h> // POSIX system API ( read, write, close )

int main(){
    // Step 1: socket() - Endpoint create
    // Creates an unbound socket in a specific domain and of a specific type.
    // AF_INET : Selects IPv4 Internet Protocol Family. 
    // SOCK_STREAM : Selects reliable, 2-way, connection-based byte streams ( TCP )
    // 0: Selects default protocol for given family/type ( TCP ).
    // Returns an fd ( file descriptor ) which is an index into kenrel's open file table. 
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0){
        std::cerr<<"Fatal Error: socket() filed to create file descriptor."<<std::endl;
        return 1;
    }

    // Step 2
    // sockaddr_in is the IPv4 - specific implementation of the generic 'sockaddr' struct
    // It must be zeroed out to prevent garbge values in padding bytes. 
    struct sockaddr_in address={};
    address.sin_family = AF_INET; // Must match the socket domain ( IPv4 )
    address.sin_addr.s_addr= INADDR_ANY; // INADDR_ANY (0.0.0.0) : Binds to ALL available network interfaces on this machine.
    // if used 127.0.0.1 only local processes could connect. 
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(1234); // htons() = Host TP Network Short. 
    // Converts the int 1234 from CPU's byte order to Network standard byte order reqd by TCP/IP Headers. 
}