#include <UnitTest++/UnitTest++.h>
#include "StegProb.h"
#include "StegProb.cpp"
SUITE(KeyTest)
{
    TEST (WorkKey_1) {
        int key=1;
        StegProb st(key);
        CHECK(true);
    }
    TEST (WorkKey_2) {
        int key=2;
        StegProb st(key);
        CHECK(true);
    }
    TEST (NegativeKey) {
        int key=-3;
        StegProb st(key);
        CHECK_THROW (st.CheckKey(),invalid_argument);
    }
    TEST (NullKey) {
        int key=0;
        StegProb st(key);
        CHECK_THROW (st.CheckKey(),invalid_argument);
    }
};
struct TESTKEY {
    int key = 1;
    StegProb *z;
    TESTKEY ()
    {
        z = new StegProb(key);
    }
    ~TESTKEY ()
    {
        delete z;
    }
};
struct TESTKEY_2 {
    int key = 2;
    StegProb *z;
    TESTKEY_2 ()
    {
        z = new StegProb (key);
    }
    ~TESTKEY_2 ()
    {
        delete z;
    }
};
SUITE (CheckFile)
{
    TEST_FIXTURE (TESTKEY,EmptyText) {
        string text = "";
        CHECK_THROW (z->CheckFile(text),ifstream::failure);
    }
    TEST_FIXTURE(TESTKEY,TrueText) {
        string path = "Что прячем.txt";
        z->CheckFile(path);
        CHECK(true);
    }
    TEST_FIXTURE (TESTKEY,WrongText) {
        string text = "NotExistingFile.txt";
        CHECK_THROW (z->CheckFile(text),ifstream::failure);
    }
}
SUITE (HideAndGetInfoTest)
{
    TEST_FIXTURE (TESTKEY,BadCont) {
        string hide = "Что прячем.txt";
        string cont = "Плохой контейнер.txt";
        CHECK_THROW (z->hideInfo(hide,cont),invalid_argument);
    }
    TEST_FIXTURE (TESTKEY,BadContWithSpaces) {
        string hide = "Что прячем.txt";
        string cont = "Двойные пробелы.txt";
        CHECK_THROW (z->hideInfo(hide,cont),invalid_argument);
    }
    TEST_FIXTURE (TESTKEY,NormalHide_1) {
        fstream stroka;
        fstream Result;
        string text;
        string resultat;
        string hide = "Что прячем.txt";
        string cont = "Контейнер.txt";
        string newcont= cont+"_copy";
        z->hideInfo(hide,cont);
        z->getInfo(newcont,"Result.txt");
        stroka.open(hide,ios_base::in);
        getline(stroka,text,'\0');
        stroka.close();
        Result.open("Result.txt",ios_base::in);
        getline(Result,resultat,'\0');
        Result.close();
        CHECK_EQUAL(text,resultat+"\n");
    }
    TEST_FIXTURE (TESTKEY_2,NormalHide_2) {
        fstream stroka;
        fstream Result;
        string text;
        string resultat;
        string hide = "Что прячем.txt";
        string cont = "Контейнер.txt";
        string newcont= cont+"_copy";
        z->hideInfo(hide,cont);
        z->getInfo(newcont,"Result.txt");
        stroka.open(hide,ios_base::in);
        getline(stroka,text,'\0');
        stroka.close();
        Result.open("Result.txt",ios_base::in);
        getline(Result,resultat,'\0');
        Result.close();
        CHECK_EQUAL(text,resultat+"\n");
    }
    TEST_FIXTURE (TESTKEY,EmrtyHideFile) {
        string hide= "Пустой файл.txt";
        string cont= "Контейнер.txt";
        CHECK_THROW(z->hideInfo(hide,cont),invalid_argument);
    }
    TEST_FIXTURE (TESTKEY,EmrtyContFile) {
        string hide= "Что прячем.txt";
        string cont= "Пустой контейнер.txt";
        CHECK_THROW(z->hideInfo(hide,cont),invalid_argument);
    }
    TEST_FIXTURE (TESTKEY,EmrtyHiddenFile) {
        string cont= "Пустой контейнер.txt";
        string hidden="Результат.txt";
        CHECK_THROW(z->getInfo(cont,hidden),invalid_argument);
    }
}
int main()
{
    return UnitTest::RunAllTests();
}
