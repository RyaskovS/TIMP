#include "BlockEncr.h"
BlockEncr::BlockEncr(int alg,const string& parole)
{
    alg=mode;
    password=parole;
}
void BlockEncr::Encrypt(const string& from_path, const string& to_path)
{
    if (mode ==1) {
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::PKCS12_PBKDF<CryptoPP::SHA512> obj;
        obj.DeriveKey(key.data(), key.size(), 0, (byte*)password.data(), password.size(), (byte*)trash.data(), trash.size(), 1024, 0.0f);
        CryptoPP::AutoSeededRandomPool prng;
        byte iv[CryptoPP::AES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));
        ofstream v_IV(string(to_path + "_vector").c_str(),ios::binary);
        v_IV.write((char*)iv, CryptoPP::AES::BLOCKSIZE);
        v_IV.close();
        cout << "Файл с вектором инициализации: " << to_path << "_vector" << endl;
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encr;
        encr.SetKeyWithIV(key, key.size(), iv);
        CryptoPP::FileSource fs(from_path.c_str(), true, new CryptoPP::StreamTransformationFilter(encr, new CryptoPP::FileSink(to_path.c_str())));
        cout << "Сохранено в файле: " << to_path << endl;
    } else {
        CryptoPP::SecByteBlock key(CryptoPP::DES::DEFAULT_KEYLENGTH);
        CryptoPP::PKCS12_PBKDF<CryptoPP::SHA512> obj;
        obj.DeriveKey(key.data(), key.size(), 0, (byte*)password.data(), password.size(), (byte*)trash.data(), trash.size(), 1024, 0.0f);
        CryptoPP::AutoSeededRandomPool prng;
        byte iv[CryptoPP::DES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));
        ofstream v_IV(string(to_path + "_vector").c_str(),ios::binary);//in = from             out = to
        v_IV.write((char*)iv, CryptoPP::DES::BLOCKSIZE);
        v_IV.close();
        cout << "Файл с вектором инициализации: " << to_path << "_vector" << endl;
        CryptoPP::CBC_Mode<CryptoPP::DES>::Encryption encr;
        encr.SetKeyWithIV(key, key.size(), iv);
        CryptoPP::FileSource fs(from_path.c_str(), true, new CryptoPP::StreamTransformationFilter(encr, new CryptoPP::FileSink(to_path.c_str())));
        cout << "Сохранено в файле: " << to_path << endl;
    }
}
void BlockEncr::Decrypt(const string& iv_path,const string& from_path, const string& to_path)
{
    //Генерируем ключ (нужно использовать такой же пароль)
    if (mode==1) {
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::PKCS12_PBKDF<CryptoPP::SHA512> pbkdf;
        pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)password.data(), password.size(), (byte*)trash.data(), trash.size(), 1024, 0.0f);
        byte iv[CryptoPP::AES::BLOCKSIZE];
        ifstream v_IV(iv_path, ios::in | ios::binary);
        v_IV.read(reinterpret_cast<char*>(&iv), CryptoPP::AES::BLOCKSIZE);
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decr;
        decr.SetKeyWithIV(key, key.size(), iv);
        CryptoPP::FileSource fs(from_path.c_str(), true, new CryptoPP::StreamTransformationFilter(decr, new CryptoPP::FileSink(to_path.c_str())));
        cout << "Сохранено в файле: " << to_path << endl;
    } else {
        CryptoPP::SecByteBlock key(CryptoPP::DES::DEFAULT_KEYLENGTH);
        CryptoPP::PKCS12_PBKDF<CryptoPP::SHA512> pbkdf;
        pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)password.data(), password.size(), (byte*)trash.data(), trash.size(), 1024, 0.0f);
        byte iv[CryptoPP::DES::BLOCKSIZE];
        ifstream v_IV(iv_path, ios::in | ios::binary);
        v_IV.read(reinterpret_cast<char*>(&iv), CryptoPP::DES::BLOCKSIZE);
        CryptoPP::CBC_Mode<CryptoPP::DES>::Decryption decr;
        decr.SetKeyWithIV(key, key.size(), iv);
        CryptoPP::FileSource fs(from_path.c_str(), true, new CryptoPP::StreamTransformationFilter(decr, new CryptoPP::FileSink(to_path.c_str())));
        cout << "Сохранено в файле: " << to_path << endl;
    }
}
