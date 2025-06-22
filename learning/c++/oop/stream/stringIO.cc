#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::ifstream;

string int_convert_string(int number);
void test_ostringstream();
void test_stringstream();
void read_conf();

int main()
{
    /* test_ostringstream(); */
    /* test_stringstream(); */
    read_conf();
    return 0;
}

string int_convert_string(int number)
{
    ostringstream oss;
    oss << number;
    return oss.str();
}

void test_ostringstream()
{
    int value = 100;
    string s1 = int_convert_string(value);

    cout << "s1 = " << s1 << endl;
}

void test_stringstream()
{
    int num1 = 100;
    int num2 = 200;
    stringstream ss;
    ss << "num1= " << num1 << " ,num2= " << num2 << endl;
    cout << ss.str();

    string key;
    int value;
    while (ss >> key >> value) {
        cout <<  key << " " << value << endl;
    }

}

void read_conf()
{
    ifstream ifs("my.conf");
    if (!ifs.good()) {
        std::cerr << "The stream is bad" << endl;
        return;
    }

    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string key;
        string value;
        iss >> key >> value;
        cout << key << "=========>" << value << endl;

        /* _dict._word = key; */
        /* _dict._fre = value; */
    }

    ifs.close();
}
