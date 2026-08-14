def encrypt(plainttext,key):
   result=""
   for i in plainttext:
      if i.isalpha():
         if i.isupper():
            result+=chr((ord(i)-ord('A')+key)%26+ord('A'))
         else:
            result+=chr((ord(i)-ord('a')+key)%26+ord('a'))
      else:
         result+=i
   return result

def decrypt(ciphertext,key):
   return encrypt(ciphertext,-key)

def main():
  plaintext=input("enter the text you want to encrypt")
  key=int(input("enter your key"))
  
  ciphertext=encrypt(plaintext,key)
  print(ciphertext)

  print(f"decryption: {decrypt(ciphertext,key)}")


if __name__ == "__main__":
    main()
