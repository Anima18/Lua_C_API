#include <stdio.h>
#include "include/lua.h"
#include "include/lualib.h"
#include "include/lauxlib.h"
#include "stackAction.h"

#define MAX_COLOR 255
#define LUA_DEMO1_FILE "src/lua/Demo1.lua"

extern int getField(lua_State *L, const char *key);
extern void setField(lua_State *L, const char *key, int value);

void loadLuaFile(lua_State *L, const char*fname, int *w, int *h) {
    if(luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
        //error(L, "cannot run file:%s", lua_tostring(L, -1));
        printf("cannot run file:%s", lua_tostring(L, -1));
    }else {
        lua_getglobal(L, "width");
        lua_getglobal(L, "height");
        if(!lua_isnumber(L, -2)) {
            //error(L, "width should be a number\n");
            printf("width should be a number");
        }
        if(!lua_isnumber(L, -1)) {
            //error(L, "height should be a number\n");
            printf("height should be a number\n");
        }
        *w = lua_tonumber(L, -2);
        *h = lua_tonumber(L, -1);
    }
}

void getTableValue(lua_State *L, const char*fname) {
    if(luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
        printf("cannot run file:%s", lua_tostring(L, -1));
    }else {
        lua_getglobal(L, "background");
        if(!lua_istable(L, -1)) {
            printf("background should be a table");
        }else {
            int red = getField(L, "r");
            int blue = getField(L, "b");
            int green = getField(L, "g");
            printf("background color is (%d, %d, %d) \n", red, green, blue);
        }
    }
}

void setTableValue(lua_State *L, const char*fname, int red, int green, int blue) {
    if(luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
        printf("cannot run file:%s", lua_tostring(L, -1));
    }else {
        lua_getglobal(L, "background");
        if(!lua_istable(L, -1)) {
            printf("background should be a table");
        }else {
            setField(L, "r", red);
            setField(L, "g", green);
            setField(L, "b", blue);
        }
    }
}

int getField(lua_State *L, const char *key) {
    int result;

    /**
    * lua_gettable函数会从栈顶取得一个值，然后根据这个值去table中寻找对应的值，最后把找到的值放到栈顶。
    * lua_gettable的第二个参数是指定的table变量在栈中的索引
    */
    //lua_pushstring(L, key);
    //lua_gettable(L, -2);

    //lua5.1提供简便方法
    lua_getfield(L, -1, key);

    if(!lua_isnumber(L, -1)) {
        printf("invalid component in background color");
        return -1;
    }else {
        result = (lua_tonumber(L, -1) * MAX_COLOR);
        lua_pop(L, 1);
        return result;
    }
}

void setField(lua_State *L, const char *key, int value) {
    /**
    lua_pushstring(L, key);
    lua_pushnumber(L, (double)value/MAX_COLOR);
    lua_settable(L, -3);
    **/
    //另一种方法
    lua_pushnumber(L, (double)value/MAX_COLOR);
    lua_setfield(L, -2, key);
}

void callLuaFunc(lua_State *L, const char*fname) {
    if(luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0)) {
        printf("cannot run file:%s", lua_tostring(L, -1));
    }else {
        int x = 10, y = 5;
        lua_getglobal(L, "add");
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        if(lua_pcall(L, 2, 1, 0) != 0) {
            printf("error running function 'add' is %s", lua_tostring(L, -1));
        }else {
            if(!lua_isnumber(L, -1)) {
                printf("function 'add' return should be a number");
            }else {
                printf("function 'add(%d, %d)' return is %s", x, y, lua_tostring(L, -1));
                lua_pop(L, 1);
            }
        }
    }
}

void loadFileTest() {
    int w = 0;
    int h = 0;
    lua_State *L = luaL_newstate();
    loadLuaFile(L, LUA_DEMO1_FILE, &w, &h);
    printf("width:%d, height:%d", w, h);
    lua_close(L);
}

void tableActionTest() {
    lua_State *L = luaL_newstate();
    getTableValue(L, LUA_DEMO1_FILE);
    setTableValue(L, LUA_DEMO1_FILE, 100, 200, 50);

    lua_getglobal(L, "background");
    if(!lua_istable(L, -1)) {
        printf("background should be a table");
    }else {
        int red = getField(L, "r");
        int blue = getField(L, "b");
        int green = getField(L, "g");
        printf("background color is (%d, %d, %d) \n", red, green, blue);
    }
    lua_close(L);
}

void callFucTest() {
    lua_State *L = luaL_newstate();
    callLuaFunc(L, LUA_DEMO1_FILE);
    lua_close(L);
}

void cluaTest() {
    callFucTest();
}
