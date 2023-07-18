#include <iostream>

using std::cout;
using std::endl;

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point(int = 0, int = 0)" << endl;
    }

    void print()
    {
        cout << "_ix = " << _ix << endl
             << "_iy = " << _iy << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }

private:
    int _ix;
    int _iy;
};

int main(int argc, char **argv)
{
    return 0;
}
