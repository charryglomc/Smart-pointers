#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class RAII
{
public:
    //在对象构建的时候初始化资源
    RAII(T *data)
    : _data(data)
    {
        cout << "RAII(T *)" << endl;
    }
    //提供若干访问资源的方法
    
    T *operator->()
    {
        return _data;
    }

    T &operator*()
    {
        return *_data;
    }

    T *get()
    {
        return _data;
    }

    void reset(T *data)
    {
        if(_data)
        {
            delete _data;
            _data = nullptr;
        }
        _data = data;
    }


    //不允许复制与赋值
    RAII(const RAII &rhs) = delete;
    RAII &operator=(const RAII &rhs) = delete;

    //在对象销毁的时候释放资源
    ~RAII()
    {
        cout << "~RAII()" << endl;
        if(_data)
        {
            delete _data;
            _data = nullptr;
        }
    }
private:
    T *_data;
};

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
    RAII<int> raii(new int(10));

    RAII<Point> pt(new Point(10, 20));
    pt->print();

    /* RAII<Point> pt2 = pt;//error */

    RAII<Point> pt3(new Point(1, 3));
    /* pt3 = pt;//error */
    return 0;
}

