#include <iostream>
#include <windows.h>

/* 1. 使用数组的引用计算数组大小
不足：#define ARR_SIZE(A) (sizeof(A)/sizeof(A[0]))  这个方式计算数组长度会有问题，因为数组作为函数参数时，会退化为指针，所以sizeof(A)得到的是指针的大小
解决：使用ARRAYSIZE宏
采用数组的引用；使用数组的引用作为模板函数的参数，并返回数组的引用
*/
namespace COUNT_ARRAY_SIZE
{
    template<typename T, size_t N>
    char(&array_size_fake_func(T(&)[N]))[N];   // 返回数组的引用,如果是指针则编译不通过，无法推到出N的数值

    #define MYARRAYSIZE(A) sizeof(array_size_fake_func(A))

    void main()
    {
        int arr[10];
        std::cout << "my func: " <<MYARRAYSIZE(arr) << "\nsystem func: "<<ARRAYSIZE(arr) <<std::endl;
    }
}


int main()
{
    COUNT_ARRAY_SIZE::main();
    return 0;
}