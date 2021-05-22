#include <UnitTest++/UnitTest++.h>
#include "Tabl_Marsh.h"
#include "Tabl_Marsh.cpp"
SUITE(KeyTest)
{
    TEST (WorkKey) {
        setlocale (LC_ALL,"ru_RU.UTF-8");
        int key=3;
        wstring res=L"абв";
        wstring text=L"вба";
        Tabl_Marsh st(key);
        CHECK_EQUAL (true,res==st.encrypt(text));
    }
    TEST (NegativeKey) {
        int key=-3;
        Tabl_Marsh st(key);
        CHECK_THROW (st.Check(key),invalid_argument);
    }
    TEST (NullKey) {
        int key = 0;
        Tabl_Marsh st(key);
        CHECK_THROW (st.Check(key),invalid_argument);
    }
};
struct TESTKEY {
    int key = 3;
    Tabl_Marsh *z;
    TESTKEY ()
    {
        z = new Tabl_Marsh (key);
    }
    ~TESTKEY ()
    {
        delete z;
    }
};
SUITE (EncryptTest)
{
    TEST_FIXTURE (TESTKEY,EmptyText) {
        wstring text = L"";
        CHECK_THROW (z->encrypt(text),invalid_argument);
    }
    TEST_FIXTURE (TESTKEY,TrueText) {
        wstring text = L"ASDasd";
        wstring res =L"DdSsAa";
        CHECK_EQUAL(true, res==z->encrypt(text));
    }
     TEST_FIXTURE (TESTKEY,TrueRusText) {
        wstring res = L"ВвЫыФф";
        wstring text =L"ФЫВфыв";
        CHECK_EQUAL(true, res==z->encrypt(text));
    }
}
SUITE (DecryptTest)
{
    TEST_FIXTURE (TESTKEY,EmptyText) {
        wstring text = L"";
        CHECK_THROW (z->decrypt(text),invalid_argument);
    }
    TEST_FIXTURE (TESTKEY,TrueText) {
        wstring res = L"ASDasd";
        wstring text =L"DdSsAa";
        CHECK_EQUAL(true, res==z->decrypt(text));
    }
    TEST_FIXTURE (TESTKEY,TrueRusText) {
        wstring text = L"ВвЫыФф";
        wstring res =L"ФЫВфыв";
        CHECK_EQUAL(true, res==z->decrypt(text));
    }
}
int main()
{
    return UnitTest::RunAllTests();
}
