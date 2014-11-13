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
        auto cpath =
            std::string("package.cpath=[[")
            + (current_path() / path("?.dll")).generic_string() + ";"
            + (current_path() / path("?.so")).generic_string() + ";"
            + "]] ..package.cpath";
        state.doString(cpath);

        std::cerr<<cpath<<std::endl;

        REQUIRE_NOTHROW(state.doString("require 'blufs'"));

        create_directories(exec_path);
        REQUIRE(exists(exec_path));
        current_path(exec_path);
    }

    ~LuaTest() {
        current_path(current_path().parent_path());
        remove_all(exec_path);
    }
};

TEST_CASE_METHOD(LuaTest, "loading the library") {
    REQUIRE(state["blufs"].is<lua::Table>());
}
