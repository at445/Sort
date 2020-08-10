// MaxSubarraySearch.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>
#include <random>
struct ret {
    int maxSum;
    int startPos;
    int stopPos;
};
int* dataGneratorRandom(int len)
{
    int* p = new int[len];
    std::default_random_engine e;
    for (int i = 0; i < len; i++) {
        *(p + i) = e() % len - len/2;
    }
    return p;
}
const std::shared_ptr<struct ret> FindMaxSubArrayInTheMiddle(const int* p, int st, int stop)
{
    if (st == stop) {
        auto result = std::make_shared<struct ret>();
        result->stopPos = result->startPos = st;
        result->maxSum = p[st-1];
        return result;
    }
    int middle = (st + stop) / 2;
    auto lRet = FindMaxSubArrayInTheMiddle(p, st, middle);
    auto rRet = FindMaxSubArrayInTheMiddle(p, middle + 1, stop);

    auto result = std::make_shared<struct ret>();
    int Max = p[middle - 1];
    int TempLeft = 0;
    for (int i = middle; i >= 1; i--) {
        TempLeft += p[i - 1];
        if (TempLeft >= Max) {
            result->startPos = i;
            Max = TempLeft;
        }
    }
    Max = p[middle - 1];
    int TempRight = 0;
    for (int i = middle; i <= stop; i++) {
        TempRight += p[i - 1];
        if (TempRight >= Max) {
            result->stopPos = i;
            Max = TempRight;
        }
    }
    for (int i = result->startPos; i <= result->stopPos; i++) {
        result->maxSum += p[i - 1];
    }
    
    if (lRet->maxSum > result->maxSum) {
        result = std::move(lRet);
    }
    
    if (rRet->maxSum > result->maxSum) {
        result = std::move(rRet);
    }
    return result;
}

int main()
{
    int str[] = { -1,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
    int * str2 = dataGneratorRandom(1000);
    auto ret = FindMaxSubArrayInTheMiddle(str, 1, sizeof(str) / sizeof(int));
    std::cout << ret->maxSum << "   " << ret->startPos << "  " << ret->stopPos << std::endl;
    ret = FindMaxSubArrayInTheMiddle(str, 1, 11);
    std::cout << ret->maxSum << "   " << ret->startPos << "  " << ret->stopPos << std::endl;
    ret = FindMaxSubArrayInTheMiddle(str, 1, 3);
    std::cout << ret->maxSum << "   " << ret->startPos << "  " << ret->stopPos << std::endl;
    ret = FindMaxSubArrayInTheMiddle(str2, 1, 1000);
    std::cout << ret->maxSum << "   " << ret->startPos << "  " << ret->stopPos << std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
