#include "Tabl_Marsh.h"
using namespace std;
Tabl_Marsh::Tabl_Marsh(int& skey )
{
    key=skey;
}
wstring Tabl_Marsh::encrypt(const wstring& open_text)
{
    if (open_text.size()==0) {
        throw invalid_argument("Empty text");
    }
    wstring shifr;
    int raws;
    int len=open_text.size();
    if (len%key==0) {
        raws=len/key;
    } else {
        raws=len/key+1;
    }
    wchar_t **Matrica= new wchar_t*[raws];
    for (int i =0; i<raws; i++) {
        Matrica[i]=new wchar_t[key];
    }
    int ch=0;
    for (int i=0; i<raws; i++) {
        for (int j=0; j<key; j++) {
            if (ch>len) {
                break;
            } else {
                Matrica[i][j]=open_text[ch];
                ch++;
            }
        }
    }
    for (int j=key-1; j>=0; j--) {
        for ( int i=0; i<raws; i++) {
            shifr.push_back(Matrica[i][j]);
        }
    }
    for (int i =0; i<raws; i++) {
        delete []Matrica[i];
    }
    delete []Matrica;
    return shifr;
}
wstring Tabl_Marsh::decrypt(const wstring& cipher_text)
{
    if (cipher_text.size()==0) {
    throw invalid_argument("Empty text");
    }
    wstring text=cipher_text;
    wstring norm_text;
    int raws,prob;
    int newl=0;
    int len=text.size();
    if (len%key==0) {
        raws=len/key;
    } else {
        raws=len/key+1;
        prob=key-len%key;
        for (int i=0; i<prob; i++) {
            text.insert(i*raws+raws-1,L" ");
            newl++;
        }
    }
    len+=newl;
    wchar_t **Matrica= new wchar_t*[raws];
    for (int i =0; i<raws; i++) {
        Matrica[i]=new wchar_t[key];
    }
    int sch=0;
    for (int j=key-1; j>=0; j--) {
        for ( int i=0; i<raws; i++) {
            Matrica[i][j]=text[sch];
            sch++;
        }
    }
    for (int i=0; i<raws; i++) {
        for ( int j=0; j<key; j++) {
            norm_text.push_back(Matrica[i][j]);
        }
    }
    for (int i=0; i<len; i++) {
        if (norm_text[i]==char(32)) {
            norm_text.erase(i,1);
        }
    }
    for (int i =0; i<raws; i++) {
        delete []Matrica[i];
    }
    delete []Matrica;
    return norm_text;
}
void Tabl_Marsh::Check(int skey){
    if(((wcin.fail())or(skey<=0))or(wcin.get() != '\n')) {
    throw invalid_argument("Must be a positive integer number");
    }
}

