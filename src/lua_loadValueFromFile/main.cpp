//
// Created by aicdg on 2017/2/1.
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

    double a, b;

    // 1. 获取a的值
    lua_getglobal(L, "a");
    a = lua_tonumber(L, -1);

    // 2. 获取b的值
    lua_getglobal(L, "b");
    b = lua_tonumber(L, -1);

    cout << "a = " << a << " b = " << b << endl;
    cout << "a + b = " << a + b << endl;

    // 3. 读取字符串
    lua_getglobal(L, "strc");
    string strc = lua_tostring(L, -1);
    cout << "strc: " << strc << endl;

    // 4. 读取table
    lua_getglobal(L, "table");
    lua_getfield(L, -1, "tabA");
    double tabA = lua_tonumber(L, -1);
    cout << "table.tabA = " << tabA << endl;
    lua_getfield(L, -2, "tabStr");
    string tabStr = lua_tostring(L, -1);
    cout << "table.tabStr = " << tabStr << endl;

    // 5. 读取函数
    lua_getglobal(L, "add");            // 获取函数
    lua_pushnumber(L, 11);              // 压入第一个参数
    lua_pushnumber(L, 22);              // 压入第二个参数
    int iRet = lua_pcall(L, 2, 1, 0);    // 调用函数，调用完成以后，会将返回值压入栈中，2表示参数个数，1表示返回结果个数。
    if(iRet)     // 错误处理
    {
        const char *pErrorMsg = lua_tostring(L, -1);
        cout << pErrorMsg << endl;
        lua_close(L);
        return ;
    }
    if (lua_isnumber(L, -1))
    {
        double res = lua_tonumber(L, -1);
        cout << "Func add result is : " << res << endl;
    }

    lua_close(L);
}