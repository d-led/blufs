/**
 * blufs - a c++ luafilesystem library
 * --------------------------------------------------------
 * Copyright 2013-2015 Dmitry Ledentsov
 * [MIT License](http://opensource.org/licenses/MIT)
 *
 */

#include "blufs_lib.h"
#include "resource.h"

#include <lua.hpp>
#include <iostream>

namespace {
    void init_blufs(lua_State* L) {
        register_blufs(L);
        luaL_dostring(L, blufs::Resource::compat().c_str());
        luaL_dostring(L, blufs::Resource::lualinq().c_str());
    }
}

extern "C" {
    void lufs_init(lua_State* L) {
        init_blufs(L);
    }
}
