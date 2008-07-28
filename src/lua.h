#ifndef LUA2_H
#define LUA2_H

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include "elements.h"

extern lua_State* l;

void initLua();

void execEvent(char *func, Object *obj);

#endif
