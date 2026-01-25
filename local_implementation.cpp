#include<iostream>
#include<string>
#include<sstream>
#include<unordered_map>

// manual implementation of trim function 
std::string trim(const std::string& str){
    size_t first=str.find_first_not_of(" \t\n\r"); // find first non-whitespace
    if( first == std::string::npos){ // if string is all whitespace
        return ""; // empty string
    }
    size_t last=str.find_last_not_of(" \t\n\r"); // find last non-white space
    return str.substr(first, last-first+1);
}
int main(){
    std::cout<<"Welcome to your C++ Key-Value Store"<<std::endl;
    std::cout<<"Commands: SET key value, GET key, DEL key, EXIT"<<std::endl;
    
    // 1.  storage using unordered_map
    std::unordered_map<std::string,std::string> storage;
    
    // 2.  loop runs forever until "EXIT" is typed. 
    while(true){
        std::cout<<">"; // command prompt

        // 2a. read input line
        std::string input_line;
        getline(std::cin,input_line);

        // 2b. Handling commands
        // check to see if user just pressed enter
        if(input_line.empty()){
            continue; // go back to starting of the loop. 
        }

        // 2c. Parsing using more robust stringstream
        std::stringstream ss(input_line);
        std::string command,key,value,extra;

        // 2c. Extract command
        // find position of first space
        ss>>command; // stringstream automically skips leading whitespace ( does not matter if 1 or 20 )

        // 2d. Handle EXIT command
        if(command=="EXIT"){
            // Edge Case: Check for "EXIT extra stuff"
            if(ss>>extra){
                std::cout<<"(error) Wrong Number of arguments for 'EXIT' Command. "<<std::endl;
                continue;
            }
            std::cout<<"Goodbye!"<<std::endl;
            break; // break out of the while loop. 
        }
        // 2e. Handle SET command
        else if(command=="SET"){
            // User types SET ( and nothing else or just whitespaces )
            if(!(ss>>key)){
                std::cout<<"(error) wrong number of arguments for 'SET' Command."<<std::endl;
                continue;
            }
            // Get the value ( including spaces )
            std::getline(ss,value);
            value=trim(value); // Trim value ( which may just be an empty space )

            // check if empty string
            if(value.empty()){
                std::cout<<"(error) wrong number of arguments for 'SET' command. Value cannot be empty."<<std::endl;
                continue;
            }            
            // Store in Map
            storage[key]=value; // overwrites or creates a new key-value pair. 
            std::cout<<"OK"<<std::endl;
        }
        else if(command=="GET"){
            // GET key
            if(!(ss>>key)){ // also checks if key is valid ( key must not be whitespaces and key is a single word. )
                std::cout<<"(error) 'GET' requires a key."<<std::endl;
                continue;
            }
            // check if an extra number of values exist.
            if(ss>>extra){
                std::cout<<"(error) wrong number of arguments for 'GET' command."<<std::endl;
                continue;
            } 
            // retrieve the value at key and check if key exists in storage
            if(storage.count(key)){
                std::cout<<storage.at(key)<<std::endl;
            }else{
                std::cout<<"(nil)"<<std::endl; // not found response. 
            }
        }
        else if(command=="DEL"){
            // check that key exists 
            if(!(ss>>key)){
                std::cout<<"(error) 'DEL' requires a key"<<std::endl;
                continue;
            }
            // check if extra values exist
            if(ss>>extra){
                std::cout<<"(error) wrong number of arguments for 'DEL' command."<<std::endl;
                continue;
            }
            // erasing the key
            if(storage.erase(key)>0){
                std::cout<<"OK"<<std::endl;
            }else{
                std::cout<<"(error) key not found."<<std::endl;
            }
        }else{ // catch-all for unknown commands.
            std::cout<<"(error) Unknown command. '"<<command<<"'"<<std::endl;
        }
    }
    return 0;
}