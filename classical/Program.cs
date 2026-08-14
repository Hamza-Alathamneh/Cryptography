using System;



namespace training
{
    class Program
    {
        static void Main(string[] args)
        {
            string key = "DK1VQF0IBJWP2ESC43XHT5MYA6UOL79RG8ZN";
            Monoalpabetic m = new Monoalpabetic(key);
            string message = "Now we just add numbers 123";
            string ciphertext=m.encrypt(message);
            string plaintext = m.decrypt(ciphertext);

            Console.WriteLine($"CipherText: {ciphertext}");

            Console.WriteLine($"PlainText: {plaintext}");
            

        }
    }
}
