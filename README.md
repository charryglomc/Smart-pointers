# 智能指针和String移动语义重载

### RAII资源管理

- RAII(Resource Acquisition Is Initialization)是一种由 C++创造者 Bjarne Stroustrup 提出的， 利用栈对象生命周期管理程序资源（包括内存、文件句柄、锁等）的技术。

- 使用 RAII 时，一般在资源获得的同时构造对象， 在对象生存期间，资源一直保持有效；对象析构时，资源被释放。

- 关键：要保证资源的释放顺序与获取顺序严格相反

#### 1、auto_ptr 

本身是有缺陷的，在执行拷贝构造函数与赋值运算符函数的时候，表面上执行拷贝赋值，但是底层已经发生所有权的转移，所以有缺陷。

```C++
//auto_ptr<int> ap2(ap)
auto_ptr(auto_ptr& __a)  
: _M_ptr(__a.release()) 
{

}

_Tp* release()  {
    _Tp* __tmp = _M_ptr;
    _M_ptr = nullptr;
    return __tmp;
  }

 _Tp& operator*() const __STL_NOTHROW {
    return *_M_ptr;
  }
```



#### 2、unique_ptr

独享所有权的智能指针，在语法层面就不能进行复制或者赋值，所以避免auto_ptr所有权转移的问题，所以相对来说比较安全。
具有移动语义，就含有移动构造函数和移动赋值函数，所以可以作为容器的参数

```C++
unique_ptr<Point> up4(new Point(1, 2));
vector<unique_ptr<Point>> vec;
/* vec.push_back(up4);//errror */
vec.push_back(std::move(up4));
vec.push_back(unique_ptr<Point>(new Point(1, 3)));
```



#### 3、shared_ptr

共享所有权的智能指针，可以进行复制与赋值，所以可以进行拷贝与赋值操作。

但是有循环引用的问题：内存泄漏。
解决方案：使用weak_ptr。



#### 4、weak_ptr

弱引用的智能指针，不会使引用计数增加。没有重载解引用与箭头运算符，不能去访问托管的资源。需要使用lock或者expired查看托管资源还存在不。

### 三、删除器

针对unique_ptr的第二个模板参数以及shared_ptr的构造函数的第二个参数，默认情况下，删除器使用的是delete或者delete []进行的删除。

如果初始化资源的时候使用的不是new，那就需要使用到对应的释放资源的方式，比如：FILE指针

```C++
tempalte <class T, class Deleter = std::default_delete<T>>
class unique_ptr;

template< class T > struct default_delete;


struct default_delete
{
    void operator()(T* ptr) const
	{
	     //delete   delete[]
	}
	
};


struct default_delete
{
    void operator()(FILE* ptr) const
	{
	     fclose(ptr);
	}
	
};
```



### String移动语义重载

- 移动函数(移动构造函数和移动赋值运算符函数)**优先于**复制函数(拷贝构造函数和赋值运算符函数)的执行
- 具有移动语义的函数(移动构造函数和移动赋值运算符函数)**优先于**具有复制控制语义函数(拷贝构造函数和赋值运算符函数)的执行
- 将左值转换为右值，在内部其实上是做了一个强制转换， static_cast<T &&>(lvaule) 。将左值转换为右值后，左值就不能直接使用了，如果还想继续使用，必须重新赋值。
- std::move()作用于内置类型没有任何作用，内置类型本身是左值还是右值，经过std::move()后不会改变。

