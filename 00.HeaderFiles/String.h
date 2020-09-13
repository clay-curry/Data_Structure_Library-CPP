/*
String Abstract Data Type primitive operations:
 createString(n):	            creates a new string of size n
 getChar(index):                gets the character stored at the position 'index'
 putChar(newChar, index):       replaces the character stored at the position 'index' with the 'newChar'
 insertChar(newChar, index):    insert 'newChar' after the character at the position 'index' in the string
 deleteChar(index):             delete the character at position 'index' and reconstructs a new string without the character
 concatenate(s):                attach a copy of 's' to the end of the string
 length():                      gets the length of the string
 equals(s):                     returns true if the string is exactly equal to 's', otherwise false
 compareTo(s):                  returns an indicator for whether the string is less than, equal to, or greater than 's'
 substring(left, length):       returns a substring of length 'length', starting at position 'length'
 index (c, start):              returns the index of the first position of character 'c' at or after index 'start' in the string, or else -1
 lastIndex(c, end):             returns the index of the last  position of character 'c' at or after index 'start' in the string, or else -1

using built-in C++ helper methods:
 char* strcpy(char* dest, const char* src):                 copies all characters from 'src' to 'dest' until reaching the NULL
 char* strncpy(char* dest, const char* src, size_t num):    copies all characters from 'src' to 'dest' until reaching NULL or 'num'
 int strcmp(const char* s1, const char* s2):                compares two strings, halting when it reaches null of either string.
 int stricmp (const char* s1, const char* s2):              compares two strings (case-insensitive), halting when it reaches null of either string.
 int strncmp (const char* s1, const char* s2, size_t num):  compares two strings, halting at 'num'
 int strlen (const char* s):                                returns the number of characters before null
 char* strcat (char* dest, const char* src, size_t num):    appends 'src' to the end of 'dest'. 'dest' must be large enough
 char* strchr(const char* str, char c):                     returns a pointer to the first occurance of 'c' in the string                   
 char* strrchr(const char* str, char c):                    returns a pointer to the last occurrence of c in str
*/

#ifndef __STRING__H
#define __STRING__H

#define _CRT_SECURE_NO_WARNINGS
#include "ArrayClass.h"

class StringSizeException : public ArrayException {};

class String : virtual public ArrayClass<char> {
public:
    String();
    String(size_t n);
    String(const char* s);
    String(const String& str);
    ~String();
    size_t length() const;
    size_t size() const;
    void concatenate(const String& str);
    void operator= (const String& str);
    bool operator==(const String& str) const;
    bool operator<(const String& str) const;
    bool equalsIgnoreCase(const String& str);
};
String::String() : ArrayClass<char>(1, '\0') {}
String::String(size_t n) : ArrayClass<char>(n + 1, '\0') {}
String::String(const char* s) : ArrayClass<char>(strlen(s) + 1) 
{
    strcpy_s(paObject, size(), s);
}
String::String(const String& str) : ArrayClass<char>(str) {};
String::~String() {};
size_t String::length() const
{
    return strlen(paObject);
}
size_t String::size() const
{
    return ArrayClass::size() - 1;
}
bool String::equalsIgnoreCase(const String& str)
{
    return (_stricmp(paObject, str.paObject) == 0);
}
void String::concatenate(const String& str)
{
    size_t len = length();
    size_t max = str.length();
    bool overflow = false;
    if (size() < max + len)
    {
        overflow = true;
        max = size() - len;
    }
};
bool String::operator==(const String& str) const
{
    return (strcmp(str.paObject, paObject) == 0);
}
bool String::operator< (const String& str) const
{
    return (strcmp(str.paObject, paObject) < 0);
}
void String::operator= (const String& str)
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
    strncpy(paObject, str.paObject, max);
    paObject[max] = '\0';
    if (overflow) throw StringSizeException();
}
#endif // !__STRING__H