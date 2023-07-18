#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::shared_ptr;
using std::string;

struct FILECloser
{
    void operator()(FILE *fp) const
    {
        if(nullptr != fp)
        {
            fclose(fp);
            cout << "fclose(fp)" << endl;
        }
    }
};

void test()
{
    string msg = "hello,world\n";
    unique_ptr<FILE, FILECloser> up(fopen("wd.txt", "a+")); //默认的删除器采用delete释放堆空间，而文件流指针也delete会出现问题
    fwrite(msg.c_str(), 1, msg.size(), up.get());
    /* fclose(up.get()); */
}

void test2()
{
    FILECloser fc;
    string msg = "hello,world\n";
    shared_ptr<FILE> sp(fopen("test.txt", "a+"), FILECloser()); 
    /* shared_ptr<FILE> sp(fopen("test.txt", "a+"), fc); */
    fwrite(msg.c_str(), 1, msg.size(), sp.get());
    /* fclose(sp.get()); */
}
int main(int argc, char **argv)
{
    test2();
    return 0;
}

