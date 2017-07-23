#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "stackAction.h"

void stackDump(lua_State *L) {
    int i;
    int length = lua_gettop(L);
    for(i = 1; i <= length; i++) {
        int type = lua_type(L, i);
        switch(type) {
        case LUA_TSTRING:
            printf("%s", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;
        case LUA_TNUMBER:
            printf("%g", lua_tonumber(L, i));
            break;
        default:
            printf("%s", lua_typename(L, type));
            break;
        }

        printf(" ");
    }
    printf("\n");
}

void stackActiontest() {

    lua_State* L;
    L = luaL_newstate();

    lua_pushboolean(L, 1);
    lua_pushnumber(L, 10);
    lua_pushnil(L);
    lua_pushstring(L, "hello");
    stackDump(L);

    lua_pushvalue(L, -4);
    stackDump(L);

    lua_replace(L, 3);
    stackDump(L);


    lua_settop(L, 6);
    stackDump(L);

    lua_remove(L, -3);
    stackDump(L);

    lua_insert(L, -3);
    stackDump(L);

    lua_settop(L, -5);
    stackDump(L);

    lua_close(L);
    return 0;
}
