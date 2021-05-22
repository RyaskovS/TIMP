#pragma once
#include <string>
#include <locale>
using namespace std;
using namespace std;
class Tabl_Marsh
{
private:
    int key;
    wstring EngAlph=L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    wstring RusAlph=L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
public:
    Tabl_Marsh(){};
    Tabl_Marsh(int& skey);
    wstring encrypt(const wstring& open_text);
    wstring decrypt(const wstring& cipher_text);
    void Check(int skey);
};
