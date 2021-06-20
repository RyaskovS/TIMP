#include <iostream>
#include "BlockEncr.h"
int main(int argc, char **argv)
{
    int op;
    int mode;
    string from;
    string password;
    string to;
    string iv;
    do {
        cout<<"Выберите режим шифрования (1 - AES, 2 - DES, 0 - выход): ";
        cin>>op;
        if (op==1) {
            mode=1;
        } else if (op==2){
            mode =2;
        } else if (op==0) {
            break;
        }
            cout<<"Выберите режим работы (1 - шифрование, 2 расшифрование, 0 - вернуться): ";
            cin>>op;
            if (op==0){
                break;
            }
            cout<<"Укажите пароль: ";
            cin>>password;
            BlockEncr be(mode,password);
            if (op==1) {
                cout<<"Введите название файла: ";
                cin>>from;
                cout<<"Куда сохранить результат?: ";
                cin>>to;
                be.Encrypt(from,to);
            }
            else if (op==2){
                cout<<"Введите название файла: ";
                cin>>from;
                cout<<"Куда сохранить результат?: ";
                cin>>to;
                cout<<"Введите название файла с iv: ";
                cin>>iv;
                be.Decrypt(iv,from,to);
            }
    } while (true);
    return 0;
}
