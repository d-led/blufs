include 'premake'

lua = assert(dofile 'premake/recipes/lua.lua')
boost = assert(dofile 'premake/recipes/boost.lua')

make_solution 'blufs'

lua:set_includedirs()
lua:set_libdirs()
boost:set_includedirs()
boost:set_libdirs()
boost:set_defines()
defines { 'BOOST_NO_VARIADIC_TEMPLATES' }

includedirs {
	'./deps/luabind',
	'./deps/Catch/single_include',
	'./deps/LuaState/include'
}

local function platform_specifics()
	make_cpp11()
end

make_static_lib('luabind',{'./deps/luabind/src/*.cpp'})
platform_specifics()

make_shared_lib('blufs', {
	'blufs.cpp',
	'blufs_lib.cpp'
})
platform_specifics()
links { 'luabind' }
boost:set_links()
lua:set_links()

make_console_app('test_blufs',{ 'test.cpp' })
links {'luabind', 'blufs' }
boost:set_links()
lua:set_links()
platform_specifics()
run_target_after_build()
