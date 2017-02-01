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
//    luaopen_base(L);
//    luaopen_table(L);
//    luaopen_string(L);
//    在lua5.1中不需要luaopen_*系列函数

    luaL_openlibs(L);  // 使用luaopen打开lua标准库

    string str;

    while (true)
    {
        cout << "请输入 lua 代码，输入 quit() 退出 lua 解释器" << endl;
        cout << "> ";
        getline(cin, str, '\n');
        if (str == "quit()") break;

        if (luaL_loadstring(L, str.c_str()) || lua_pcall(L, 0, 0, 0))
        {
            const char * msg = lua_tostring(L, -1);
            cout << string(msg) << endl;
        }
    }

    lua_close(L);
}
