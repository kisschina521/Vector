#include "stdafx.h"
// ��ģ�� vector Ĭ�Ϲ��� size:0-1-2-4-8-16-32-64....
#include <iostream>
using namespace std;
#include <string>
template<typename T = int>
class Vector // ���ģ������
{
public:
    Vector();
    ~Vector();
    Vector(const Vector<T> &vec);
    Vector(Vector<T> &&vec);
    void operator=(const Vector<T> &vec);
    void operator=(Vector<T> &&vec);

    void reserve(int size); // Ԥ������

    void push_back(const T &val); // ĩβ���Ԫ��
    void pop_back(); // ĩβɾ��Ԫ��
    bool empty()const; // �п�
    bool full()const; // ����

    void show()const; // ��ӡvector����������Ԫ��
private:
    T *mpvec;
    int mcur;
    int msize;

    void resize(); // vector�����ײ�Ĭ��2������
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