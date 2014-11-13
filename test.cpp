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
        REQUIRE_NOTHROW(state.doString("require 'blufs'"));
        create_directories(exec_path);
        REQUIRE(exists(exec_path));
        current_path(exec_path);
    }

    ~LuaTest() {
        remove_all(exec_path);
    }
};

TEST_CASE_METHOD(LuaTest,"loading the library") {
    REQUIRE(state["blufs"].is<lua::Table>());
}
