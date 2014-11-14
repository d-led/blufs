#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <LuaState.h>

#include <boost/filesystem.hpp>
#include <luabind/luabind.hpp>

using namespace boost::filesystem;

class LuaTest {
protected:
    lua::State state;
    path exec_path;
public:
    LuaTest() :
        exec_path(absolute(unique_path()))
    {
        add_lua_cpath();
        load_library_under_test();
        set_up_isolated_test_folder();
    }

    ~LuaTest() {
        clean_up_test_folder();
    }
public:
    void debug(std::string expression) {
        state.doString(std::string("print(") + expression + ")");
    }
private:
    void add_lua_cpath() {
        auto cpath =
            std::string("package.cpath=[[")
            + (current_path() / path("?.dll")).generic_string() + ";"
            + (current_path() / path("?.so")).generic_string() + ";"
            + "]] ..package.cpath";
        state.doString(cpath);
    }

    void load_library_under_test() {
        REQUIRE_NOTHROW(state.doString("require 'blufs'"));
    }

    void set_up_isolated_test_folder() {
        create_directories(exec_path);
        REQUIRE(exists(exec_path));
        current_path(exec_path);
    }

    void clean_up_test_folder() {
        try {
            current_path(exec_path.parent_path());
            remove_all(exec_path);
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

TEST_CASE_METHOD(LuaTest, "loading the library") {
    REQUIRE(state["blufs"].is<lua::Table>());
}

namespace {
    struct my_exception
    {};

    void throwing_function() {
        throw my_exception();
    }
}

TEST_CASE_METHOD(LuaTest, "throwing inside bound functions is allowed") {
    auto L = state.getState();
    luabind::module(L)
    [
        luabind::def("throwing_function", throwing_function)
    ];

    CHECK_THROWS_AS(state.doString("throwing_function()"), lua::RuntimeError);
}

TEST_CASE_METHOD(LuaTest, "changing and querying current directory") {
    std::string res = state["blufs"]["current_path"]();
    CHECK(res == current_path().generic_string());

    state.doString("blufs.current_path('..')");
    std::string parent_dir = state["blufs"]["current_path"]();
    CHECK(absolute(current_path()) == absolute(parent_dir));
    CHECK(absolute(current_path()) != absolute(res));
}

TEST_CASE_METHOD(LuaTest, "path construction and conversion") {
    SECTION("construct from string and path") {
        CHECK_NOTHROW(state.doString("blufs.path'.'"));
        CHECK_NOTHROW(state.doString("assert(blufs.path('.').generic_string == '.')"));
        CHECK_NOTHROW(state.doString("assert(blufs.path(blufs.path('.')).generic_string == '.')"));
    }

    SECTION("empty constructor") {
        CHECK_NOTHROW(state.doString("blufs.path()"));
        CHECK_NOTHROW(state.doString("assert(blufs.path().empty)"));
        CHECK_NOTHROW(state.doString("assert(not blufs.path('.').empty)"));
    }

    CHECK_NOTHROW(state.doString("assert(tostring(blufs.path('.')) == '\".\"')"));
}

TEST_CASE_METHOD(LuaTest, "concatenation and appends") {
    CHECK_NOTHROW(state.doString("assert((blufs.path('.')+blufs.path('a')).generic_string=='.a')"));
    CHECK_NOTHROW(state.doString("assert((blufs.path('.')/blufs.path('a')).generic_string=='./a')"));
}