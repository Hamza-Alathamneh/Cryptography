#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdint>
#include <cmath>

using namespace std;


class MD5{
   

    private:
    string result;

    unsigned int s[64]={7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
     4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    uint32_t k[64] = {
    0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
    0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
    0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
    0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
    0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
    0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
    0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};

    uint32_t ROL1(uint32_t num,unsigned int amount){
        return (num<<amount)|(num>>(32-amount));
    }

    string hexToString(uint32_t num){
        stringstream stream;

         for(int i=0; i<4; ++i){
        stream << hex << setw(2) << setfill('0') << ((num >> (i*8)) & 0xff);
    }
        return stream.str();
    }

     string hashAlgo(string message){
        uint64_t bitLen=message.length() * 8;
        int x=0;
         while((message.length()*8)%512!=448){
            if(x<1){
                message+=0x80;
                x++;
            }
            
        message +=(char)0x00;
    }
    for(int shift=0;shift<64;shift+=8){
        message +=(char)((bitLen >> shift)& 0xff);
      }
      
      uint32_t w[80];
       int g;
      uint32_t A = 0x67452301, B = 0xefcdab89, C = 0x98badcfe, D = 0x10325476;
      uint32_t F,sum=0;
      size_t numOfBlocks=message.length()/64;
      for(size_t t=0;t<numOfBlocks;++t){
        uint32_t AA=A,BB=B,CC=C,DD=D;
         for(int i=0;i<16;++i){
        w[i]=((uint8_t)message[t*64 + i*4]) |
             ((uint8_t)message[t*64 + i*4+1] <<8)|
             (((uint8_t)message[t*64 + i*4+2] <<16))|
             (((uint8_t)message[t*64 + i*4+3]<<24));
            }
        for(int i=0;i<64;++i){
           

            if(i<16){
                F=(B&C)|(~B & D);
                g=i;
                
               
                sum=A+F+k[i]+w[g];
                uint32_t oldB=B;
                uint32_t temp=D;
                D=C;
                C=oldB;
                B=oldB+ROL1(sum,s[i]);
                A=temp;

            }
            else if(i>=16&i<32){
                F=(B&D)|(C&(~D));
                g=(5*i+1)%16;
                
               
                 sum=A+F+k[i]+w[g];
                uint32_t oldB=B;
                uint32_t temp=D;
                D=C;
                C=oldB;
                B=oldB+ROL1(sum,s[i]);
                A=temp;
            }
            else if(i>=32&i<48){
                F=B^C^D;
                g=(3*i+5)%16;
               
                
                 sum=A+F+k[i]+w[g];
                uint32_t oldB=B;
                uint32_t temp=D;
                D=C;
                C=oldB;
                B=oldB+ROL1(sum,s[i]);
                A=temp;
            }
            else if(i>=48&i<64){
                F=C^(B|(~D));
                g=(7*i)%16;
               
               
                sum=A+F+k[i]+w[g];
                uint32_t oldB=B;
                uint32_t temp=D;
                D=C;
                C=oldB;
                B=oldB+ROL1(sum,s[i]);
                A=temp;
            }
            
       }
        A += AA; B += BB; C += CC; D += DD;
    }
    result=hexToString(A)+hexToString(B)+hexToString(C)+hexToString(D);
    return result;
}


     public:
    MD5(){}

   void Hash(string message){
    cout<<"Result:  "+hashAlgo(message);
}

};

int main(){

    MD5 m1=MD5();
    m1.Hash("Reverse the Planet");

    return 0;
}