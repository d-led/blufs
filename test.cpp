#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <LuaState.h>

#include <boost/filesystem.hpp>

using namespace boost::filesystem;

class LuaTest {
protected:
    lua::State state;
    path exec_path;
public:
    LuaTest() :
        exec_path(unique_path())
    {
        add_lua_cpath();
        load_library_under_test();
        set_up_isolated_test_folder();
    }

    ~LuaTest() {
        clean_up_test_folder();
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
            current_path(current_path().parent_path());
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
