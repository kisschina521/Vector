#include "stdafx.h"
// 类模板 vector 默认构造 size:0-1-2-4-8-16-32-64....
#include <iostream>
using namespace std;
#include <string>
template<typename T = int>
class Vector // 类的模板名字
{
public:
    Vector();
    ~Vector();
    Vector(const Vector<T> &vec);
    Vector(Vector<T> &&vec);
    void operator=(const Vector<T> &vec);
    void operator=(Vector<T> &&vec);

    void reserve(int size); // 预留函数

    void push_back(const T &val); // 末尾添加元素
    void pop_back(); // 末尾删除元素
    bool empty()const; // 判空
    bool full()const; // 判满

    void show()const; // 打印vector容器的所有元素
private:
    T *mpvec;
    int mcur;
    int msize;

    void resize(); // vector容器底层默认2倍扩容
};


/*int main()
{
    Vector<> intVec;
    intVec.push_back(20);
    intVec.push_back(30);
    intVec.push_back(21);
    intVec.show();

    Vector<string> strVec;
    strVec.push_back("hello");
    strVec.push_back("world");
    strVec.show();

    return 0;
}*/