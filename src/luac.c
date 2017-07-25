#include <stdio.h>
#include <string.h>
#include "include/lua.h"
#include "include/lualib.h"
#include "include/lauxlib.h"

//待Lua调用的C注册函数。
static int add2(lua_State* L)
{
    //检查栈中的参数是否合法，1表示Lua调用时的第一个参数(从左到右)，依此类推。
    //如果Lua代码在调用时传递的参数不为number，该函数将报错并终止程序的执行。
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    //将函数的结果压入栈中。如果有多个返回值，可以在这里多次压入栈中。
    lua_pushnumber(L,op1 + op2);
    //返回值用于提示该C函数的返回值数量，即压入栈中的返回值数量。
    return 1;
}

//另一个待Lua调用的C注册函数。
static int sub2(lua_State* L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1 - op2);
    return 1;
}

void callLuaFunc2(lua_State *L, const char*fname) {
    if(luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
        printf("cannot run file:%s", lua_tostring(L, -1));
    }else {
        lua_getglobal(L, "testCFunction");
        if(lua_pcall(L, 0, 1, 0) != 0) {
            printf("error running function 'testCFunction' is %s", lua_tostring(L, -1));
        }else {
            if(!lua_isnumber(L, -1)) {
                printf("function 'testCFunction' return should be a number");
            }else {
                printf("function 'testCFunction' return is %s", lua_tostring(L, -1));
            }
        }
    }
}

void functionTest()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    //将指定的函数注册为Lua的全局函数变量，其中第一个字符串参数为Lua代码
    //在调用C函数时使用的全局函数名，第二个参数为实际C函数的指针。
    lua_register(L, "add2", add2);
    lua_register(L, "sub2", sub2);

    callLuaFunc2(L, "src/lua/Demo2.lua");
    lua_close(L);
}
