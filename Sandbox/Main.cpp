#include<iostream>
template<typename DT>
class Object
{
private:
	static int count;
	DT* info
public:
	Object(const DT& val)
	{

	}

};

int value()
{
	return 10;
}

int& svalue()
{
	static int value = 10;
	return value;
}

void setValue(int i)
{

}

int main()
{
	// To demonstrate the differences between lvalues, rvalues, lvalue references, and rvalue references
	int i = 10; // on the left is a variable 'i' cooresponding to a (l)ocation in memory. 'i' is an lvalue
				// on the right is a value which C++ gives no permenant place in memory. 10 is an rvalue
	
	int a = value();	//  on the right is a temporary value which is created by the function. the expression on the right is an rvalue
	svalue() = a;		// the expression on the left returns a permenant value in memory, meaning it is an lvalue
	
	setValue(a);	// valid since the signiture (int i) can accept an lvalue or rvalue
	setValue(svalue());
}