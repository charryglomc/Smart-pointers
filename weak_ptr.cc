#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

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

void test()
{
    weak_ptr<Point> wp;
    {
        shared_ptr<Point> sp(new Point(1, 2));
        wp = sp;
        cout << "wp.use_count() = " << wp.use_count() << endl;
        cout << "sp.use_count() = " << sp.use_count() << endl;
        cout << "*sp = ";
        sp->print();

        /* wp->print();//error */
        cout << "wp.expired() = " << wp.expired() << endl;
        shared_ptr<Point> sp2 = wp.lock();
        if(sp2)
        {
            cout << "提升成功" << endl;
            cout << "*sp2 = ";
            sp2->print();
        }
        else
        {
            cout << "提升失败，托管的资源已经销毁了" << endl;
        }
    }

    cout << endl << endl << endl;
    cout << "wp.expired() = " << wp.expired() << endl;
    shared_ptr<Point> sp2 = wp.lock();
    if(sp2)
    {
        cout << "提升成功" << endl;
        cout << "*sp2 = ";
        sp2->print();
    }
    else
    {
        cout << "提升失败，托管的资源已经销毁了" << endl;
    }
}
int main(int argc, char **argv)
{
    test();
    return 0;
}

