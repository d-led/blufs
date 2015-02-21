/**
 * blufs - a c++ luafilesystem library
 * --------------------------------------------------------
 * Copyright 2013-2015 Dmitry Ledentsov
 * [MIT License](http://opensource.org/licenses/MIT)
 *
 */

#include <lua.hpp>
#include <iostream>

#include "blufs_lib.h"

#ifdef _MSC_VER
#define BLUFS __declspec(dllexport)
#else
#define BLUFS
#endif

extern "C" BLUFS int luaopen_blufs (lua_State* L) {
	register_blufs(L);
	return 1;
}
