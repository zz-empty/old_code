#include <iostream>
#include <string>
#include <limits>

using std::cout;
using std::endl;
using std::cin;
using std::string;

void test_cin();
void test_cyleCin();
void print_streamStates();

int main()
{
    /* test_cin(); */
    test_cyleCin();
    return 0;
}

void test_cyleCin()
{
    int number = 10;
    while (cin >> number, !cin.eof()) {
        if (cin.bad()) {
            std::cerr << "The istream is bad!" << endl;
            return;
        }
        else if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "input_type error, please data of int type!" << endl;
        }
        else {
            cout << "number = " << number << endl;
        } 
    }
}

void test_cin()
{
    print_streamStates();
    cout << endl;

    int number = 0;
    cin >> number;
    cout << "number = " << number << endl;

    cout << endl;
    print_streamStates();

    cout << endl;
    cout << "excute cin.clear()" << endl;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << endl;
    print_streamStates();
    
    cout << endl;
    string s1;
    cin >> s1;
    cout << "s1 = " << s1 << endl;
}

void print_streamStates()
{
    cout << "cin.bad = " << cin.bad() << endl;
    cout << "cin.fail = " << cin.fail() << endl;
    cout << "cin.eof = " << cin.eof() << endl;
    cout << "cin.good = " << cin.good() << endl;
}
