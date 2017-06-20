#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "qh_vector.h"


void test_ctor()
{
    qh::vector<int> vi;
    assert(vi.size() == 0 && vi.capacity() == 0);
    qh::vector<double> vd(10, 5.0);
    assert(vd.size() == 10 && vd.capacity() == 10);
    qh::vector<double> vd2(20, 1);
    vd2 = vd;
    for (size_t i = 0; i < vd2.size(); ++i)
    {
        assert(vd[i] == vd2[i]);
    }
    assert(vd2.size() == vd.size() && vd2.capacity() == vd.capacity());
    printf("%s: All test OK!\n", __FUNCTION__);
}

void test_push_pop()
{
    qh::vector<int> vi;
    for (int i=0; i<5; ++i)
    {
        vi.push_back(i);
    }
    assert(vi.size() == 5);
    for (int i=4; i>=0; --i)
    {
        assert(vi[i] == i);
        vi.pop_back();
    }
    assert(vi.size() == 0);
    printf("%s: All test OK!\n", __FUNCTION__);
}

void test_clear_empty()
{
    qh::vector<int> vi(10, 1);
    vi.clear();
    assert(vi.size() == 0);
    assert(vi.empty() == true);
    printf("%s: All test OK!\n", __FUNCTION__);
}

void test_resize_reserve()
{
    qh::vector<int> vi;
    vi.resize(10, 100);
    assert(vi.size() == 10);
    for (int i=0; i<10; ++i)
        assert(vi[i] == 100);
    vi.reserve(1000);
    assert(vi.capacity() == 1000);
    printf("%s: All test OK!\n", __FUNCTION__);
}

void test_set_get()
{
    qh::vector<int> vi(10, 2);
    assert(vi[5] == 2);
    vi[5] = 1;
    assert(vi[5] == 1);
    printf("%s: All test OK!\n", __FUNCTION__);
}


int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
    test_ctor();
    test_push_pop();
    test_clear_empty();
    test_resize_reserve();
    test_set_get();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

