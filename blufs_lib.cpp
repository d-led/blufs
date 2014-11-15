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
#include <boost/container/vector.hpp>
#include <string>
#include <stdexcept>
#include <iostream>

namespace fs = boost::filesystem;

namespace blufs {

    struct path {
        fs::path me;
        boost::container::vector<path> parts;
        void update_parts() {
            parts.clear();
            for (auto& x : me)
                parts.push_back(path(x));
        }
        
        boost::container::vector<path> const& get_parts() {
            update_parts();
            return parts;
        }

        explicit path(std::string const& p) : me(p) { }
        path() {}
        path(path const& other) : me(other.me) {  }
        explicit path(fs::path const& other) : me(other) {  }
        std::string generic_string() const { return me.generic_string(); }
        path operator+ (std::string const& other) const { fs::path res(me); res += other; return path(res); }
        path operator+ (path const& other) const { fs::path res(me); res += other.me; return path(res); }
        path operator/ (std::string const& other) const { fs::path res(me); res /= other; return path(res); }
        path operator/ (path const& other) const { fs::path res(me); res /= other.me; return path(res); }
        int compare_p(path const& other) const { return me.compare(other.me); }
        int compare_s(std::string const& other) const { return me.compare(other); }
        path root_path() const { return path(me.root_path()); }
        path root_name() const { return path(me.root_name()); }
        path root_directory() const { return path(me.root_directory()); }
        path relative_path() const { return path(me.relative_path()); }
        path parent_path() const { return path(me.parent_path()); }
        path filename() const { return path(me.filename()); }
        path stem() const { return path(me.stem()); }
        path extension() const { return path(me.extension()); }
        bool empty() const { return me.empty(); }
        void make_preferred() { me.make_preferred(); }
        void clear() { me.clear(); }
        void remove_filename() { me.remove_filename(); }
        void replace_extension(path const& e) { me.replace_extension(e.me); }
        void replace_extension_s(std::string const& e) { me.replace_extension(e); }
    };

    static path get_current_path() { return path(fs::current_path()); }
    static void set_current_path(path const& p) { fs::current_path(p.me); }
    static void set_current_path_s(std::string const& p) { fs::current_path(p); }

    std::ostream& operator<<(std::ostream& s, path const& p) {
        return s << p.generic_string();
    }
}

void register_blufs (lua_State* L) {
    using namespace luabind;

    open(L);

    module(L, "blufs")
    [
        class_<blufs::path>("path")
            .def(constructor<std::string const&>())
            .def(constructor<>())
            .def(constructor<blufs::path const&>())
            .def(tostring(self))
            .def(self + blufs::path())
            .def(self / blufs::path())
            .def(self + std::string())
            .def(self / std::string())
            .property("generic_string", &blufs::path::generic_string)
            .property("root_path", &blufs::path::root_path)
            .property("root_name", &blufs::path::root_name)
            .property("root_directory", &blufs::path::root_directory)
            .property("relative_path", &blufs::path::relative_path)
            .property("parent_path", &blufs::path::parent_path)
            .property("filename", &blufs::path::filename)
            .property("stem", &blufs::path::stem)
            .property("extension", &blufs::path::extension)
            .property("empty", &blufs::path::empty)
            .def("clear", &blufs::path::clear)
            .def("make_preferred", &blufs::path::make_preferred)
            .def("remove_filename", &blufs::path::remove_filename)
            .def("replace_extension", &blufs::path::replace_extension)
            .def("replace_extension", &blufs::path::replace_extension_s)
            .def("compare", &blufs::path::compare_p)
            .def("compare", &blufs::path::compare_s)
            .def_readonly("parts", &blufs::path::get_parts, return_stl_iterator)
        ,

        def("current_path", blufs::set_current_path),
        def("current_path", blufs::set_current_path_s),
        def("current_path", blufs::get_current_path)
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
