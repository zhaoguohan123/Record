#ifndef _AutoPtr_HEAD_H
#define _AutoPtr_HEAD_H
#include <iostream>

namespace TestAutoPtr
{
    // 1. 给智能指针添加自定义的删除函数, 适用于一些特殊的资源释放
    template<typename _T, typename _D>
    auto make_unique_with_del(_T ptr, _D del)
    {
        return std::unique_ptr<std::remove_pointer<_T>::type, _D>(ptr, del);   // remove_pointer：返回指针指向的类型，若不是指针则返回原类型
    }






    //////////////////////////-------------------测试类,测试函数-------------------//////////////////////////
    class TestClass
    {
    public:
        int a_;
    public:
        TestClass(int);
        ~TestClass();
    };
    
    TestClass::TestClass(int a) 
    {
        a_ = a;
        std::cout << "TestClass::TestClass(): "<< a_ << std::endl;
    }
    
    TestClass::~TestClass()
    {
        std::cout << "TestClass::~TestClass: "<< a_ << std::endl;
    }

    void ReleaseTestClass(TestClass * ptr)
    {
        std::cout<< "ReleaseTestClass ptr.a_="<< ptr->a_ <<std::endl;
        if (ptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    void ReleaseTestClassV2(int a, TestClass* ptr)
    {
        std::cout<< "ReleaseTestClassV2 a = " << a  << " ptr.a_"<< ptr->a_<< std::endl;
        if (ptr)
        {
            delete ptr;     // 这里会调用析构函数
            ptr = nullptr;
        }
    }
    //////////////////////////-------------------测试类-------------------//////////////////////////


    void main()
    {
        TestClass * ptr = new TestClass(1);
        auto uptr = make_unique_with_del(ptr, ReleaseTestClass);

        int aaa = 2;
        TestClass * ptr1 = new TestClass(aaa);
        // 需要传入多个参数的删除函数的lambda表达式使用
        auto uptr2 = make_unique_with_del(ptr1, [aaa](TestClass * ptr1){ReleaseTestClassV2(aaa, ptr1);});
    }
    
}

#endif