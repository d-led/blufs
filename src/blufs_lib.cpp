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
        bool exists() const { return fs::exists(me); }
        path absolute() const { return path(fs::absolute(me)); }
        path absolute_with_base(const path& base) { return path(fs::absolute(me,base.me)); }
        path absolute_with_base_s(const std::string & base) { return path(fs::absolute(me,base)); }
        path canonical() const { return path(fs::canonical(me)); }
        path canonical_with_base(const path& base) { return path(fs::canonical(me,base.me)); }
        path canonical_with_base_s(const std::string & base) { return path(fs::canonical(me,base)); }

        void make_preferred() { me.make_preferred(); }
        void clear() { me.clear(); }
        void remove_filename() { me.remove_filename(); }
        void replace_extension(path const& e) { me.replace_extension(e.me); }
        void replace_extension_s(std::string const& e) { me.replace_extension(e); }
    };

    static path get_current_path() { return path(fs::current_path()); }
    static void set_current_path(path const& p) { fs::current_path(p.me); }
    static void set_current_path_s(std::string const& p) { fs::current_path(p); }
    static path absolute(path const& p) { return path(fs::absolute(p.me)); }
    static path absolute_s(std::string const& p) { return path(fs::absolute(p)); }
    static path absolute_with_base(path const& p,const path& base) { return path(fs::absolute(p.me, base.me)); }
    static path absolute_with_base_s(std::string const& p,const std::string & base) { return path(fs::absolute(p, base)); }
    static path canonical(path const& p) { return path(fs::canonical(p.me)); }
    static path canonical_s(std::string const& p) { return path(fs::canonical(p)); }
    static path canonical_with_base(path const& p,const path& base) { return path(fs::canonical(p.me, base.me)); }
    static path canonical_with_base_s(std::string const& p,const std::string & base) { return path(fs::canonical(p, base)); }
    static bool create_directories(path const& p) { return fs::create_directories(p.me); }
    static bool create_directories_s(std::string const& p) { return fs::create_directories(fs::path(p)); }
    static bool create_directory(path const& p) { return fs::create_directory(p.me); }
    static bool create_directory_s(std::string const& p) { return fs::create_directory(fs::path(p)); }
    static void copy(path const& from, path const& to,int option) { fs::copy(from.me, to.me); }
    static void copy_s(std::string const& from, std::string const& to) { fs::copy(fs::path(from), fs::path(to)); }


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
            .property("exists", &blufs::path::exists)
            .def("clear", &blufs::path::clear)
            .def("make_preferred", &blufs::path::make_preferred)
            .def("remove_filename", &blufs::path::remove_filename)
            .def("replace_extension", &blufs::path::replace_extension)
            .def("replace_extension", &blufs::path::replace_extension_s)
            .def("compare", &blufs::path::compare_p)
            .def("compare", &blufs::path::compare_s)
            .def_readonly("parts", &blufs::path::get_parts, return_stl_iterator)

            .enum_("file_type")
            [
                value("status_error", fs::status_error),
                value("file_not_found", fs::file_not_found),
                value("regular_file", fs::regular_file),
                value("directory_file", fs::directory_file),
                value("symlink_file", fs::symlink_file),
                value("block_file", fs::block_file),
                value("character_file", fs::character_file),
                value("fifo_file", fs::fifo_file),
                value("socket_file", fs::socket_file),
                value("type_unknown", fs::type_unknown)
            ]

            .enum_("perms")
            [
                value("no_perms", fs::no_perms),
                value("owner_read", fs::owner_read),
                value("owner_write", fs::owner_write),
                value("owner_exe", fs::owner_exe),
                value("owner_all", fs::owner_all),
                value("group_read", fs::group_read),
                value("group_write", fs::group_write),
                value("group_exe", fs::group_exe),
                value("group_all", fs::group_all),
                value("others_read", fs::others_read),
                value("others_write", fs::others_write),
                value("others_exe", fs::others_exe),
                value("others_all", fs::others_all),
                value("all_all", fs::all_all),
                value("set_uid_on_exe", fs::set_uid_on_exe),
                value("set_gid_on_exe", fs::set_gid_on_exe),
                value("sticky_bit", fs::sticky_bit),
                value("perms_mask", fs::perms_mask),
                value("perms_not_known", fs::perms_not_known),
                value("add_perms", fs::add_perms),
                value("remove_perms", fs::remove_perms),
                value("symlink_perms", fs::symlink_perms)
            ]
        ,

        class_<fs::space_info>("space_info")
            .def_readwrite("capacity", &fs::space_info::capacity)
            .def_readwrite("free", &fs::space_info::free)
            .def_readwrite("available", &fs::space_info::available)
        ,

        class_<fs::copy_option>("copy_option")
            .enum_("values")
            [
                value("none",static_cast<int>(fs::copy_option::none)),
                value("fail_if_exists", static_cast<int>(fs::copy_option::fail_if_exists)),
                value("overwrite_if_exists", static_cast<int>(fs::copy_option::overwrite_if_exists))
            ]
        ,

        class_<fs::symlink_option>("symlink_option")
            .enum_("values")
            [
                value("none", static_cast<int>(fs::symlink_option::none)),
                value("no_recurse", static_cast<int>(fs::symlink_option::no_recurse)),
                value("recurse", static_cast<int>(fs::symlink_option::recurse))
            ]
        ,

        def("current_path", blufs::set_current_path),
        def("current_path", blufs::set_current_path_s),
        def("current_path", blufs::get_current_path),
        def("create_directories", blufs::create_directories),
        def("create_directories", blufs::create_directories_s),
        def("create_directory", blufs::create_directory),
        def("create_directory", blufs::create_directory_s),
        def("copy", blufs::copy),
        def("copy", blufs::copy_s),
        def("absolute", &blufs::absolute),
        def("absolute", &blufs::absolute_s),
        def("absolute", &blufs::absolute_with_base),
        def("absolute", &blufs::absolute_with_base_s),
        def("canonical", &blufs::canonical),
        def("canonical", &blufs::canonical_s),
        def("canonical", &blufs::canonical_with_base),
        def("canonical", &blufs::canonical_with_base_s)
    ];
}
