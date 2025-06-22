#include <iostream> 

using std::endl;
using std::cout;

class Base {
public:
    Base()
    {   
		a=5;
        cout<<"Base a="<<a<<endl;
    }  
protected:
    int a;
};

class  Base1
:virtual public Base
{
public:
    Base1()
    {	
		a = a + 10; 
	    cout<<"Base1 a = " << a <<endl;
	} 
};


class Base2
: virtual public Base
{
public:
    Base2()
    {
	   a = a + 20; 
	   cout << "Base2 a = " << a << endl;
    } 
};

class Derived
:public Base1
,public Base2
{
public:
    Derived()
    { 
	   cout<<"Derived a="<<a<<endl;
    } 
};

int main(void)
{ 
   Derived  obj;
   return  0; 
}
