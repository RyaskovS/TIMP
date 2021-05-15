#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"
#include <locale>
using namespace std;
int main(int argc, char **argv)
{
     try {
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    wstring key;
    wstring text;
    unsigned op;
    wcout<<L"Cipher ready. Input key: ";
    wcin>>key;
    modAlphaCipher cipher(key);
    if (!cipher.language(key)) {
        cerr<<"key not valid\n";
        return 1;
    }
    wcout<<L"Key loaded\n";
    do {
        wcout<<L"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
        wcin>>op;
        if (op > 2) {
            wcout<<L"Illegal operation\n";
        } else if (op >0) {
            wcout<<L"Cipher ready. Input text: ";
            wcin>>text;
            if (op==1) {
                    wcout<<L"Encrypted text: "<<cipher.encrypt(text)<<endl;
                } else {
                    wcout<<L"Decrypted text: "<<cipher.decrypt(text)<<endl;
                }
        }

    } while (op!=0);
    } catch(const cipher_error & e) {
    cerr<<"Error: "<<e.what()<<endl;
    }
    return 0;
}
