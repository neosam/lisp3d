#include "lua.h"
#include "elements.h"

lua_State *l;

int wrapper_objGetName(lua_State *l)
{
	int parameter = lua_gettop(l);
	int index = lua_tointeger(l, parameter);
	
	lua_pop(l, lua_gettop(l));
	lua_pushstring(l, objGetName(index));
	
	return 1;
}

int wrapper_quadGetRGB(lua_State *l)
{
	int parameter = lua_gettop(l);
	int index = lua_tointeger(l, parameter);
	double *rgb = quadGetRGB(index);
	
	lua_pop(l, lua_gettop(l));
	lua_pushnumber(l, rgb[0]);
	lua_pushnumber(l, rgb[1]);
	lua_pushnumber(l, rgb[2]);
	
	return 3;
}

int wrapper_quadSetRGB(lua_State *l)
{
	int parameter = lua_gettop(l);
	int index = lua_tointeger(l, 1);
	double r, g, b;
	
	r = lua_tonumber(l, 2);
	g = lua_tonumber(l, 3);
	b = lua_tonumber(l, 4);
	
	lua_pop(l, lua_gettop(l));
	
	quadSetRGB(index, r, g, b);
	
	return 0;
}

void initLua()
{
	l = lua_open();
	luaopen_base(l);
	lua_pushcfunction(l, wrapper_objGetName);
	lua_setglobal(l, "objGetName");
	lua_pushcfunction(l, wrapper_quadGetRGB);
	lua_setglobal(l, "quadGetRGB");
	lua_pushcfunction(l, wrapper_quadSetRGB);
	lua_setglobal(l, "quadSetRGB");
}

void execEvent(char *func, Object *obj)
{
	char *name = (obj->name == NULL)? "noname": obj->name;
	
	lua_getfield(l, LUA_GLOBALSINDEX, func);
	lua_pushinteger(l, obj->id);
	lua_call(l, 1, 0);
}
