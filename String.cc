#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class String
{
public:
    String()
    : _pstr(nullptr)
    {
        cout << "String()" << endl;
    }

    String(const char *pstr)
    : _pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
    }

    //拷贝构造函数与赋值运算符函数称为具有复制控制语义的函数
    //移动赋值运算符函数与移动构造函数称为具有移动语义的函数
    //拷贝构造函数
    String(const String &rhs)
    : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(_pstr, rhs._pstr);
    }

    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        if(this != &rhs)
        {
            delete [] _pstr;
            _pstr = nullptr;

            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }

        return *this;
    }
    //移动构造函数与移动赋值运算符函数优先于拷贝构造函数与赋值
    //运算符函数的执行
    //
    //移动构造函数与移动赋值运算符函数编译器不会自动生成，必须
    //手写

    //String s3 = String("world");
    //String s3 = s1;
    //移动构造函数
    String(String &&rhs)
    : _pstr(rhs._pstr)
    {
        cout << "String(String &&)" << endl;
        rhs._pstr = nullptr;
    }
    
    //s4 = String("wuhan")
    //移动赋值运算符函数
    //Sting("world") = String("world")
    //s4 = std::move(s4)
    //s5 = std::move(s4)
    String &operator=(String &&rhs)
    {
        cout << "String &operator=(String &&)" << endl;
        if(this != &rhs) //1、自移动
        {
            delete [] _pstr; //2、释放左操作数
            _pstr = nullptr;

            _pstr = rhs._pstr;//3、浅拷贝
            rhs._pstr = nullptr;
        }

        return *this;//4、返回*this
    }

    ~String()
    {
        cout << "~String()" << endl;
        if(_pstr)
        {
            delete [] _pstr;
            _pstr = nullptr;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
private:
    char *_pstr;
};

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    if(rhs._pstr)
    {
        os << rhs._pstr;
    }

    return os;
}

void test()
{
    String s1("hello");
    cout << "s1 = " << s1 << endl;

    cout << endl;
    String s2 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;

    cout << endl;
    String s3 = "world";//String("world")
    cout << "s3 = " << s3 << endl;

    cout << endl;
    String s4("world");
    cout << "s4 = " << s4 << endl;

    s4 = "wuhan";//String("wuhan")
    cout << "s4 = " << s4 << endl;

    cout << endl << endl;
    String("world") = String("world");

    cout << endl;
    s4 = std::move(s4);//作用：就是将一个左值转换为一个右值
                       //std::move底层只是做了一个强转
                       //static_cast<T &&>(lvaue)
    cout << "s4 = " << s4 << endl;

     cout << endl << endl;
     String s5 = std::move(s1);//表名s1以后就不想使用
     cout <<"s5 = " << s5 << endl;
     cout <<"s1 = " << s1 << endl;


     cout << endl;
     s1 = "hellowuhan";
     cout <<"s1 = " << s1 << endl;

}

int main(int argc, char **argv)
{
    test();
    return 0;
}
