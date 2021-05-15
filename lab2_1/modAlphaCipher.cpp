#include "modAlphaCipher.h"

modAlphaCipher::modAlphaCipher(wstring& skey)
{
    skey=getValidKey(skey);
    for (long unsigned int i=0; i<skey.size(); i++) {
        if (numAlpha.find(skey[i])==string::npos) {
            wstring n;
            n=numAlpha;
            numAlpha=numAlpha2;
            numAlpha2=n;
            break;
        }
    }
    for (unsigned i=0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    key = convert(skey);
}

wstring modAlphaCipher::encrypt(const wstring& open_text)
{
    vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
wstring modAlphaCipher::decrypt(const wstring& cipher_text)
{
    vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
inline vector<int> modAlphaCipher::convert(const wstring& s)
{
    vector<int> result;
    for(auto c:s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}
inline wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}
bool modAlphaCipher::language(const wstring & skey)
{
    int sr=0;
    for (long unsigned int i=0; i<skey.size(); i++) {
        if (numAlpha.find(skey[i])==string::npos) {
            numAlpha=numAlpha2;
            sr=1;
            break;
        }
    }
    if (sr==1) {
        for (long unsigned int i=0; i<skey.size(); i++) {
            if (numAlpha.find(skey[i])==string::npos) {
                throw cipher_error(string("Letters from the English and Russian alphabets are entered"));
                return false;
            }
        }
    }
    return true;
}
inline wstring modAlphaCipher::getValidKey(const wstring & s)
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    if (s.size()==0)
        throw cipher_error("Empty key");
    wstring tmp(s);
    for (long unsigned int i=0; i<tmp.size(); i++) {
        if (!iswalpha(tmp[i]))
            throw cipher_error(string("Invalid key "));
        if (iswlower(tmp[i]))
            tmp[i] = towupper(tmp[i]);
    }
    return tmp;
}
inline wstring modAlphaCipher::getValidOpenText(const wstring & s)
{
    wstring tmp;
    for (auto c:s) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        }
    }
    for (long unsigned int i=0; i<tmp.size(); i++) {
        if (numAlpha.find(tmp[i])==string::npos) {
            throw cipher_error(string("Invalid open text"));
            }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}
inline wstring modAlphaCipher::getValidCipherText(const wstring & s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (auto c:s) {
        if (!iswupper(c))
            throw cipher_error(string("Invalid cipher text "));
    }
    for (long unsigned int i=0; i<s.size(); i++) {
            if (numAlpha.find(s[i])==string::npos) {
                throw cipher_error(string("Invalid cipher text"));
            }
    }
    return s;
}
