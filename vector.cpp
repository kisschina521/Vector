#include "stdafx.h"
#include "Vector.h"
template<typename T>
Vector<T>::Vector()
    :mcur(0)
    , msize(0)
    , mpvec(nullptr) {}

template<typename T>
Vector<T>::~Vector()
{
    delete[]mpvec;
    mcur = 0;
    msize = 0;
    mpvec = nullptr;
}
template<typename T>
Vector<T>::Vector(const Vector<T> &vec)
{
    mpvec = new T [vec.msize];
    for (int i = 0; i < vec.msize; ++i)
    {
        mpvec[i] = vec.mpvec[i];
    }
    mcur = vec.mcur;
    msize = vec.msize;
    //return;
}

template<typename T>
void Vector<T>::operator= (const Vector<T> &vec)
{
    /*mpvec = new T [vec.msize];
    for (int i = 0; i < vec.msize; ++i)
    {
        mpvec[i] = vec.mpvec[i];
    }
    mcur = vec.mcur;
    msize = vec.msize;*/
    if (this == &vec) return;
    delete[]mpvec;

    msize = vec.msize;
    mcur = vec.mcur;
    mpvec = new T[msize];
    for (int i = 0; i < mcur; ++i)
    {
        mpvec[i] = vec.mpvec[i];
    }
}/**/
/**/
template<typename  T>
Vector<T>::Vector(Vector<T> &&vec)
{
    mpvec = vec.mpvec;
    msize = vec.msize;
    mcur = vec.cur;
    vec.mpvec = nullptr;
}
template<typename  T>
void Vector<T>:: operator=(Vector<T> &&vec)
{
    mpvec = vec.mpvec;
    msize = vec.msize;
    mcur = vec.cur;
    vec.mpvec = nullptr;

}
template<typename T>
void Vector<T>::push_back(const T &val)
{
    if (full())
    {
        resize();
    }
    mpvec[mcur++] = val;
    //return;
}
/*template<typename T>
void Vector<T>::push_back(const T &val)
{
    if (full())
    {
        resize();
    }
    mpvec[++mcur] = val;
    return;
}*/

template<typename T>
bool Vector<T>::empty()const
{
    return mcur == 0;
}
template<typename T>
bool Vector<T>::full()const
{
    return mcur == msize;
}
template<typename T>
void Vector<T>::pop_back()
{
    if (empty())
    {
        return;
    }
    mcur--;
    return;
}
template<typename T>
void Vector<T>::resize()
{
    if (msize == 0)
    {
        msize = 1;
        //mpvec = new T[msize];
    }
    mpnew = new  T [msize * 2];
    for (int i = 0; i < mszie; ++i)
    {
        mpnew[i] = mpvec[i];
    }
    delete[]mpvec;
    mpvec = mpnew;
    msize *= 2;
    return;
}
template<typename T>
void Vector<T>::reserve(int size)
{
    mpvec = new T[size];
    return;
    if (size <= msize)
    {
        return;
    }
    T *
}
template<typename T>
void Vector<T>::show() const
{
    int i = 0;
    for (; i < mcur + 1; ++i)
    {
        cout << mpvec[i];
    }
    return;
}