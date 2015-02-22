/**
 * blufs - a c++ luafilesystem library
 * --------------------------------------------------------
 * Copyright 2013-2015 Dmitry Ledentsov
 * [MIT License](http://opensource.org/licenses/MIT)
 *
 */

#include "blufs_lib.h"

#include <boost/filesystem.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/shared_ptr.hpp>

#include <lua.hpp>

#include <luabind/luabind.hpp>
#include <luabind/tag_function.hpp>
#include <luabind/operator.hpp>
#include <luabind/copy_policy.hpp>
#include <luabind/iterator_policy.hpp>
#include <boost/container/vector.hpp>
#include <string>
#include <stdexcept>
#include <iostream>

namespace blufs = boost::filesystem;

std::ostream& operator<<(std::ostream& s, blufs::path const& p) {
    return s << p.generic_string();
}

blufs::path const& itself(blufs::path const& self) { return self; }
blufs::path absolute_d(blufs::path const& self) { return blufs::absolute(self); }
blufs::path canonical_d(blufs::path const& self) { return blufs::canonical(self); }
void current_path_s(std::string const& p) { blufs::current_path(p); }

void register_blufs (lua_State* L) {
    using namespace luabind;
    using namespace blufs;

    open(L);

    module(L, "blufs")
    [
        class_<path, boost::shared_ptr<path>>("path")
            .def(constructor<std::string const&>())
            .def(constructor<>())
            .def(constructor<path const&>())
            .def(tostring(self))
            //.def(const_self + path())
            .def(const_self / path())
            //.def(const_self + std::string())
            .def(const_self / std::string())
            .property("generic_string", (std::string(path::*)()const) &path::generic_string)
            .property("root_path", &path::root_path)
            .property("root_name", &path::root_name)
            .property("root_directory", &path::root_directory)
            .property("relative_path", &path::relative_path)
            .property("parent_path", &path::parent_path)
            .property("filename", &path::filename)
            .property("stem", &path::stem)
            .property("extension", &path::extension)
            .property("empty", &path::empty)
            .property("exists", (bool(*)(path const&))exists)
            .property("absolute",absolute_d)
            .property("canonical", canonical_d)
            .def("parts", itself, copy(result) + return_stl_iterator)
            .def("absolute_to", (path(*)(path const&, path const&))absolute)
            .def("canonical_to", (path(*)(path const&, path const&))canonical)
            .def("clear", &path::clear)
            .def("make_preferred", &path::make_preferred)
            .def("remove_filename", &path::remove_filename)
            .def("replace_extension", &path::replace_extension)
            .def("compare", (int(path::*)(std::string const&)const) &path::compare)
            .def("compare", (int(path::*)(path const&)const) &path::compare)

            .enum_("file_type")
            [
                value("status_error", blufs::status_error),
                value("file_not_found", blufs::file_not_found),
                value("regular_file", blufs::regular_file),
                value("directory_file", blufs::directory_file),
                value("symlink_file", blufs::symlink_file),
                value("block_file", blufs::block_file),
                value("character_file", blufs::character_file),
                value("fifo_file", blufs::fifo_file),
                value("socket_file", blufs::socket_file),
                value("type_unknown", blufs::type_unknown)
            ]

            .enum_("perms")
            [
                value("no_perms", blufs::no_perms),
                value("owner_read", blufs::owner_read),
                value("owner_write", blufs::owner_write),
                value("owner_exe", blufs::owner_exe),
                value("owner_all", blufs::owner_all),
                value("group_read", blufs::group_read),
                value("group_write", blufs::group_write),
                value("group_exe", blufs::group_exe),
                value("group_all", blufs::group_all),
                value("others_read", blufs::others_read),
                value("others_write", blufs::others_write),
                value("others_exe", blufs::others_exe),
                value("others_all", blufs::others_all),
                value("all_all", blufs::all_all),
                value("set_uid_on_exe", blufs::set_uid_on_exe),
                value("set_gid_on_exe", blufs::set_gid_on_exe),
                value("sticky_bit", blufs::sticky_bit),
                value("perms_mask", blufs::perms_mask),
                value("perms_not_known", blufs::perms_not_known),
                value("add_perms", blufs::add_perms),
                value("remove_perms", blufs::remove_perms),
                value("symlink_perms", blufs::symlink_perms)
            ]
        ,

        class_<blufs::space_info>("space_info")
            .def_readwrite("capacity", &blufs::space_info::capacity)
            .def_readwrite("free", &blufs::space_info::free)
            .def_readwrite("available", &blufs::space_info::available)
        ,

        class_<blufs::copy_option>("copy_option")
            .enum_("values")
            [
                value("none", static_cast<int>(blufs::copy_option::none)),
                value("fail_if_exists", static_cast<int>(blufs::copy_option::fail_if_exists)),
                value("overwrite_if_exists", static_cast<int>(blufs::copy_option::overwrite_if_exists))
            ]
        ,

        class_<blufs::symlink_option>("symlink_option")
            .enum_("values")
            [
                value("none", static_cast<int>(blufs::symlink_option::none)),
                value("no_recurse", static_cast<int>(blufs::symlink_option::no_recurse)),
                value("recurse", static_cast<int>(blufs::symlink_option::recurse))
            ]
        ,

        def("current_path", (blufs::path(*)()) blufs::current_path),
        def("current_path", (void(*)(blufs::path const&)) blufs::current_path),
        def("current_path", current_path_s ),
        def("create_directories", (bool(*)(blufs::path const&)) blufs::create_directories),
        // def("create_directories", fs::create_directories_s),
        def("create_directory", (bool(*)(blufs::path const&)) blufs::create_directory),
        // def("create_directory", fs::create_directory_s),
        def("copy", (void(*)(blufs::path const&,blufs::path const&)) blufs::copy)
        // def("copy", fs::copy_s),
    ];
}
