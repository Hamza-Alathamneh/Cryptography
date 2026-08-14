#include "../Hlibraries/Hmath.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N_MOD  4294180819ULL   
#define PHI    4294049760ULL   

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long n);
int  RSA_encryption(char* plaintext, unsigned long long* ciphertext, unsigned long long pub, unsigned long long n);
void RSA_decryption(int* decrypted_text, unsigned long long* ciphertext, unsigned long long priv, unsigned long long n, int num_blocks);

int main(){
    char plaintext[] = "RSA is Fun";   
    unsigned long long ciphertext[256];
    int decrypted_text[256];
    long long d = extended_Euclidean(E_standard, PHI);
    if(d < 0) d += PHI;                         
    printf("d = %lld  (e*d mod phi = %llu)\n",
           d, ((unsigned long long)E_standard * (unsigned long long)d) % PHI);

    int bytespacked = RSA_encryption(plaintext, ciphertext, d, N_MOD);
    printf("Bytes packed: %d\n", bytespacked);

    printf("ciphertext:");
    for(int i = 0; i < bytespacked; ++i)        
        printf(" %llu", ciphertext[i]);
    printf("\n");

    

    RSA_decryption(decrypted_text, ciphertext, E_standard, N_MOD, bytespacked);

    printf("decrypted_text:\n");
    for(int i = 0; i < (int)strlen(plaintext); ++i)
        printf("%c", decrypted_text[i]);
    printf("\n");
    return 0;
}

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long n){
    unsigned long long res = 1;
    base %= n;
    while(exp > 0){
        if(exp & 1) res = (res * base) % n;
        exp >>= 1;
        base = (base * base) % n;
    }
    return res;
}

int RSA_encryption(char* plaintext, unsigned long long* ciphertext, unsigned long long pub, unsigned long long n){
    if(n < 256){ printf("Please enter a bigger n\n"); return 0; }

    int max_bytes = 0;
    unsigned long long max_val = 1;
    while(max_val * 256 < n){ max_bytes++; max_val *= 256; }

    int i = 0, c_idx = 0;
    while(plaintext[i] != '\0'){
        unsigned long long block = 0;
        int bytes_packed = 0;
        while(bytes_packed < max_bytes && plaintext[i] != '\0'){
            block = (block * 256) + (unsigned char)plaintext[i];
            bytes_packed++; i++;
        }
        ciphertext[c_idx++] = mod_exp(block, pub, n);
    }
    return c_idx;
}

void RSA_decryption(int* decrypted_text, unsigned long long* ciphertext, unsigned long long priv, unsigned long long n, int num_blocks){
    int text_idx = 0;
    for(int i = 0; i < num_blocks; i++){
        unsigned long long block = mod_exp(ciphertext[i], priv, n);
        char reversed_chars[8];
        int temp_idx = 0;
        while(block > 0){
            reversed_chars[temp_idx++] = (char)(block % 256);
            block /= 256;
        }
        for(int j = temp_idx - 1; j >= 0; --j)
            decrypted_text[text_idx++] = reversed_chars[j];
    }
    decrypted_text[text_idx] = '\0';
}