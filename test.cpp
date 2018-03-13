#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct MyClass
{
    int a;
    int b;
    MyClass(int a_, int b_) : a(a_), b(b_) { }
};

template<typename T, typename M, template<typename> class C = std::less>
struct member_comparer : std::binary_function<T, T, bool>
{
    explicit member_comparer(M T::*p) : p_(p) { }

    bool operator ()(T const& lhs, T const& rhs) const
    {
        return C<M>()(lhs.*p_, rhs.*p_);
    }

private:
    M T::*p_;
};

template<typename T, typename M>
member_comparer<T, M> make_member_comparer(M T::*p)
{
    return member_comparer<T, M>(p);
}

template<template<typename> class C, typename T, typename M>
member_comparer<T, M, C> make_member_comparer2(M T::*p)
{
    return member_comparer<T, M, C>(p);
}

int main()
{
    vector <MyClass> vec;
    vec.push_back(MyClass(2,9));
    vec.push_back(MyClass(0,1));
    vec.push_back(MyClass(0,0));
    vec.push_back(MyClass(1,7));
    vec.push_back(MyClass(0,7));
    vec.push_back(MyClass(2,5));
    vec.push_back(MyClass(0,6));
    vec.push_back(MyClass(3,1));
    std::sort(vec.begin(), vec.end(), make_member_comparer(&MyClass::a));
    for(int i=0;i<vec.size();i++)
    {
      cout<<vec[i].a<<vec[i].b<<endl;
    }
    int num1=vec[0].a;
    int count1=0,count2=0;   
    for(int i=0;i<vec.size();i++)
    {
        if(num1!=vec[i].a)
        {
            num1=vec[i].a;
            std::sort(vec.begin()+count1,vec.begin()+count2,make_member_comparer(&MyClass::b));
            count1=count2=i;
        }
        count2++;
    }
    for(int i=0;i<vec.size();i++)
    {
      cout<<vec[i].a<<vec[i].b<<endl;
    }
    return 0;
}