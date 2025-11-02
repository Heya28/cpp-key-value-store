#include<iostream>
#include<string>
#include<sstream>
#include<unordered_map>

// manual implementation of trim function 
std::string trim(const std::string& str){
    size_t first=str.find_first_not_of(" \t\n\r"); // find first non-whitespace
    if(std::string::npos == first){ // if string is all whitespace
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

        // 2c. Extract command
        // find position of first space
        size_t first_space= input_line.find(' ');
        std::string command;
        if(first_space==std::string::npos){
            // no space found, entire line is command. 
            command=input_line;
        }else{
            command=input_line.substr(0,first_space);
        }

        // 2d. Handle EXIT command
        if(command=="EXIT"){
            std::cout<<"Goodbye!"<<std::endl;
            break; // break out of the while loop. 
        }
        // 2e. Handle SET command
        else if(command=="SET"){
            // SET key value is required. 
            // If first_space DNE -> INVALID NUMBER OF ARGUMENTS
            if(first_space==std::string::npos){
                std::cout<<"(error) wrong number of arguments for SET command."<<std::endl;
                continue;
            }
            // Find Key ( Find Second Space )
            size_t second_space=input_line.find(' ', first_space+1);
            if(second_space==std::string::npos){
                // no value only key 
                std::cout<<"(error) wrong number of arguments for SET command."<<std::endl;
                continue;
            }
            // Find Key ( keys cannot have whitespaces )
            std::string key= trim(input_line.substr(first_space+1,second_space-first_space-1));
            // Extract rest as Value. ( no trim, keep data )
            std::string value=input_line.substr(second_space+1);

            // empty key check. 
            if(key.empty()){
                std::cout<<"(error) Key cannot be empty."<<std::endl;
                continue;
            }
            // Store in Map
            storage[key]=value;
            std::cout<<"OK"<<std::endl;
        }
        else if(command=="GET"){
            // GET key
            if(first_space==std::string::npos){
                std::cout<<"(error) GET requires a key."<<std::endl;
                continue;
            }
            // check if key is valid. 
            // if there is any space after key
            size_t second_space=input_line.find(' ', first_space+1);
            if(second_space!=std::string::npos){
                std::cout<<"(error) GET takes only one argument."<<std::endl;
                continue;
            }
            std::string key = trim(input_line.substr(first_space+1));
            // incase of single white space npos cant check as no characters left to check. 
            if(key.empty()){
                std::cout<<"(error) Key cannot be empty."<<std::endl;
                continue;
            }
            if(storage.count(key)){
                std::cout<<"Value is "<<storage.at(key)<<std::endl;
            }else{
                std::cout<<"(nil)"<<std::endl;
            }
        }
        else if(command=="DEL"){
            // DEL key
            if(first_space==std::string::npos){
                std::cout<<"(error) DEL requires a key."<<std::endl;
                continue;
            }
            // check if key is valid
            // if there is any space after key
            size_t second_space=input_line.find(' ',first_space+1);
            if(second_space!=std::string::npos){
                std::cout<<"(error) DEL takes only one argument."<<std::endl;
                continue;
            }
            std::string key = trim(input_line.substr(first_space+1));
            // incase of single white space
            if(key.empty()){
                std::cout<<"(error) Key cannot be empty."<<std::endl;
                continue;
            }
            size_t deleted = storage.erase(key); // returns number deleted
            if(deleted>0){
                std::cout<<"OK"<<std::endl;
            }else{
                std::cout<<"(integer) 0"<<std::endl;
            }
        }else{
            std::cout<<"(error) Unknown command."<<std::endl;
        }
    }
    return 0;
}