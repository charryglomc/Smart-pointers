#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::shared_ptr;

class Point
: public std::enable_shared_from_this<Point>
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

    /* Point *add(Point *pt) */
    shared_ptr<Point> add(Point *pt)
    {
        _ix += pt->_ix;
        _iy += pt->_iy;

        //Point * const this
        /* return this; */
        /* return shared_ptr<Point>(this); */
        return shared_from_this();
    }
    /* shared_ptr<Point> sp3(sp1->add(sp2.get())); */

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
    //不同的智能指针去托管同一个裸指针
    Point *pt = new Point(1, 2);
    unique_ptr<Point> up1(pt);
    unique_ptr<Point> up2(pt);
}

void test2()
{
    //使用不同的智能指针去托管同一个裸指针（同一块堆空间）
    unique_ptr<Point> up1(new Point(1, 2));
    unique_ptr<Point> up2(new Point(3, 4));

    up1.reset(up2.get());
}

void test3()
{
    //不同的智能指针去托管同一个裸指针
    Point *pt = new Point(1, 2);
    shared_ptr<Point> sp1(pt);
    shared_ptr<Point> sp2(pt);
    /* shared_ptr<Point> sp2(sp1); */
}

void test4()
{
    shared_ptr<Point> sp1(new Point(1, 2));
    cout << "sp1 = ";
    sp1->print() ;

    cout << endl;
    shared_ptr<Point> sp2(new Point(3, 4));
    cout << "sp2 = ";
    sp2->print() ;

    cout << endl;
    shared_ptr<Point> sp3(sp1->add(sp2.get()));
    cout << "sp3 = ";
    sp3->print() ;
}
int main(int argc, char **argv)
{
    test4();
    return 0;
}

