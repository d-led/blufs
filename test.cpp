#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <LuaState.h>

class LuaTest {
protected:
    lua::State state;
public:
    LuaTest() {
        REQUIRE_NOTHROW(state.doString("require 'blufs'"));
    }
};

TEST_CASE_METHOD(LuaTest,"loading the library") {
    REQUIRE(state["blufs"].is<lua::Table>());
}
