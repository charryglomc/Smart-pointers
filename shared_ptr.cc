#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;


void test()
{
    shared_ptr<int> sp(new int(10));
    cout << "*sp = " << *sp << endl;  
    cout << "sp.get() = " << sp.get() << endl;
    cout << "sp.use_count() = " << sp.use_count() << endl;

    cout << endl;
    shared_ptr<int> sp2(sp);
    cout << "*sp2 = " << *sp2 << endl;
    cout << "*sp = " << *sp << endl;
    cout << "sp2.get() = " << sp2.get() << endl;
    cout << "sp.get() = " << sp.get() << endl;
    cout << "sp2.use_count() = " << sp2.use_count() << endl;
    cout << "sp.use_count() = " << sp.use_count() << endl;

    cout << endl;
    shared_ptr<int> sp3(new int(20));
    cout << "*sp3 = " << *sp3 << endl;
    cout << "sp3.get() = " << sp3.get() << endl;
    cout << "sp3.use_count() = " << sp3.use_count() << endl;
    cout << endl << endl;
    sp3 = sp;
    cout << "*sp3 = " << *sp3 << endl;
    cout << "*sp2 = " << *sp2 << endl;
    cout << "*sp = " << *sp << endl;
    cout << "sp3.get() = " << sp3.get() << endl;
    cout << "sp2.get() = " << sp2.get() << endl;
    cout << "sp.get() = " << sp.get() << endl;
    cout << "sp3.use_count() = " << sp3.use_count() << endl;
    cout << "sp2.use_count() = " << sp2.use_count() << endl;
    cout << "sp.use_count() = " << sp.use_count() << endl;

    cout << endl;
    shared_ptr<int> sp4(new int(30));
    vector<shared_ptr<int>> number;
    number.push_back(sp4); 
    number.push_back(std::move(sp4));
    number.push_back(shared_ptr<int>(new int(30)));

    /* cout << endl; */
    /* vector<int *> vec; */
    /* vec.push_back(new int(10));//error,堆空间new int(10)无法释放 */

}
int main(int argc, char **argv)
{
    test();
    return 0;
}

