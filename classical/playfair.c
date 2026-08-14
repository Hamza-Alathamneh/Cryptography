#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>


char* removeDuplicates(char* key);
char* toLowerCase(char* key);
char* fillMatrix(char* key,char* matrix);
char* removeCharacters(char* key,char* alphabet);
char* encrypt(char* matrix,char* cipher_text,char* plain_text,int* x_holder);
char* decrypt(char* matrix,char* cipher_text,char* plain_text,int* x_holder);

int main(){
    char key[]="BaLlOon";
    char plain_text[]="success";
    int plainTextLen=sizeof(plain_text)/sizeof(char);
    int x_holders[2*plainTextLen+1];

   char modified_key[sizeof(key)];

   strcpy(modified_key,key);

   toLowerCase(modified_key);

   removeDuplicates(modified_key);
   char matrix[27]="";
   fillMatrix(modified_key, matrix);
   char cipher_text[2*plainTextLen+1];

   encrypt(matrix,cipher_text,plain_text,x_holders);

   printf("CipherText: %s\n",cipher_text);

   decrypt(matrix,cipher_text,plain_text,x_holders);

   printf("PlainText: %s\n",plain_text);
   

       return 0;
}

char* removeDuplicates(char* key){
    if(key==NULL) return NULL;

    bool seen[256]={false};

    int read_index=0;
    int write_index=0;

    while(key[read_index]!='\0'){
        unsigned char current_char=(unsigned char)key[read_index];

        if(!seen[current_char]){
            seen[current_char]=true;
            key[write_index]=key[read_index];
            write_index++;
        }
        read_index++;
    }
    key[write_index]='\0';

    return key;

}

char* toLowerCase(char* key){
    int i=0;
    while(key[i]!='\0'){
        key[i]=tolower((unsigned char)key[i]);
        i++;
    }
    return key;

}


char* removeCharacters(char* key, char* alphabet) {
    
    bool key_chars[256] = {false};

    for(int i = 0; key[i] != '\0'; ++i) {
        key_chars[(unsigned char)key[i]] = true;
    }

    int read_index = 0;
    int write_index = 0;

    while(alphabet[read_index] != '\0') {
        unsigned char current_char = (unsigned char)alphabet[read_index];

       

        if(!key_chars[current_char]) {
            alphabet[write_index] = alphabet[read_index];
            write_index++;
        }
        read_index++;
    }
    alphabet[write_index] = '\0';

    char* temp = realloc(alphabet, (write_index + 1) * sizeof(char));
    if (temp != NULL) {
        alphabet = temp; 
    }

    return alphabet;
}




char* fillMatrix(char* key, char* matrix) {
    
    int key_len = 0;
    
    
    while(key[key_len] != '\0') {
        matrix[key_len] = key[key_len];
        key_len++;
    }
    
    
    char* alphabet = malloc(27 * sizeof(char));
    int alphabet_index = 0; 
    
    for(int i = 0; i < 26; ++i) {
        if('a' + i == 'j') continue; 
        
        alphabet[alphabet_index] = 'a' + i;
        alphabet_index++; 
    }
    alphabet[alphabet_index] = '\0'; 
    
    
    alphabet = removeCharacters(key, alphabet);

    
    int i = 0;
    while(alphabet[i] != '\0') {
        
        matrix[key_len + i] = alphabet[i];
        i++;
    }
    
    matrix[key_len + i] = '\0';
    free(alphabet);
    return matrix;
}

char* encrypt(char* matrix, char* cipher_text, char* plain_text,int* x_holder) {
    char temp_list[100] = ""; 
    int i = 0; 
    int j = 0;
    int count_x=0;

   
    while(plain_text[i] != '\0') {
        
        char current = (plain_text[i] == 'j') ? 'i' : plain_text[i];
        char next = (plain_text[i+1] == 'j') ? 'i' : plain_text[i+1];

        if (next == '\0') {
           
            temp_list[j++] = current;
            temp_list[j++] = 'x';
            x_holder[count_x]=j-1;
            count_x++;
            i++; 
        } else if (current == next) {
           
            temp_list[j++] = current;
            temp_list[j++] = 'x';
            x_holder[count_x]=j-1;
            count_x++;
            i++; 
        } else {
           
            temp_list[j++] = current;
            temp_list[j++] = next;
            i += 2; 
        }
    }
    temp_list[j] = '\0';
    x_holder[count_x] = -1;   

    printf("Plaintext: %s\n", temp_list);

    int k = 0; 
    
    while(temp_list[k] != '\0' && temp_list[k+1] != '\0') {
        char char_A = temp_list[k];
        char char_B = temp_list[k+1];

        char* pos_A = strchr(matrix, char_A);
        char* pos_B = strchr(matrix, char_B);
        if(pos_A==NULL || pos_B==NULL){
            printf("please enter characters from [a-z]\n");
            cipher_text[0]='\0';
            return cipher_text;
        }

        int index_A = pos_A - matrix;
        int index_B = pos_B - matrix;

        int row_A = index_A / 5;
        int col_A = index_A % 5;
        int row_B = index_B / 5;
        int col_B = index_B % 5;

        if (row_A == row_B) {
            cipher_text[k]   = matrix[(row_A * 5) + ((col_A + 1) % 5)];
            cipher_text[k+1] = matrix[(row_B * 5) + ((col_B + 1) % 5)];
            
        } else if (col_A == col_B) {
            cipher_text[k]   = matrix[(((row_A + 1) % 5) * 5) + col_A];
            cipher_text[k+1] = matrix[(((row_B + 1) % 5) * 5) + col_B];
            
        } else {
            cipher_text[k]   = matrix[(row_A * 5) + col_B];
            cipher_text[k+1] = matrix[(row_B * 5) + col_A];
        }

        k += 2; 
    }
    cipher_text[k] = '\0';

    return cipher_text;
}

char* decrypt(char* matrix,char* cipher_text,char* plain_text,int* x_holder){
    int k=0;
    int temp_len=strlen(cipher_text);
    char temp[temp_len];
    
    while(cipher_text[k]!='\0' && cipher_text[k+1] !='\0'){
        char char_A=cipher_text[k];
        char char_B=cipher_text[k+1];

        char* pos_A = strchr(matrix, char_A);
        char* pos_B = strchr(matrix, char_B);
        if(pos_A==NULL || pos_B==NULL){
            printf("invalid character in ciphertext\n");
            plain_text[0]='\0';
            return plain_text;
        }

        int index_A = pos_A - matrix;
        int index_B = pos_B - matrix;
        
        int row_A = index_A / 5;
        int col_A = index_A % 5;
        int row_B = index_B / 5;
        int col_B = index_B % 5;

        if(row_A==row_B){
              temp[k]=matrix[(row_A*5)+((col_A+4)%5)];
              temp[k+1]=matrix[(row_B*5)+((col_B+4)%5)];
        }
        else if(col_A==col_B){
              temp[k]=matrix[(((row_A+4)%5)*5)+(col_A)];
              temp[k+1]=matrix[(((row_B+4)%5)*5)+col_B];
        }
        else{
              temp[k]=matrix[(row_A*5)+col_B];
              temp[k+1]=matrix[(row_B*5)+col_A];
        }
        k+=2;

    }
    int i=0,j=0,b=0;
    for(;i<temp_len;i++){
        if(temp[i]=='x' && x_holder[j]==i){
            j++;
            continue;
        }
        plain_text[b]=temp[i];
        b++;
    }
    plain_text[b]='\0';
    return plain_text;
}
