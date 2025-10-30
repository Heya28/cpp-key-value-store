#include<iostream>
#include<string>
#include<sstream>
#include<unordered_map>
#include<vector>

using namespace std;
int main(){
    cout<<"Welcome to your C++ Key-Value Store"<<endl;
    cout<<"Commands: SET key value, GET key, DEL key, EXIT"<<endl;
    
    // 1.  storage using unordered_map
    unordered_map<string,string> storage;
    
    // 2.  loop runs forever until "EXIT" is typed. 
    while(true){
        cout<<">"; // command prompt

        // 2a. read input line
        string input_line;
        getline(cin,input_line);

        // 2b. using stringstream to spilt input_line into words that are stored in a vector.
        string word;
        stringstream ss(input_line);
        vector<string> words;
        while(ss>>word){
            words.push_back(word);
        }

        // 2c. Handling commands
        // check to see if user just pressed enter
        if(words.empty()){
            continue; // go back to starting of the loop. 
        }

        // first word is the command
        string command = words[0];

        if(command=="EXIT"){
            cout<<"Goodbye!"<<endl;
            break; // break out of the while loop. 
        }
        else if(command=="SET"){
            // ensuring that words.size() == 3 as SET command is SET, key, value. 
            if(words.size()<3){
                cout<<"(error) wrong number of arguments for SET command."<<endl;
                continue;
            }
            string value=words[2];
            for(size_t i=3; i<words.size();i++){
                value+=" "+words[i];
            }
            storage[words[1]]=value; // insert will not overwrite. 
            cout<<"OK"<<endl;
        }
        else if(command=="GET"){
            if(words.size()!=2){
                cout<<"(error) wrong number of arguments for GET command."<<endl;
                continue;
            }
            // checking if key exists in unordered_map or not. 
            if(storage.count(words[1])){
                cout<<"Value is "<<storage.at(words[1])<<endl;
            }else{
                cout<<"(nil)"<<endl;
            }
        }
        else if(command=="DEL"){
            if(words.size()!=2){
                cout<<"(error) wrong number of arguments for DEL command."<<endl;
                continue;
            }
            storage.erase(words[1]); // note : this works even if the key does not exist. 
            cout<<"OK"<<endl;
        }else{
            cout<<"(error) Unknown command."<<endl;
        }
    }
    return 0;
}