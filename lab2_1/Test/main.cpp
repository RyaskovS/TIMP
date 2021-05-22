#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include "modAlphaCipher.cpp"
SUITE(KeyTest)
{
    TEST(ValidKey) {
        setlocale (LC_ALL,"ru_RU.UTF-8");
        wstring key=L"BCD";
        wstring res=L"BCDBC";
        wstring text=L"AAAAA";
        CHECK_EQUAL(true, res==modAlphaCipher(key).encrypt(text));
    }
    TEST(RusAlph) {
        wstring key=L"АБВ";
        wstring res=L"ФЬДА";
        wstring text=L"ФЫВА";
        CHECK_EQUAL(true, res==modAlphaCipher(key).encrypt(text));
    }
     TEST(RusLowAlph) {
        wstring key=L"абв";
        wstring res=L"ФЬДА";
        wstring text=L"ФЫВА";
        CHECK_EQUAL(true, res==modAlphaCipher(key).encrypt(text));
    }
    TEST(RusLowAndHighAlph) {
        wstring key=L"аБв";
        wstring res=L"ФЬДА";
        wstring text=L"ФЫВА";
        CHECK_EQUAL(true, res==modAlphaCipher(key).encrypt(text));
    }
    TEST(LongKey) {
        wstring key=L"BCDEFGHIJK";
        wstring res=L"BCDEF";
        wstring text=L"AAAAA";
        CHECK_EQUAL(true, res==modAlphaCipher(key).encrypt(text));
    }
    TEST(LowCaseKey) {
        wstring key=L"bcd";
        wstring res=L"BCDBC";
        wstring text=L"AAAAA";
        CHECK_EQUAL(true, res==modAlphaCipher(key).encrypt(text));
    }
    TEST(RusAndEngAlph) {
        wstring text=L"РусскийИEng";
        CHECK_THROW(modAlphaCipher(text).language(text),cipher_error);
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp(L"B1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp(L"B,C"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp(L"B C"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(L""),cipher_error);
    }
}
struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher(L"B");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};
struct KeyA_fixture {
    modAlphaCipher * p;
    KeyA_fixture()
    {
        p = new modAlphaCipher(L"АБВ");
    }
    ~KeyA_fixture()
    {
        delete p;
    }
};
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyA_fixture,UpRus) {
        wstring text = L"ФЫВА";
        wstring res = L"ФЬДА";
        CHECK_EQUAL (true, res == p->encrypt(text));
    }
    TEST_FIXTURE(KeyA_fixture,LowRus) {
        wstring text = L"фыва";
        wstring res = L"ФЬДА"; 
        CHECK_EQUAL (true, res == p->encrypt(text));
    }
    TEST_FIXTURE (KeyA_fixture,MixedRus) {
        wstring text = L"фЫвА";
        wstring res = L"ФЬДА";
        CHECK_EQUAL (true, res == p->encrypt(text));
    }
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        wstring res=L"UIFRVJDLCSPXOGPYKVNQTPWFSUIFMBAZEPH";
        wstring text=L"THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG";
        CHECK_EQUAL(true, res==p->encrypt(text));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        wstring res=L"UIFRVJDLCSPXOGPYKVNQTPWFSUIFMBAZEPH";
        wstring text=L"thequickbrownfoxjumpsoverthelazydog";
        CHECK_EQUAL(true, res==p->encrypt(text));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        wstring res=L"UIFRVJDLCSPXOGPYKVNQTPWFSUIFMBAZEPH";
        wstring text=L"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG!!!";
        CHECK_EQUAL(true, res==p->encrypt(text));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        wstring res=L"IBQQZOFXZFBS";
        wstring text=L"Happy New 2019 Year";
        CHECK_EQUAL(true, res==p->encrypt(text));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        wstring text=L"";
        CHECK_THROW(p->encrypt(text),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        wstring text=L"1234+8765=9999";
        CHECK_THROW(p->encrypt(text),cipher_error);
    }
    TEST(MaxShiftKey) {
        wstring res=L"SGDPTHBJAQNVMENWITLORNUDQSGDKZYXCNF";
        wstring text=L"THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG";
        wstring key=L"Z";
        CHECK_EQUAL(true, res==modAlphaCipher(key).encrypt(text));
    }
}
SUITE(DecryptText)
{
    TEST_FIXTURE(KeyA_fixture,UpRus) {
        wstring res= L"ФЫВА";
        wstring text = L"ФЬДА";
        CHECK_EQUAL (true, res == p->decrypt(text));
    }
    TEST_FIXTURE(KeyA_fixture,LowRus) {
        wstring text = L"фьда"; 
         CHECK_THROW(p->decrypt(text),cipher_error);
    }
    TEST_FIXTURE (KeyA_fixture,MixedRus) {
        wstring text = L"фЬдА";
         CHECK_THROW(p->decrypt(text),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        wstring res=L"THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG";
        wstring text=L"UIFRVJDLCSPXOGPYKVNQTPWFSUIFMBAZEPH";
        CHECK_EQUAL(true, res==p->decrypt(text));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        wstring text=L"uifRVJDLCSPXOGPYKVNQTPWFSUIFMBAZEPH";
        CHECK_THROW(p->decrypt(text),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        wstring text=L"UIF RVJDL CSPXO GPY KVNQT PWFS UIF MBAZ EPH";
        CHECK_THROW(p->decrypt(text),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        wstring text=L"IBQQZOFX2019ZFBS";
        CHECK_THROW(p->decrypt(text),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        wstring text=L"IFMMP,XPSME";
        CHECK_THROW(p->decrypt(text),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        wstring text=L"";
        CHECK_THROW(p->decrypt(text),cipher_error);
    }
    TEST(MaxShiftKey) {
        wstring res=L"THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG";
        wstring text=L"SGDPTHBJAQNVMENWITLORNUDQSGDKZYXCNF";
        wstring key=L"Z";
        CHECK_EQUAL(true, res==modAlphaCipher(key).decrypt(text));
    }
}

int main()
{
    return UnitTest::RunAllTests();
}
