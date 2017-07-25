#ifndef STACKACTION_H_INCLUDED
#define STACKACTION_H_INCLUDED

#include "include/lua.h"
#include "include/lualib.h"
#include "include/lauxlib.h"

__declspec(dllexport) int luaopen_mytestlib(lua_State* L);

#endif // STACKACTION_H_INCLUDED
