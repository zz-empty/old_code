#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::vector;

void test_fileIO1();
void test_fileIO2();
void test_fileIO3();
void test_ifstream_vector();
void test_ofstream_vector();
void test_fstream();

int main()
{
    /* test_fileIO1(); */
    /* test_fileIO2(); */
    /* test_fileIO3(); */
    /* test_ifstream_vector(); */
    test_fstream();
    return 0;
}

void test_fileIO1()
{
    ifstream ifs("buffer.cc");
    if (!ifs.good()) {
        cerr << "ifstream is not good!" << endl;
        return;
    }

    string word;
    while (ifs >> word) {
        cout << word;
    }

    ifs.close();
}

void test_fileIO2()
{
    ifstream ifs("buffer.cc");
    if (!ifs.good()) {
        cerr << "ifstream is not good!" << endl;
        return;
    }

    string line;
    while (getline(ifs, line)) {
        cout << line << endl;
    }

    ifs.close();
}

void test_fileIO3()
{
    ifstream ifs("buffer.cc");
    if (!ifs.good()) {
        cerr << "ifstream is not good!" << endl;
        return;
    }

    string line[100];
    size_t idx = 0;
    while (getline(ifs, line[idx])) {
        cout << line[idx] << endl;
        ++idx;
    }

    cout << endl;
    cout << "output 10 line: " << line[10] << endl;

    ifs.close();
}


void test_ifstream_vector()
{
    ifstream ifs("buffer.cc");
    if (!ifs.good()) {
        cerr << "ifstream is not good!" << endl;
        return;
    }

    //store data in container
    vector<string> vec;
    string line;
    while (getline(ifs, line)) {
        vec.push_back(line);
    }

    //iterate the vec
    size_t idx = 0;
    for (idx = 0; idx < vec.size(); ++idx) {
        cout << vec[idx] << endl;
    }

    cout << endl;
    cout << "output 10 line: " << vec[10]<< endl;

    ifs.close();
}

void test_ofstream_vector()
{
    ifstream ifs("buffer.cc");
    if (!ifs.good()) {
        cerr << "ifstream is not good!" << endl;
        return;
    }

    ofstream ofs("copy.txt");
    if (!ofs.good()) {
        cerr << "ofstream is not good!" << endl;
        ifs.close();
        return;
    }

    //read data into container
    vector<string> vec;
    string line;
    while (getline(ifs, line)) {
        vec.push_back(line);
    }

    

    ifs.close();
    ofs.close();
}

void test_fstream()
{
    fstream fs("text.txt");
    if (!fs.good()) {
        cerr << "The stream is not good!" << endl;        
        return;
    }

    int number = 0;
    int idx = 0;
    for (idx = 0; idx < 5; ++idx) {
        cin >> number;
        fs << number << " ";
    }

    fs.seekp(0, std::ios::beg);
    for (idx = 0; idx < 5; ++idx) {
        fs >> number;
        cout << number << " ";
    }

    fs.close();
}
