#include <iostream>
#include <cmath>
#include <cctype>
#include <string>

using namespace std;


class Vigenere{
    private:
    string key;

   string toUpper(string s){
    for(char &c : s){
        c = toupper(static_cast<unsigned char>(c));
    }
    return s;
}

    public:

    Vigenere(string key){
        if(key.empty()){
            throw invalid_argument("key should be at least of length 1");
        }
        for(char &c:key){
            c=toupper(static_cast<unsigned char>(c));
            if(c<'A'||c>'Z'){
                throw invalid_argument("key should be made of alphabetical characters");
                
            }
           
        }
        this->key=key;

    }
    string encrypt(string plaintext){
        string result="";
        plaintext=toUpper(plaintext);
        int counter=0;
        
        for(int i=0;i<plaintext.length();++i){
          
            if(plaintext[i]>='A' && plaintext[i]<='Z'){
            
            result+=(char)(((plaintext[i]-'A')+(key[counter%key.length()]-'A'))%26+'A');
            counter++;
            }
            else{
               result+=plaintext[i];
            }
        }
        return result;
    }

    string decrypt(string ciphertext){
        ciphertext=toUpper(ciphertext);
        string result="";
        int counter=0;
        for(int i=0;i<ciphertext.size();++i){
            if(ciphertext[i]>='A' && ciphertext[i]<='Z'){
            result+=(char)(((ciphertext[i]-'A')-(key[counter%key.length()]-'A')+26)%26+'A');
            counter++;
            }
            else{
                result+=ciphertext[i];
            }
        }
        return result;
        
    }


};



int main(){
    string key="deceptive";
    string message="we are discovered save yourself";
    Vigenere c=Vigenere(key);

    string cipher=c.encrypt(message);
    cout<<"Ciphertext: "<<cipher<<endl;

    string plaintext=c.decrypt(cipher);
    cout<<"Plaintext: "<<plaintext<<endl;


    return 0;
}