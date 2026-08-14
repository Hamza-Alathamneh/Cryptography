#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstdint>

using namespace std;

class sha1{

    public:
    sha1(){};
    string result;

    string hash(string message){
       
    uint32_t h0 = 0x67452301,h1 = 0xEFCDAB89,h2 = 0x98BADCFE,h3 = 0x10325476,h4 = 0xC3D2E1F0;
    uint64_t bitLen=message.length()*8;
    message +=(char)0x80;
    while((message.length()*8)%512!=448){
        message +=(char)0x00;
    }
      for(int shift=56;shift>=0;shift-=8){
        message +=(char)((bitLen >> shift)& 0xff);
      }
     
      uint32_t w[80];
      size_t numBlocks = message.length() / 64;
      for(size_t t=0;t<numBlocks;++t){
     for(int i=0;i<16;++i){
        w[i]=((uint8_t)message[t*64 + i*4] <<24) |
             ((uint8_t)message[t*64 + i*4+1] <<16)|
             (((uint8_t)message[t*64 + i*4+2] <<8))|
             (((uint8_t)message[t*64 + i*4+3]));
            
             
           
     }
     uint32_t a=h0,b=h1,c=h2,d=h3,e=h4;
             
    for(int t=16;t<80;++t){
                w[t]=ROL1(w[t-3]^w[t-8]^w[t-14]^w[t-16],1);
             }
    for(int t=0;t<80;++t){
        uint32_t k[4]={0x5A827999,0x6ED9EBA1,0x8F1BBCDC,0xCA62C1D6};
        uint32_t f[4]={(b & c)|((~b)&d),b^c^d,(b & c)|(b & d)|(c & d),b^c^d};

        uint32_t temp=ROL1(a,5)+f[t/20]+e+w[t]+k[t/20];
        e=d; d=c; c=ROL1(b,30); b=a; a=temp;
    }
    h0=h0+a; h1=h1+b; h2=h2+c; h3=h3+d; h4=h4+e;
    }
    result=hexToString(h0)+hexToString(h1)+hexToString(h2)+hexToString(h3)+hexToString(h4);
    return result;
    }

    void hashPrint(){
        cout<<"Sha1: "<<result;
    }

   

    private:
    uint32_t ROL1(uint32_t num,unsigned int amount){
        return (num<<amount)|(num>>(32-amount));
    }

    string hexToString(uint32_t num){
        stringstream stream;

        stream << hex << setw(8) << setfill('0') << num;
        return stream.str();
    }

    
};


int main(){
sha1 test=sha1();
test.hash("Reverse the Planet");
test.hashPrint();

}