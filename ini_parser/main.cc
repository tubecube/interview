#include "ini_parser.h"

#include <string.h>
#include <assert.h>
#include <iostream>

void test1()
{
    const char* ini_text= "a=1\nb=2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    const std::string& b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "");

    std::cout << __FUNCTION__ << " success!\n";
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    const std::string& b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");

    std::cout << __FUNCTION__ << " success!\n";
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");

    std::cout << __FUNCTION__ << " success!\n";
}

void test4()
{
    const char* ini_text="t1==1&&t2==2&&t3==3&&";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "&&", "==")) {
        assert(false);
    }

    const std::string& t1 = parser.Get("t1", NULL);
    assert(t1 == "1");

    const std::string& t2 = parser.Get("t2", NULL);
    assert(t2 == "2");

    const std::string& t3 = parser.Get("t3", NULL);
    assert(t3 == "3");

    std::cout << __FUNCTION__ << " success!\n";
}

void test_file()
{
    std::string file_path = "system.ini"; 
    qh::INIParser parser;
    assert(parser.Parse(file_path) == true);

    const std::string& wave = parser.Get("drivers", "wave", NULL);
    assert(wave == "mmdrv.dll");

    const std::string& OFFLINE = parser.Get("TCY181259294", "OFFLINE", NULL);
    assert(OFFLINE == "0");
    std::cout << __FUNCTION__ << " success!\n";
}


int main(int argc, char* argv[])
{
    //TODO ÔÚÕâÀïÌí¼Óµ¥Ôª²âÊÔ£¬Ô½¶àÔ½ºÃ£¬´úÂëÂ·¾¶¸²¸ÇÂÊÔ½È«Ô½ºÃ

    test1();
    test2();
    test3();
    test4();
    test_file();

    return 0;
}


