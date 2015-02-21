/**
 * blufs - a c++ luafilesystem library
 * --------------------------------------------------------
 * Copyright 2013-2015 Dmitry Ledentsov
 * [MIT License](http://opensource.org/licenses/MIT)
 *
 */

#include "blufs_lib.h"

#include <lua.hpp>
#include <iostream>

namespace {
    void init_blufs(lua_State* L) {
        register_blufs(L);
    }
}

extern "C" {
    void lufs_init(lua_State* L) {
        init_blufs(L);
    }
}
