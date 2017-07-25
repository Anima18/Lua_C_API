#include <stdio.h>
#include <string.h>
#include "include/lua.h"
#include "include/lualib.h"
#include "include/lauxlib.h"

//��Lua���õ�Cע�ắ����
static int add2(lua_State* L)
{
    //���ջ�еĲ����Ƿ�Ϸ���1��ʾLua����ʱ�ĵ�һ������(������)���������ơ�
    //���Lua�����ڵ���ʱ���ݵĲ�����Ϊnumber���ú�����������ֹ�����ִ�С�
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    //�������Ľ��ѹ��ջ�С�����ж������ֵ��������������ѹ��ջ�С�
    lua_pushnumber(L,op1 + op2);
    //����ֵ������ʾ��C�����ķ���ֵ��������ѹ��ջ�еķ���ֵ������
    return 1;
}

//��һ����Lua���õ�Cע�ắ����
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
    //��ָ���ĺ���ע��ΪLua��ȫ�ֺ������������е�һ���ַ�������ΪLua����
    //�ڵ���C����ʱʹ�õ�ȫ�ֺ��������ڶ�������Ϊʵ��C������ָ�롣
    lua_register(L, "add2", add2);
    lua_register(L, "sub2", sub2);

    callLuaFunc2(L, "src/lua/Demo2.lua");
    lua_close(L);
}
