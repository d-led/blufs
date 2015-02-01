include 'premake'

lua = assert(dofile 'premake/recipes/lua.lua')
boost = assert(dofile 'premake/recipes/boost.lua')

make_solution 'blufs'

platforms 'native'

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
links { 'luabind' }
platform_specifics()

configuration 'linux'
	links { 'boost_filesystem', 'dl', 'pthread' }
	targetprefix ''
configuration 'macosx'
	links 'boost_filesystem'
	targetprefix ''
	targetextension '.so'
configurations '*'
boost:set_links()
lua:set_links()




make_console_app('test_blufs',{ 'test.cpp' })
links {'luabind', 'blufs' }
boost:set_links()
lua:set_links()
platform_specifics()
run_target_after_build()

configuration 'linux'
	links { 'boost_filesystem', 'dl', 'pthread' }
configuration 'macosx'
	links 'boost_filesystem'
configurations '*'
