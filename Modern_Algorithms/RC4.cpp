#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

class RC4{
    private:
     unsigned char state_array[256];
     string key;
     unsigned char keystream;
    
    public:
    RC4(string key){
        this->key=key;
    }
    
    string encrypt(string plaintext){
        key_schedule();
        int j=0;
        int i=0;
        string ciphertext="";
        for(int k=0;k<plaintext.size();++k){
            i=(i+1)%256;
            j=(j+state_array[i]) %256;
            swap(state_array[i],state_array[j]);
            int t=(state_array[i]+state_array[j])%256;
            keystream=(state_array[t]);
        
       
            ciphertext+=plaintext[k]^keystream;
        }
        return ciphertext;

      
        
    }

      string decrypt(string ciphertext){
        key_schedule();
        string plaintext="";
        int i=0,j=0;
            for(int k=0;k<ciphertext.size();++k){
                 i=(i+1)%256;
            j=(j+state_array[i]) %256;
            swap(state_array[i],state_array[j]);
            int t=(state_array[i]+state_array[j])%256;
            keystream=(state_array[t]);
                plaintext+=ciphertext[k]^keystream;
            }
            return plaintext;
        }
    private:
    void key_schedule(){
        for(int i=0;i<256;++i){
            state_array[i]=i;
        }
      
        int j=0;
        for(int i=0;i<256;++i){
            j=(j+state_array[i]+key[i % key.size()])%256;
          swap(state_array[i], state_array[j]);
        }
    }

    

};

int main(){

    cout<<"welcome to hamza's RC4 implementation\n";
   
   
    string plaintext="Hamza";
    string key="im the key";
   
    RC4 rc(key);
   string ciphertext = rc.encrypt(plaintext);

    cout << "Ciphertext (Hex): ";
    for(int i = 0; i < ciphertext.size(); ++i) {
        cout << hex << setw(2) << setfill('0') << (int)(unsigned char)ciphertext[i] << " ";
    }
    cout << dec << "\n";
    cout<<"decrypted : "<<rc.decrypt(ciphertext);



    return 0;
}