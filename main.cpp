#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack> // ��ģ��ʵ�ֵ�ջ
#include <queue> // ��ģ��ʵ�ֵĶ��нṹ
#include <string>
#include <string.h>
using namespace std;

/*
C++ STL�������
���� vector
������ ��
����õ������Ǹ�ʲô�õã������㷨Ϊʲô��Ҫ���յ�������Ϊ������
������ =�� ���� =�� ������

����  ����  ��ϣ��  ��
p++   p = p->next

�������������������ķ�ʽ����һģһ���ģ�������
*/

template<typename T>
struct myallocator
{
    // �ڴ濪��
    T* allocate(size_t size)
    {
        return (T*)malloc(size * sizeof(T));
    }

    // �ڴ��ͷ�
    void deallocate(T *ptr)
    {
        free(ptr);
    }

    // ������ 1.new 2.new const 3.��λnew
    void construct(T *ptr, const T &obj)
    {
        new (ptr)T(obj); // ��λnew
    }

    // ��������
    void destroy(T *ptr)
    {
        ptr->~T();
    }
};

// ��ģ�� vector Ĭ�Ϲ��� size:0-1-2-4-8-16-32-64....
template<typename T = int,
    typename _Alloc = myallocator<T >>
class Vector // ���ģ������
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
            // ������������Ч�Ķ���
            malloctor.destroy(mpvec + i);
        }
        // �������ڴ��ͷŵ�
        malloctor.deallocate(mpvec);
        mpvec = nullptr;
    }
    Vector(const Vector<T> &vec)
    {
        msize = vec.msize;//�ռ��С
        mcur = vec.mcur;//���ڴ��Ԫ�ظ���
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

        msize = vec.msize;//�ռ��С
        mcur = vec.mcur;//���ڴ��Ԫ�ظ���

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

    void reserve(int size) // Ԥ������
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

    void push_back(const T &val) // ĩβ���Ԫ��
    {
        if (full())
        {
            //resize();
            reserve(1);
        }
        malloctor.construct(mpvec + mcur, val);
        mcur++;
    }
    void pop_back() // ĩβɾ��Ԫ��
    {
        if (empty())
        {
            return;
        }
        malloctor.destroy(mpvec + mcur);
        mcur--;
    }
    bool empty()const // �п�
    {
        return mcur == 0;
    }
    bool full()const // ����
    {
        return mcur == msize;
    }
    int size()const // ����vector����Ԫ�صĸ���
    {
        return mcur;
    }

    void show()const // ��ӡvector����������Ԫ��
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

    // ��ҵ������ǰVector�����ṩ�����ʵ��
    // 1���ṩ��������ʵ��
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

    // 2.�ṩinsert���뺯�������ز���λ�õĵ�������ʾ
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
        �ʼ�ҵķ���Ϊʲôreserve�����أ�
        �ٸ����ӣ�����ʼû�п��ٿռ䣬����һ��Ԫ�أ�����һ���ռ�
        Ȼ��insert���ҵ�ʱÿ�����ݶ���reserve(1)������ÿ���㶼����msize��
        Ҳ�Ͳ�������������ٿռ��ָ���Ϊʲô���ܲ�������أ���Ϊѹ��û�в���
        ����ֱ�ӹ����ˣ���Ȼ˵�ǿ�ռ�û�б����٣�������Ȼ���Զ��ǿ�ռ���и�ֵ
        �������ⱻ������
        */

        //�������λ�ò���ȷ�ͻ��׳��쳣
        if (where.m_ptr < mpvec || where.m_ptr > mpvec + mcur)
        {
            throw "xxx";
        }

        // ����
        //�������Ҫ���û�������ÿ������֮��whereָ������ݱ��������ռ䱻�ͷţ�
        //whereָ���ֵ��������ֵ�ˣ������߼���whereָ�������Ӧ�û����߼��ϵĲ���λ��
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

    // 3.ɾ��ָ��λ�õ�Ԫ�أ����ص�ǰλ�õĵ�������ʾ
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
            malloctor.construct(p, *(p + 1));//ע�������ǶԵײ�T *ָ����в�����
            //������Ĵ�������ǶԵ���������
            p++;
        }
        malloctor.destroy(p);

        mcur--;
        return iterator(where.m_ptr); // T* iterator(T*)
    }

    // 4.�ṩoperator    vec[2];    ������[]��������غ���

private:
    T *mpvec;
    int mcur;
    int msize;
    _Alloc malloctor; // ����ռ����������� 

    void resize() // vector�����ײ�Ĭ��2������
    {
        if (msize > 0)
        {
            T *ptmp = malloctor.allocate(msize * 2);
            for (int i = 0; i < msize; i++)
            {
                malloctor.construct(ptmp + i, mpvec[i]);
                // ������������Ч�Ķ���
                malloctor.destroy(mpvec + i);
            }
            // �������ڴ��ͷŵ�
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