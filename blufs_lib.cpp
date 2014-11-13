/**
 * blufs - a c++ luafilesystem library
 * --------------------------------------------------------
 * Copyright (C) 2013-2014, by Dmitry Ledentsov (d.ledentsov@gmail.com)
 *
 * This software is distributed under the MIT License. See notice at the end
 * of this file.
 *
 */

#include "blufs_lib.h"

#include <boost/filesystem.hpp>
#include <boost/interprocess/sync/file_lock.hpp>

#include <lua.hpp>

#include <luabind/luabind.hpp>
#include <string>
#include <stdexcept>
#include <iostream>

namespace blufs {
    namespace fs=boost::filesystem;
}

namespace luabind
{
    namespace fs = boost::filesystem;

    template <>
    struct default_converter<fs::path>
        : native_converter_base<fs::path>
    {
        static int compute_score(lua_State* L, int index)
        {
            return lua_type(L, index) == LUA_TSTRING ? 0 : -1;
        }

        fs::path from(lua_State* L, int index)
        {
            return fs::path(lua_tostring(L, index));
        }

        void to(lua_State* L, fs::path const& x)
        {
            lua_pushstring(L, x.generic_string().c_str());
        }
    };

    template <>
    struct default_converter<fs::path const&>
        : default_converter<fs::path>
    {};
}

void register_blufs (lua_State* L) {
    using namespace luabind;
    using namespace blufs;

    open(L);

    module(L, "blufs")
    [
        class_<fs::path>("path")
            .def(constructor<std::string const&>())
        ,
        def("current_path", ((void(*)(fs::path const&))fs::current_path)),
        def("current_path", ((fs::path(*)())fs::current_path))
    ];
}

/**
 * Copyright (c) 2013-2014 Dmitry Ledentsov
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
