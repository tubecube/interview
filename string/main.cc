#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <assert.h>
#include "qh_string.h"

const char* hello = "hello";
const char* null = NULL;

void test_default_ctor()
{
    qh::string str;
    assert(str.size()==0 && str.data()==NULL);
    printf("%s : test OK!\n", __FUNCTION__);
}

void test_cstring_ctor()
{
    qh::string str(hello);
    assert(str.size() == strlen(hello));
    assert(strcmp(str.data(), hello) == 0);
    printf("%s : test OK!\n", __FUNCTION__);
}

void test_cstring_with_len_ctor()
{
    qh::string str(hello, 2);
    assert(strcmp(str.data(), "he") == 0);
    assert(str.size() == 2);
    printf("%s : test OK!\n", __FUNCTION__);
}

void test_cpy_ctor()
{
    qh::string str1(hello);
    qh::string str2(str1);
    assert(strcmp(str2.data(), str1.data()) == 0);
    assert(str2.size() == str1.size());
    printf("%s : test OK!\n", __FUNCTION__);
}

void test_assignment_op()
{
    qh::string str1(hello);
    qh::string str2;
    str2 = str1;
    assert(strcmp(str2.data(), str1.data()) == 0);
    assert(str2.size() == str1.size());
    printf("%s : test OK!\n", __FUNCTION__);
}

void test_set_get()
{
    qh::string str(hello);
    assert(strcmp(str.c_str(), "hello") == 0);
    assert(*(str[0]) == 'h');
    assert(str[5] == NULL);
    *(str[0]) = 'H';
    assert(strcmp(str.c_str(), "Hello") == 0);
    printf("%s : test OK!\n", __FUNCTION__);
}



int main(int argc, char* argv[])
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�

    test_default_ctor();
    test_cstring_ctor();
    test_cstring_with_len_ctor();
    test_cpy_ctor();
    test_assignment_op();
    test_set_get();


#ifdef WIN32
    system("pause");
#endif

	return 0;
}

