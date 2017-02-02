//
// Created by aicdg on 2017/2/2.
//

#include <stdio.h>
//#include "myLuaLib.h"
extern "C"
{

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#ifdef _MSC_VER
#define PUGILUA __declspec(dllexport)
#else
#define PUGILUA
#endif

static int averageAndSumFunc(lua_State *L)
{
    int n = lua_gettop(L);
    double sum = 0;
    int i;

    /* 循环求参数之和 */
    for (i = 1; i <= n; i++)
        sum += lua_tonumber(L, i);

    lua_pushnumber(L, sum / n);     //压入平均值
    lua_pushnumber(L, sum);         //压入和

    return 2;                       //返回两个结果
}

static int sayHelloFunc(lua_State* L)
{
    printf("hello world!\n");
    return 0;
}

static const luaL_Reg myLib[] = {
        {"averageAndSum", averageAndSumFunc},
        {"sayHello", sayHelloFunc},
        {NULL, NULL}       //数组中最后一对必须是{NULL, NULL}，用来表示结束
};

extern "C" PUGILUA int luaopen_libmyLuaLib(lua_State *L)
{
    printf("luaopen_LuaDll invoked\n");
    luaL_register(L, "myModule", myLib);
    return 1;
}