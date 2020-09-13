#pragma once
#include "StackArray.h"
#include "StringClass.h"
class StringTokenizer
{
protected:
	StackArray<String> s;
public:
	StringTokenizer(String& s);
	bool hasMoreTokens();
	String nextToken();
};

