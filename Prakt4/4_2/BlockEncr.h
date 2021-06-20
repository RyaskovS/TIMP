#pragma once
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/des.h>
#include <cryptopp/aes.h>
#include <cryptopp/base64.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include "cryptopp/modes.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class BlockEncr{
private:
    int mode;
    string password;
    string trash="aswgethj5weymjnetje5yj";
public:
    BlockEncr(int alg,const string& parole);
    void Encrypt(const string& from_path, const string& to_path);
    void Decrypt(const string& iv_path,const string& from_path, const string& to_path);
};