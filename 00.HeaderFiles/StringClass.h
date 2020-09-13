#pragma once
#ifndef __STRING__H
#define __STRING__H

#define _CRT_SECURE_NO_WARNINGS
#include "ArrayClass.h"
#include "StackLinked.h"
#include <istream>

class StringSizeException : public ArrayException {};

class StringClass : virtual public ArrayClass<char> {
    friend std::ostream& operator<< (std::ostream& s, const StringClass& str)
    {
        s << str.paObject;
        return s;
    };
    friend std::istream& operator>>(std::istream& s, StringClass& str)
    {
        StackLinked<char> inputStack;
        char c; int size = 1;

        s >> c;
        while (c != '\n')
        {
            inputStack.push(c);
            size++;
            s.get(c);
        }

        inputStack.push('\0');

        char* characters = new char[size];
        do
        {
            characters[--size] = inputStack.pop();
        } while (size > 0);

        str = characters;

        delete[] characters;
        return s;
    }
public:
    StringClass();
    StringClass(size_t n);
    StringClass(const char* s);
    StringClass(const StringClass& str);
    virtual ~StringClass();
    void operator= (const StringClass& str);
    virtual size_t length() const;
    virtual size_t size() const;
    bool operator==(const StringClass& str) const;
    bool operator<(const StringClass& str) const;
    void concatenate(const StringClass& str);
    size_t index(char c, size_t start) const;
    size_t index(char c) const;
    size_t lastIndex(char c, size_t start) const;
    size_t lastIndex(char c) const;
    StringClass substring(int left, size_t len) const;
    StringClass operator+(const StringClass& str);
    StringClass& operator+=(const StringClass& str);
    bool equalsIgnoreCase(const StringClass& str);
    char& operator[] (size_t k) const;
};
StringClass::StringClass() : ArrayClass<char>(1, '\0') {}
StringClass::StringClass(size_t n) : ArrayClass<char>(n + 1, '\0') {}
StringClass::StringClass(const char* s) : ArrayClass<char>(strlen(s) + 1)
{
    size_t len = _size - 1;
    for (size_t i = 0; i < len; i++)
    {
        paObject[i] = s[i];
    }
    paObject[len] = '\0';
}
StringClass::StringClass(const StringClass& str) : ArrayClass<char>(str) {};

StringClass::~StringClass() {};
size_t StringClass::index(char c, size_t start) const
{
    if (start >= length()) return -1;
    char* pc = strchr(paObject + start, c);
    if (pc == NULL) return -1;
    return (pc - paObject);
}
size_t StringClass::lastIndex(char c, size_t start) const
{
    size_t last;
    while (start = index(c, start) != -1) last = start;
    return last;
}
size_t StringClass::lastIndex(char c) const
{
    return lastIndex(c, 0);
}
size_t StringClass::index(char c) const
{
    return index(c, 0);
}
StringClass StringClass::substring(int left, size_t len) const
{
    if (left < 0) throw ArrayBoundsException();
    StringClass sub(len);
    if (left > length()) return sub;
    size_t max = len;
    if (max + len > length()) max = length() - left;
    strcpy_s(sub.paObject, max, &paObject[left]);
    sub.paObject[max] = '\0';
    return sub;
}
StringClass StringClass::operator+(const StringClass& str)
{
    StringClass temp(length() + str.length());
    temp = (*this);
    temp.concatenate(str);
    return temp;
}
size_t StringClass::length() const
{
    return strlen(paObject);    // length of current string may be less than capacity
}
size_t StringClass::size() const
{
    return ArrayClass::size() - 1;
}
bool StringClass::equalsIgnoreCase(const StringClass& str)
{
    return (_stricmp(paObject, str.paObject) == 0);
}
void StringClass::concatenate(const StringClass& str)
{
    size_t len = length();
    size_t max = str.length();
    bool overflow = false;
    if (size() < max + len)
    {
        overflow = true;
        max = size() - len;
    }
    for (size_t i = 0; i < max; i++)
    {
        paObject[i + len] = str.paObject[i];
    }
    paObject[max + len] = '\0'; // NULL terminate
    if (overflow) throw StringSizeException();
};
StringClass& StringClass::operator+=(const StringClass& str)
{
    concatenate(str);
    return *this;
}
bool StringClass::operator==(const StringClass& str) const
{
    return (strcmp(str.paObject, paObject) == 0);
}
bool StringClass::operator< (const StringClass& str) const
{
    return (strcmp(paObject, str.paObject) < 0);
}
void StringClass::operator= (const StringClass& str)
{
    if (size() == 0)
    {
        ArrayClass<char>::operator= (str);
        return;
    }
    size_t max = str.length();
    bool overflow = false;
    if (_size - 1 < max)
    {
        overflow = true;
        max = _size - 1;
    }
    for (size_t i = 0; i < max; i++)
    {
        paObject[i] = str.paObject[i];
    }
    paObject[max] = '\0';
    if (overflow) throw StringSizeException();
}
char& StringClass::operator[] (size_t k) const
{
    if ((k < 0) || (k > strlen(paObject))) throw ArrayBoundsException();
    return paObject[k];
}
#endif // !__STRING__H