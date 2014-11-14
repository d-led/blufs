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
#include <luabind/tag_function.hpp>
#include <luabind/operator.hpp>
#include <luabind/iterator_policy.hpp>
#include <string>
#include <stdexcept>
#include <iostream>

namespace fs = boost::filesystem;

namespace blufs {
    struct path : public fs::path {
        path(std::string const& _) : fs::path(_){}
        path() {}
        path(path const& other) : fs::path(other) {}
        std::string get_generic_string() const { return this->generic_string(); }
        path operator+ (path const& other) { auto res = path(*this); res += other; return res; }
        path operator/ (path const& other) { auto res = path(*this); res /= other; return res; }
        int compare_p(path const& other) const { return this->compare(other); }
        int compare_s(std::string const& other) const { return this->compare(other); }
        path root_path_() const { return from(this->root_path()); }
        path root_name_() const { return from(this->root_name()); }
        path root_directory_() const { return from(this->root_directory()); }
        path relative_path_() const { return from(this->relative_path()); }
        path parent_path_() const { return from(this->parent_path()); }
        path filename_() const { return from(this->filename()); }
        path stem_() const { return from(this->stem()); }
        path extension_() const { return from(this->extension()); }

        static path from(fs::path const& other) {
            path p;
            (fs::path&)(p) = other;
            return p;
        }
    };
}



namespace luabind
{
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

    open(L);

    module(L, "blufs")
    [
        class_<fs::path>("boost_path")
            .def(tostring(self))
        ,

        class_<blufs::path, fs::path>("path")
            .def(constructor<std::string const&>())
            .def(constructor<>())
            .def(constructor<blufs::path const&>())
            .def(tostring(self))
            .def(self + blufs::path())
            .def(self / blufs::path())
            .def(self + std::string())
            .def(self / std::string())
            .property("generic_string", &blufs::path::get_generic_string)
            .property("root_path", &blufs::path::root_path_)
            .property("root_name", &blufs::path::root_name_)
            .property("root_directory", &blufs::path::root_directory_)
            .property("relative_path", &blufs::path::relative_path_)
            .property("parent_path", &blufs::path::parent_path_)
            .property("filename", &blufs::path::filename_)
            .property("stem", &blufs::path::stem_)
            .property("extension", &blufs::path::extension_)
            .property("empty", &blufs::path::empty)
            .def("clear", &blufs::path::clear)
            .def("make_preferred", &blufs::path::clear)
            .def("remove_filename", &blufs::path::remove_filename)
            .def("replace_extension", &blufs::path::replace_extension)
            .def("compare", &blufs::path::compare_p)
            .def("compare", &blufs::path::compare_s)
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
