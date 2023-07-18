#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;

class Child;//前向声明

class Parent
{
public:
    Parent()
    {
        cout << "Parent()" << endl;
    }

    ~Parent()
    {
        cout << "~Parent()" << endl;
    }

    shared_ptr<Child> pParent;
};

class Child
{
public:
    Child()
    {
        cout << "Child()" << endl;
    }

    ~Child()
    {
        cout << "~Child()" << endl;
    }

    shared_ptr<Parent> pChild;
};

int main(int argc, char **argv)
{
    shared_ptr<Parent> ptrParent(new Parent());//智能指针（栈对象）
    shared_ptr<Child> ptrChild(new Child());
    cout << "ptrParent.use_count() = " << ptrParent.use_count() << endl;
    cout << "ptrChild.use_count() = " << ptrChild.use_count() << endl;

    cout << endl;
    ptrParent->pParent = ptrChild;//sp = sp;
    ptrChild->pChild = ptrParent;//sp = sp;
    cout << "ptrParent.use_count() = " << ptrParent.use_count() << endl;
    cout << "ptrChild.use_count() = " << ptrChild.use_count() << endl;
    return 0;
}

