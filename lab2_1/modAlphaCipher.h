#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <iostream>
#include <cstring>
using namespace std;
class modAlphaCipher
{
private:
    wstring numAlpha2 =L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    wstring numAlpha =L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
    map <char,int> alphaNum; //ассоциативный массив "номер по символу"
    vector <int> key; //ключ
    vector<int> convert(const wstring& s); //преобразование строка-вектор
    wstring convert(const vector<int>& v); //преобразование вектор-строка
    inline wstring getValidKey(const wstring & s);
    inline wstring getValidOpenText(const wstring & s);
    inline wstring getValidCipherText(const wstring & s);
public:
    modAlphaCipher()=delete; //запретим конструктор без параметров
    modAlphaCipher(wstring& skey); //конструктор для установки ключа
    wstring encrypt(const wstring& open_text); //зашифрование
    wstring decrypt(const wstring& cipher_text);//расшифрование
    bool language(const wstring& skey);
};
class cipher_error: public invalid_argument {
public:
 explicit cipher_error (const string& what_arg):
invalid_argument(what_arg) {}
 explicit cipher_error (const char* what_arg):
 invalid_argument(what_arg) {}
 
};
