#include<iostream>
#include<vector>
#include<stack>
#include<math.h>
using namespace std;

vector<int> parseIntArray(string s)
{
    s = s.substr(1, s.size() - 2);      // trims off '[' ']'
    char* reverse = new char[s.size()]; // reverses user's input to parse each element by place value order
    size_t i = s.size();                // iterator starts at the end of the string
    int element = 0, digit = 0, placeValue = 0;
    stack<int> inputs;                // inputs are stacked in reverse order, and popped back in order
    while (i != 0)
    {
        while (i != 0 && (digit = ((int)s[--i])) > 47 && digit < 58)
        {
            element += (digit - 48) * (pow(10, placeValue));
            placeValue++;
        }
        inputs.push(element);
        placeValue = digit = element = 0;
    }
    vector<int> response(inputs.size());
    while (!inputs.empty())
    {
        response[element++] = inputs.top();
        inputs.pop();
    }

    return response;
}
ostream& operator<<(ostream& s, vector<int> v)
{
    s << "{";
    if (v.size() > 0) s << v[0];
    for (int i = 1; i < v.size(); i++)
        s << ", " << v[i];
    s << "}";
    return s;
}

int findNumbers(vector<int>&& nums)
{
    int digCt = 0, count = 0;
    for (int i : nums)
    {
        while (i = (i / 10) > 0)
        {
            digCt++;
        }
        if (digCt % 2 == 0) count++;
        digCt = 1;
    };
    return count;
}

int sumEvenDigits(const vector<int>& nums)
{
    int count = 0;
    int logb10;
    float logi, log10 = log(10);
    for (int i : nums) {
        logi = log(i);
        logb10 = logi / log10;
        if(logb10 % 2 == 1)
            count++;
    }

    return count;
}

// Find pair with given sum in the array
int main()
{
    string input;
    cin >> input;
    vector<int> parseArray = parseIntArray(input);
    cout << sumEvenDigits(parseArray);



}