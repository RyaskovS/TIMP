#include "StegProb.h"

StegProb::StegProb(const int& ch)
{
    mode=ch;
}
void::StegProb::hideInfo(const string& hide_path,const string& cont_path)
{
    string text,stroka;
    fstream hide;
    hide.open(hide_path, ios_base::in);
    fstream cont;
   cont.open(cont_path, ios_base::in|ios_base::out);
    getline(hide,stroka,'\0');
    for (long unsigned int i=0;i<stroka.size();i++){
        if (stroka[i]=='\n'){
            stroka.erase(i);
        }
    }
    hide.close();
    getline(cont,text,'\0');
    cont.close();
    long unsigned int space=0;
    int pos=0;
    for (long unsigned int i=0; i<text.size(); i++) {
        if (text[i]==' ') {
            space++;
        }
    }
    if (space!=8*stroka.size()){
        throw invalid_argument("Количество пробелов в контейнере не подходит для скрытия сообщения");
    }
    unsigned char chislo=0b00000000;
    unsigned char newchislo=0b00000000;
    unsigned char digit=0b00000000;
    unsigned char edinica=0b10000000;
    unsigned char zero=0b00000000;
    unsigned char buf;
    if (mode==2){
        buf=edinica;
        edinica=zero;
        zero=buf;
    }
    hide.open(hide_path, ios_base::in|ios::binary);
    while(hide.read(reinterpret_cast<char*>(&chislo),sizeof(unsigned char))) {
        if (chislo!=0b00001010) {
            for (int i=0; i<8; i++) {
                newchislo=chislo&0b10000000;
                digit<<=1;
                if (newchislo==edinica) {
                    text.insert(text.find(' ',pos),1,' ');
                    pos=text.find(' ',pos)+2;
                    digit+=0b00000001;
                } else if (newchislo ==zero) {
                    pos=text.find(' ',pos)+1;
                }
                chislo<<=1;
            }
        }
    }
    fstream new_cont;
    string new_path=cont_path+"_copy";
    new_cont.open(new_path,ios_base::out|ios_base::trunc);
    new_cont<<text;
    new_cont.close();
    cont.close();
    hide.close();

}
void::StegProb::getInfo(const string& cont_path,const string& hidden_path)
{
    string text;
    fstream cont;
    fstream hidden;
    fstream hidden_copy;
    cont.open(cont_path, ios_base::in);
    hidden.open(hidden_path,ios_base::out|ios_base::binary);
    getline(cont,text,'\0');
    int space=0;
    cont.close();
    unsigned char chislo=0b00000000;
    string newtext=text;
    for (long unsigned int i=0; i<text.size(); i++) {
        if ((newtext[i]==' ')and(newtext[i+1]==' ')) {
            newtext.erase(i,1);
        }
    }
    for (long unsigned int i=0; i<newtext.size(); i++) {
        if(newtext[i]==' ') {
            space++;
        }
    }
    int bytes=space/8;
    int pos=0;
    unsigned char edinica=0b00000001;
    unsigned char zero=0b00000000;
    unsigned char buf;
    if (mode==2){
        buf=edinica;
        edinica=zero;
        zero=buf;
    }
    for (int i=0; i<bytes; i++) {
        for (int j=0; j<8; j++) {
            chislo<<=1;
            if (text[text.find(' ',pos)+1]==' ') {
                pos=text.find(' ',pos)+2;
                chislo+=edinica;
            } else {
                chislo+=zero;
                pos=text.find(' ',pos)+1;
            }
        }
        hidden.write(reinterpret_cast<char*>(&chislo),sizeof(unsigned char));
        chislo<<=8;
    }
    hidden.close();
}
void::StegProb::CheckFile(const string& path){
    ifstream file;
    file.exceptions(ifstream::badbit|ifstream::failbit);
    file.open(path);
    file.close();
}
void::StegProb::CheckKey(){
    if (((mode!=1)and(mode!=2))or(cin.fail())or(cin.get() != '\n')) {
        throw invalid_argument ("Неправильно введён ключ");
    }
}
void::StegProb::getHelp(){
    cout<<"Данная программа предназначена для стеганографии методом двойных пробелов. Два пробела - 1, один пробел - 0(в инверсированном режиме наоборот)"<<endl;
    cout<<"Таким образом, получаемое сообщение, которое необходимо скрыть, преобразовывается в двоичный код и записывается в файле-контейнере."<<endl;
    cout<<"При получении информации из файла-контейнера, считываются все пробелы, и в зависимости от режима работы записывается сообщение скрытой в файле-контейнер"<<endl;
}