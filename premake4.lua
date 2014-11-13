_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

make_solution 'blufs'

local OS = os.get()
local settings = {
	links = {
		linux = { 'lua' },
		windows = { 'lua5.1' },
		macosx = { 'lua', 'boost_system', 'boost_filesystem' }
	}
}

includedirs {
	'./luabind',
	'./Catch/single_include',
	'./LuaState/include'
}

local function platform_specifics()
	-- platform specific --
	configuration 'macosx'
		targetprefix ''
		targetextension '.so'
	configuration 'windows'
		includedirs { [[C:\luarocks\2.1\include]] , os.getenv 'BOOST' }
		libdirs { [[C:\luarocks\2.1]] , path.join(os.getenv'BOOST',[[lib32-msvc-12.0]]) }
	configuration 'linux'
		targetprefix ''
		includedirs { [[/usr/include/lua5.1]] }
	configuration { '*' }
end

defines { 'BOOST_NO_VARIADIC_TEMPLATES' }

make_static_lib('luabind',{'./luabind/src/*.cpp'})
platform_specifics()

make_shared_lib('blufs', {
	'blufs.cpp',
	'blufs_lib.cpp'
})
platform_specifics()

links { 'luabind' , settings.links[OS] }

make_console_app('test_blufs',{ 'test.cpp' })
links {'luabind','blufs'}
make_cpp11()
run_target_after_build()

targetdir '.'

