using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace training
{
    class Monoalpabetic
    {
        private const string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        private readonly string _key;
        public Monoalpabetic(string key) {
            key = key.ToUpper();
            if (key.Length != 36)
                throw new ArgumentException("key must be 36 letters long.");

            bool flag = key.All(c => (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
            if(!flag || key.Distinct().Count() != 36)
            {
                throw new ArgumentException("Key must contain [A-Z]/[0-9] and each character must be unique");
            }

            _key = key;
        }
        public string encrypt(string message) {
            string result = "";
            
            message = message.ToUpper();
            
            for(int i = 0; i < message.Length; ++i)
            {
                if (message[i] >= 'A' && message[i] <= 'Z')
                {
                    result += _key[message[i] - 'A'];
                }
                else if (message[i] >= '0' && message[i] <= '9')
                {
                    result += _key[message[i] - '0'+26];
                }
                else {
                    result += " ";
                }
            }

            return result;
        }

        public string decrypt(string ciphertext)
        {
            
            string result = "";
            for(int i = 0; i < ciphertext.Length; ++i)
            {
                if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
                {
                    for (int j = 0; j < 36; ++j)
                    {
                        if (_key[j] == ciphertext[i])
                        {
                            result += Alphabet[j];
                            break;
                        }
                    }

                }
                else if (ciphertext[i] >= '0' && ciphertext[i] <= '9')
                {
                    for (int j = 0; j < 36; ++j)
                    {
                        if (_key[j] == ciphertext[i])
                        {
                            result += Alphabet[j];
                            break;
                        }
                    }

                }
                else {
                    result += " ";
                }

            }

            return result;
        }
    }
}
