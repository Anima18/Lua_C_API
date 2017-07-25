#include <stdio.h>
#include <stdlib.h>
#include "include/lua.h"
#include "include/lualib.h"
#include "include/lauxlib.h"
#include "mytestlib.h"

extern int luaopen_mytestlib(lua_State *L);

void callLuaFunc3(const char*fname) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    //把C模块注册到Lua中
    //第二个参数是模块实例名称，在lua中可以通过这个实例调用方法
    //第三个参数是C模块的入口方法
    luaL_requiref(L,"mytestlib",luaopen_mytestlib,1);
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
    lua_close(L);
}

int main()
{
    callLuaFunc3("src/lua/Demo3.lua");
    return 0;
}


