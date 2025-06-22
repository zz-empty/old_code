#include <iostream>
#include <string>

using namespace std;

void print_diamond(int n)
{
    for (int i = 1; i <= n; i++) {
        cout << string(n - i, ' ');
        string stars;
        for (int j = 0; j < i; j++) {
            stars += '*';
            if (j != i - 1) stars += ' ';
        }
        cout << stars << endl;
    }
    for (int i = n - 1; i > 0; i--) {
        cout << string(n - i, ' ');
        string stars;
        for (int j = 0; j < i; j++) {
            stars += '*';
            if (j != i - 1) stars += ' ';
        }
        cout << stars << endl;
    }
}

int main()
{
    int n = 5;
    print_diamond(n);
    return 0;
}
