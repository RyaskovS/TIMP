#include "StegProb.h"

int main(int argc, char **argv)
{
    string hidden,hide,cont;
    int ex,mode;
    cout<<"Введите режим работы(1 - Обычный, 2 - Инверсированный: ";
    cin>>mode;
    StegProb Steg(mode);
    try {
        Steg.CheckKey();
    } catch (const invalid_argument& ia) {
        cerr<<"Error: "<<ia.what()<<endl;;
        return 10;
    }
    while (true) {
        cout<<"Введите команду(0 - Выход, 1 - Скрыть информацию, 2 - Достать информацию, 3 - Получить справку): ";
        cin>>ex;
        try {
            if((cin.fail())or(cin.get() != '\n')or(ex>3) or (ex<0)) {
                throw invalid_argument("Неправильно введена операция");
            }
        } catch (const invalid_argument& ia) {
            cerr<<"Error: "<<ia.what()<<endl;
            return 2;
        }
        if (ex==1) {
            cout<<"Введите название файла(или полный путь), содержимое которого надо скрыть: ";
            getline(cin,hide);
            try {
                Steg.CheckFile(hide);
            } catch (const ifstream::failure & f) {
                cerr<<"Error: Ошибка открытия файла"<<endl;
                return 3;
            }
            cout<<"Введите название файла(или полный путь), в котором находится контейнер для скрытия: ";
            getline(cin,cont);
            try {
                Steg.CheckFile(cont);
            } catch (const ifstream::failure& f) {
                cerr<<"Error: Ошибка открытия файла-контейнера"<<endl;
                return 4;
            }
            try {
                Steg.hideInfo(hide,cont);
                cout<<"Информация скрыта в файле "<<cont<<"_copy"<<endl;
            } catch (const invalid_argument& ia) {
                cerr<<"Error: "<<ia.what()<<endl;
                return 6;
            }
        }
        if (ex==2) {
            cout<<"Введите название файла(или полный путь), содержимое которого надо достать: ";
            getline(cin,cont);
            try {
                Steg.CheckFile(cont);
            } catch (const ifstream::failure& f) {
                cerr<<"Error: Ошибка открытия файла"<<endl;
                return 5;
            }
            cout<<"Введите название файла(или полный путь), в котором будет находится информация, которую достали: ";
            getline(cin,hidden);
            try {
                Steg.getInfo(cont,hidden);
            } catch (const invalid_argument& ia) {
                cerr<<"Error: "<<ia.what()<<endl;
                return 7;
            }
            cout<<"Информация сохранена в файле "<<hidden<<endl;
        }
        if(ex==3) {
            Steg.getHelp();
        } else if (ex==0) {
            break;
        }
    }
    return 0;
}

