//
// Created by aicdg on 2017/2/2.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
};

static int averageAndSum(lua_State *L); // 要添加到lua中的函数
void MyLuaInterpreter();

int main()
{
    MyLuaInterpreter();
    return 0;
}

void MyLuaInterpreter()
{
    lua_State *L = luaL_newstate();

    luaL_openlibs(L);  // 使用luaopen打开lua标准库

//  1.  把值传入lua
    int valueFromCpp = 100;
    // 将值压入栈顶
    lua_pushnumber(L, valueFromCpp);
    // 给栈顶的值命名
    lua_setglobal(L, "valueFromCpp");

//  2. 把函数传入lua
    lua_register(L, "averageAndSum", averageAndSum);
//    等价于
//    lua_pushcfunction(L, averageAndSum);
//    lua_setglobal(L, "averageAndSum");

    string str;
    while (true) {
        cout << "请输入 lua 代码路径" << endl;
        cout << "> ";
        getline(cin, str, '\n');

        if (luaL_loadfile(L, str.c_str()) || lua_pcall(L, 0, 0, 0)) {
            const char *msg = lua_tostring(L, -1);
            cout << string(msg) << endl;
        } else {
            break;
        }
    }

    lua_close(L);
}

static int averageAndSum(lua_State *L)
{
//    得到参数个数
    int n = lua_gettop(L);
    double sum = 0;

//    循环求参数之和
    for (int i = 1; i <=n; i++)
    {
        sum += lua_tonumber(L, i); // lua的参数从1开始
    }

//    返回第一个返回值(平均数)
    lua_pushnumber(L, sum / n);
//    返回第二个返回值(和)
    lua_pushnumber(L, sum);
//    返回返回值的个数
    return 2;
}