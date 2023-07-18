#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;


void test()
{
    unique_ptr<int> up(new int(10));
    cout << "*up = " << *up << endl;
    cout << "up.get() = " << up.get() << endl;

    cout << endl;
    /* unique_ptr<int> up2(up);//error,不允许复制*/

    cout << endl;
    unique_ptr<int> up3(new int(20));
    /* up3 = up;//error,不允许赋值 */

    cout << endl;
    unique_ptr<int> up4(new int(30));
    vector<unique_ptr<int>> number;
    /* number.push_back(up4);//error */
    number.push_back(std::move(up4));
    number.push_back(unique_ptr<int>(new int(30)));

    cout << endl;
    vector<int *> vec;
    vec.push_back(new int(10));//error,堆空间new int(10)无法释放

}
int main(int argc, char **argv)
{
    test();
    return 0;
}

