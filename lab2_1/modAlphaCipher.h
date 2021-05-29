/**
* @file modAlphaCipher.h
* @author Рясков.С.С.
* @version 1.0
* @brief Описание класса modAlphaCipher
* @date 29.05.2021
* @copyright ИБСТ ПГУ
*/
#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <iostream>
#include <cstring>
using namespace std;
///@brief Класс зашифрования и расшифрования текста алгоритмом Гронсфельда.
class modAlphaCipher
{
private:
    ///@brief Алфавит для работы с английским текстом
    wstring numAlpha2 =L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ///@brief Алфавит для работы с русским текстом
    wstring numAlpha =L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; 
    ///@brief ассоциативный массив "номер по символу"
    map <char,int> alphaNum;
    ///@brief ключ
    vector <int> key;
    /**@brief Преобразование строка-вектор.
     * @param s - строка для преобразования в вектор.
     **/
    vector<int> convert(const wstring& s); 
     /**@brief Преобразование вектор-строка.
     * @param v - вектор для преобразования в строку.
     **/
    wstring convert(const vector<int>& v); 
    /**@brief Метод валидации ключа.
     * @param s - ключ-строка.
     * @details Метод проверяет правильность ввода ключа-строки и выбрасывает исключение если:
     * Введен пустой ключ, ключ содержит символы, не являющиеся символами русского или английского алфавита.
     * Все символы ключа переводятся в верхний регистр.
    **/
    inline wstring getValidKey(const wstring & s);
    /**@brief Метод валидации текста, который необходимо зашифровать.
    * @param s - текст-строка,введенный пользователем.
    * @details Метод проверяет корректность ввода текста-строки и выбрасывает исключение если:
    * Введен пустой текст, текст содержит символы, которых нет в используемом алфавите.
    * Все символы текста переводятся в верхний регистр.
    **/
    inline wstring getValidOpenText(const wstring & s);
    /**@brief Метод валидации текста, который необходимо расшифровать.
     * @param s - текст-строка,введенный пользователем.
     * @details Метод проверяет корректность ввода текста-строки и выбрасывает исключение если:
     * Введен пустой текст, текст содержит символы нижнего регистра или символы, которых нет в используемом алфавите.
     **/
    inline wstring getValidCipherText(const wstring & s);
public:
    ///@brief Запрет конструктора без параметров.
    modAlphaCipher()=delete; 
    /**@brief Конструктор для установки ключа.
     * @param skey - ключ, вводенный пользователем.
     * @details После проверки ключа с помощью метода "getValidKey" конвертирует строку-ключ в вектор.
    **/
    modAlphaCipher(wstring& skey); 
    /**@brief Метод зашифрования текста.
     * @param open_text - текст для зашифрования.
     * @return Зашифрованаая методом Гронсфельда строка.
     */
    wstring encrypt(const wstring& open_text); 
    /**@brief Метод расшифрования текста.
     * @param cipher_text - текст для расшифрования.
     * @return Расшифрованная строка.
     */
    wstring decrypt(const wstring& cipher_text);
    /**
     * @brief Метод проверки ключа на соответствие алфавиту.
     * @details Метод выбрасывает исключение, если в ключе находятся символы русского и английского алфавита одновременно.
     * @param skey - ключ-строка.
     * @return Значение true, если проверка прошла.
     */
    bool language(const wstring& skey);
};
///@brief Собственный класс исключений, наследуемый от класса "invalid_argument".
class cipher_error: public invalid_argument {
public:
    /** 
    * @brief Конструктор инициализации ошибки строкой.
    * @param what_arg - описание ошибки.
    **/
 explicit cipher_error (const string& what_arg):
invalid_argument(what_arg) {}
    /** 
    * @brief Конструктор инициализации ошибки Си-строкой.
    * @param what_arg - описание ошибки.
    **/
 explicit cipher_error (const char* what_arg):
 invalid_argument(what_arg) {}
 
};
