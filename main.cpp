#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack> // 用模板实现的栈
#include <queue> // 用模板实现的队列结构
#include <string>
#include <string.h>
using namespace std;

/*
C++ STL六大组件
容器 vector
迭代器 ：
你觉得迭代器是干什么用得？泛型算法为什么都要接收迭代器作为参数？
迭代器 =》 迭代 =》 容器的

数组  链表  哈希表  树
p++   p = p->next

迭代器遍历所有容器的方式都是一模一样的！！！！
*/

template<typename T>
struct myallocator
{
    // 内存开辟
    T* allocate(size_t size)
    {
        return (T*)malloc(size * sizeof(T));
    }

    // 内存释放
    void deallocate(T *ptr)
    {
        free(ptr);
    }

    // 对象构造 1.new 2.new const 3.定位new
    void construct(T *ptr, const T &obj)
    {
        new (ptr)T(obj); // 定位new
    }

    // 对象析构
    void destroy(T *ptr)
    {
        ptr->~T();
    }
};

// 类模板 vector 默认构造 size:0-1-2-4-8-16-32-64....
template<typename T = int,
    typename _Alloc = myallocator<T >>
class Vector // 类的模板名字
{
public:
    Vector() :mcur(0)
        , msize(0)
        , mpvec(nullptr)
    {

    }

    ~Vector()
    {
        for (int i = 0; i <= mcur; ++i)
        {
            // 析构容器中有效的对象
            malloctor.destroy(mpvec + i);
        }
        // 把容器内存释放掉
        malloctor.deallocate(mpvec);
        mpvec = nullptr;
    }
    Vector(const Vector<T> &vec)
    {
        msize = vec.msize;//空间大小
        mcur = vec.mcur;//现在存的元素个数
        mpvec = malloctor.allocate(msize);
        for (int i = 0; i <= mcur; i++)
        {
            malloctor.construct(mpvec + i, vec.mpvec[i]);
        }
    }
    Vector(Vector<T> &&vec)
    {
        mpvec = vec.mpvec;
        vec.mpvec = nullptr;
        mcur = vec.mcur;
        msize = vec.msize;
    }
    void operator=(const Vector<T> &vec)
    {
        if (this == &vec)
        {
            return;
        }
        for (int i = 0; i <= mcur; i++)
        {
            malloctor.destory(mpvec + i);
        }
        malloctor.deallocate(mpvec);

        msize = vec.msize;//空间大小
        mcur = vec.mcur;//现在存的元素个数

        mpvec = malloctor.allocate(msize);
        for (int i = 0; i <= mcur; i++)
        {
            malloctor.construt(mpvec + i, vec.mpvec[i]);
        }
    }
    void operator=(Vector<T> &&vec)
    {
        if (this == &vec)
        {
            return;
        }
        for (int i = 0; i <= mcur; i++)
        {
            malloctor.destory(mpvec + i);
        }
        malloc.deallocate(mpvec);

        msize = vec.msize;
        mcur = vec.mcur;
        mpvec = vec.mpvec;
        vec.mpvec = nullptr;
    }

    void reserve(int size) // 预留函数
    {
        if (size <= msize)
            return;
        /*T* ptmp = malloctor.allocate(size);
        for (int i = 0; i < mcur; ++i)
        {
        malloctor.construct(ptmp + i, mpvec[i]);
        }
        for (int i = 0; i < mcur; i++)
        {
        malloctor.destroy(mpvec + i);
        }
        malloctor.deallocate(mpvec);
        mpvec = ptmp;
        msize = size;*/
        T* ptmp = malloctor.allocate(size);
        for (int i = 0; i < mcur; ++i)
        {
            malloctor.construct(ptmp + i, mpvec[i]);
            malloctor.destroy(mpvec + i);
        }
        malloctor.deallocate(mpvec);
        mpvec = ptmp;
        msize = size;
    }

    void push_back(const T &val) // 末尾添加元素
    {
        if (full())
        {
            //resize();
            reserve(1);
        }
        malloctor.construct(mpvec + mcur, val);
        mcur++;
    }
    void pop_back() // 末尾删除元素
    {
        if (empty())
        {
            return;
        }
        malloctor.destroy(mpvec + mcur);
        mcur--;
    }
    bool empty()const // 判空
    {
        return mcur == 0;
    }
    bool full()const // 判满
    {
        return mcur == msize;
    }
    int size()const // 返回vector容器元素的个数
    {
        return mcur;
    }

    void show()const // 打印vector容器的所有元素
    {
        for (int i = 0; i < mcur; i++)
        {
            cout << mpvec[i] << " ";
        }
        cout << endl;
    }

    T operator[](int i)
    {

        return mpvec[i];
    }

    // 作业，给当前Vector容器提供下面的实现
    // 1。提供迭代器的实现
    class iterator
    {
        friend class Vector;
    private:
        int *m_ptr;
    public:
        iterator(T *p = nullptr) :m_ptr(p) {}
        iterator& operator++()
        {
            m_ptr++;
            return *this;
        }

        iterator operator++(int)
        {
            T *tmp = m_ptr;
            m_ptr++;
            return iterator(tmp);
        }

        iterator& operator--()
        {
            m_ptr--;
            return *this;
        }

        iterator operator--(int)
        {
            T *tmp = m_ptr;
            m_ptr--;
            return iterator(tmp);
        }

        iterator operator-(int step)
        {
            m_ptr -= step;
            return *this;
        }

        bool operator==(const iterator &src)
        {
            return m_ptr == src.m_ptr;
        }

        bool operator!=(const iterator &src)
        {
            return m_ptr != src.m_ptr;
        }

        T& operator*()
        {
            return *(m_ptr);
        }
        T* getLocation()
        {
            return m_ptr;
        }
        T getIt()
        {
            return *m_ptr;
        }
        void setIt(const T &val)
        {
            *m_ptr = val;
        }
        void operator+=(const int &step)
        {
            m_ptr += step;
        }
        void iteratorSwap(T &val)
        {
            T tmp = *m_ptr;
            *m_ptr = val;
            val = tmp;
        }
    };
    iterator begin()
    {
        return iterator(mpvec);
    }
    iterator end()
    {
        return iterator(mpvec + mcur);
    }

    // 2.提供insert插入函数，返回插入位置的迭代器表示
    iterator insert(iterator &where, const T &val)
    {
#if 0
        /**/
        if (full())
        {
            int offset = where.m_ptr - mpvec;
            resize();
            where.m_ptr = mpvec + offset;
        }

        iterator itTmp = begin();
        if (where == end())
        {
            push_back(val);
        }

        else
        {
            T tmp;
            while (itTmp != where)
            {
                ++itTmp;
            }
            tmp = val;
            while (itTmp != end())
            {
                itTmp.iteratorSwap(tmp);
                ++itTmp;
            }

            push_back(tmp);

        }
        return where;
#endif
        /*
        最开始我的方法为什么reserve可以呢？
        举个例子，如果最开始没有开辟空间，插入一个元素，开辟一个空间
        然后insert，我当时每次扩容都用reserve(1)，这样每次你都等于msize，
        也就不会进入真正开辟空间的指令，那为什么还能插入对象呢，因为压根没有插入
        而是直接构造了，虽然说那块空间没有被开辟，但你仍然可以对那块空间进行赋值
        所以问题被隐藏了
        */

        //如果插入位置不正确就会抛出异常
        if (where.m_ptr < mpvec || where.m_ptr > mpvec + mcur)
        {
            throw "xxx";
        }

        // 扩容
        //这个很重要如果没有这个你每次扩容之后，where指向的内容被析构，空间被释放，
        //where指向的值就是垃圾值了，按照逻辑，where指向的内容应该还是逻辑上的插入位置
        /*if (full())
        {
            int offset = where.m_ptr - mpvec;
            resize();
            where.m_ptr = mpvec + offset;
        }*/

        T *p = mpvec + mcur;
        while (p > where.m_ptr)
        {
            malloctor.construct(p, *(p - 1));
            malloctor.destroy(p - 1);
            p--;
        }

        // p -> where
        malloctor.construct(p, val);
        mcur++;
        return iterator(p);/**/


    }

    // 3.删除指定位置的元素，返回当前位置的迭代器表示
    iterator erase(iterator &where)
    {
#if 0
        iterator itTmp = end() - 1;
        T tmp = *itTmp;
        while (itTmp != where)
        {
            (itTmp - 1).iteratorSwap(tmp);
            itTmp--;
        }
        pop_back();
        return where;
#endif
        if (where.m_ptr < mpvec || where.m_ptr > mpvec + mcur - 1)
        {
            throw "xxx";
        }

        T *p = where.m_ptr;
        while (p < mpvec + mcur - 1)
        {
            malloctor.destroy(p);
            malloctor.construct(p, *(p + 1));//注意这里是对底层T *指针进行操作，
            //我上面的错误代码是对迭代器操作
            p++;
        }
        malloctor.destroy(p);

        mcur--;
        return iterator(where.m_ptr); // T* iterator(T*)
    }

    // 4.提供operator    vec[2];    中括号[]运算符重载函数

private:
    T *mpvec;
    int mcur;
    int msize;
    _Alloc malloctor; // 定义空间配置器对象 

    void resize() // vector容器底层默认2倍扩容
    {
        if (msize > 0)
        {
            T *ptmp = malloctor.allocate(msize * 2);
            for (int i = 0; i < msize; i++)
            {
                malloctor.construct(ptmp + i, mpvec[i]);
                // 析构容器中有效的对象
                malloctor.destroy(mpvec + i);
            }
            // 把容器内存释放掉
            malloctor.deallocate(mpvec);
            mpvec = ptmp;
            msize *= 2;
        }
        else
        {
            mpvec = malloctor.allocate(1); // size * sizeof(T)
            msize = 1;
            mcur = 0;
        }
    }

};

// char *p = "dddd"l char arr[]="4444";
int main()
{
    Vector<int> vec;
    vec.reserve(10);
    for (int i = 0; i < 5; ++i)
        vec.push_back(rand() % 100);


    for (int i = 0; i < vec.size(); ++i)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    int a = 1;
    //iterator begin() { return iterator(mptr); }
    Vector<int>::iterator it = vec.begin();
    for (; it != vec.end();)
    {
        vec.insert(it, 1);

        a++;
        it += 2;
    }
    for (int val : vec)
    {
        cout << val << " ";
    }
    cout << endl;
    /*it = vec.end();
    vec.insert(it, 12);*/
    cout << endl;
    it = vec.begin();
    for (; it != vec.end();)
    {
        if (*it == 1)
        {
            it = vec.erase(it);
        }
        else
        {
            ++it;
        }
    }
    // foreach
    for (int val : vec)
    {
        cout << val << " ";
    }
    cout << endl;
}