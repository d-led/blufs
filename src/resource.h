#pragma once
/* This file has been generated using ris, do not modify! */

#include <string>

namespace blufs {
class Resource /*final*/ {
public:
    static std::string lualinq();
    static std::string compat();

public:
    typedef std::string(*ResourceGetter)();
public: // key/value api
template <typename TInserter>
static void GetKeys(TInserter inserter) {
    static const char* keys[] = {
        "lualinq",
        "compat",
    };
    for (auto key : keys) {
        inserter(key);
    }
}
public: // key/value api
    static std::string Get(std::string const& key);
public:
    static std::string OnNoKey(std::string const& key="") {
        return "";
    }
};
}
