#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

int main(int argc, char **argv)
{
    //裸指针
    int *pInt = new int(10);
    auto_ptr<int> ap(pInt);
    cout << "*ap = " << *ap << endl;
    cout << "pInt = " << pInt << endl;
    cout << "ap.get() = " << ap.get() << endl;

    cout << endl;
    auto_ptr<int> ap2(ap);//表面上去进行了拷贝操作，但是底层已经
                         //发生了所有权的转移，所以该智能指针存在
                         //隐患
    cout << "*ap2 = " << *ap2 << endl;
    cout << "*ap = " << *ap << endl;
    return 0;
}

