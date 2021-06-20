#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main ()
{
    
    CryptoPP::SHA224 Hash;
    string path;
    cin>>path;
    ifstream HashFile;
    HashFile.exceptions(ifstream::failbit | ifstream::badbit);
    HashFile.open(path,ios::binary);
    HashFile.exceptions(ifstream::goodbit );
    char Bukva='\0';
    string FromFile="";
    while(HashFile.read(reinterpret_cast<char*>(&Bukva),sizeof(char))){
        FromFile += Bukva;
    }
    string hexed;
    string digest;
    string str="";
    Hash.Update(reinterpret_cast<const byte*>(FromFile.data()),FromFile.size());
    digest.resize(Hash.DigestSize());
    Hash.Final((byte*)&digest[0]);
    cout << "Хэш(SHA224) в 16-ричном формате : ";
    CryptoPP::StringSource ss(digest, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hexed)));
    cout <<hexed<< std::endl;
    return 0;
}