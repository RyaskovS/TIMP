#include <iostream>
#include "Tabl_Marsh.h"
#include <locale>
#include <string>
#include <stdexcept>
using namespace std;

int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    int st,ex;
    wstring text;
    wcout<<L"Введите ключ(кол-во столбцов): ";
    wcin>>st;
    try {
        if(((wcin.fail())or(st<=0))or(wcin.get() != '\n')) {
            throw invalid_argument("Must be a positive integer number");
        }
    } catch (const invalid_argument& ia) {
        wcerr<<L"Error: "<<ia.what()<<endl;
        return 1;
    }
    Tabl_Marsh shifr(st);
    while (true) {
        wcout<<L"Введите команду(0 - выход, 1 - дешифрование, 2 - шифрование): ";
        wcin>>ex;
        try {
            if((wcin.fail())or(wcin.get() != '\n')) {
                throw invalid_argument("Must be a positive integer number between 0 and 2");
            }
        } catch (const invalid_argument& ia) {
            wcerr<<L"Error: "<<ia.what()<<endl;
            return 2;
        }
        if ((ex>0)and(ex<=2)) {
            wcout<<L"Введите текст : ";
            wcin>>text;
            if (ex==1) {
                wcout<<L"Расшифрованный текст - "<<shifr.decrypt(text)<<endl;
            }
            if (ex==2) {
                wcout<<L"Зашифрованный текст - "<<shifr.encrypt(text)<<endl;
            }
        } else if (ex==0) {
            break;
        }
    }
return 0;
}
