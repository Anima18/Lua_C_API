#include "mytestlib.h"

//��ע���C�������ú�����������ʽ��������������Ѿ�������
//��Ҫ˵�����ǣ��ú���������C����ʽ�����������extern "C"�Ǳ���ġ�
//���������������ͬ�����ﲻ��׸����
static int add(lua_State* L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1 + op2);
    return 1;
}

static int sub(lua_State* L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1 - op2);
    return 1;
}

//luaL_Reg�ṹ��ĵ�һ���ֶ�Ϊ�ַ�������ע��ʱ����֪ͨLua�ú��������֡�
//��һ���ֶ�ΪC����ָ�롣
//�ṹ�������е����һ��Ԫ�ص������ֶξ�ΪNULL��������ʾLuaע�ắ���Ѿ����������ĩβ��
static luaL_Reg mytestlib[] = {
    {"add", add},
    {"sub", sub},
    {NULL, NULL}
};

//5.1��luaL_register������5.2�Ժ���luaL_newlib
//��C���Ψһ��ں������亯��ǩ����ͬ�������ע�ắ���������¼���˵����
//1. ���ǿ��Խ��ú����򵥵����Ϊģ��Ĺ���������
//2. �亯��������Ϊluaopen_xxx������xxx��ʾlibrary���ơ�Lua����require "xxx"��Ҫ��֮��Ӧ��
//3. ��luaL_register�ĵ����У����һ���ַ�������Ϊģ����"xxx"���ڶ�������Ϊ��ע�ắ�������顣
//4. ��Ҫǿ�����ǣ�������Ҫ�õ�"xxx"�Ĵ��룬����C����Lua�������뱣��һ�£�����Lua��Լ����
//   �����޷����á�
__declspec(dllexport)
int luaopen_mytestlib(lua_State* L)
{
    luaL_newlib(L, mytestlib);
     //luaL_register(L, "mytestlib", mytestlib);
    return 1;
}
