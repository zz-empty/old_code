#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void test()
{
    double x, y;
    cin >> x >> y;

    try
    {
        if (0 == y) {
            throw y;
        }
        else {
            cout << "x / y = " << x / y << endl;
        }
    }
    catch (int e) {
        cout << "catch(int)" << endl;
    }
    catch (double d) {
        cout << "catch(double)" << endl;
    }

}

int main()
{
    test();
    return 0;
}

