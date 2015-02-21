include 'premake'

local function platform_specifics()
	use_standard 'c++0x'
	configuration 'linux'
		buildoptions '-fPIC'
	configuration '*'
end

function get_local_lua()
	local lua_dir = './deps/lua/lua-5.3.0'
	
	return {
		set_includedirs = function()
			includedirs( path.join(lua_dir,'src') )
		end,
		set_libdirs = function() end,
		set_links = function()
			links 'lua5.3'
		end,
		generate_build = function()
			make_shared_lib('lua5.3',{
				path.join(lua_dir,'src','lapi.c'),
				path.join(lua_dir,'src','lcode.c'),
				path.join(lua_dir,'src','lctype.c'),
				path.join(lua_dir,'src','ldebug.c'),
				path.join(lua_dir,'src','ldo.c'),
				path.join(lua_dir,'src','ldump.c'),
				path.join(lua_dir,'src','lfunc.c'),
				path.join(lua_dir,'src','lgc.c'),
				path.join(lua_dir,'src','llex.c'),
				path.join(lua_dir,'src','lmem.c'),
				path.join(lua_dir,'src','lobject.c'),
				path.join(lua_dir,'src','lopcodes.c'),
				path.join(lua_dir,'src','lparser.c'),
				path.join(lua_dir,'src','lstate.c'),
				path.join(lua_dir,'src','lstring.c'),
				path.join(lua_dir,'src','ltable.c'),
				path.join(lua_dir,'src','ltm.c'),
				path.join(lua_dir,'src','lundump.c'),
				path.join(lua_dir,'src','lvm.c'),
				path.join(lua_dir,'src','lzio.c'),
				path.join(lua_dir,'src','lauxlib.c'),
				path.join(lua_dir,'src','lbaselib.c'),
				path.join(lua_dir,'src','lbitlib.c'),
				path.join(lua_dir,'src','lcorolib.c'),
				path.join(lua_dir,'src','ldblib.c'),
				path.join(lua_dir,'src','liolib.c'),
				path.join(lua_dir,'src','lmathlib.c'),
				path.join(lua_dir,'src','loslib.c'),
				path.join(lua_dir,'src','lstrlib.c'),
				path.join(lua_dir,'src','ltablib.c'),
				path.join(lua_dir,'src','lutf8lib.c'),
				path.join(lua_dir,'src','loadlib.c'),
				path.join(lua_dir,'src','linit.c')
			})
			configuration 'windows'
				defines 'LUA_BUILD_AS_DLL'
			configuration 'macosx'
				targetextension '.so'
		 	configuration '*'
		 	targetprefix ''

			make_console_app('lufs',{
				path.join(lua_dir,'src','lua.c')
			})
			links 'lua5.3'
		end
	}
end

boost = assert(dofile 'premake/recipes/boost.lua')

---- SOLUTION -------
make_solution 'blufs'

local local_lua = true

platforms 'native'

boost:set_includedirs()
boost:set_libdirs()
boost:set_defines()
defines { 'BOOST_NO_VARIADIC_TEMPLATES' }

includedirs {
	'./deps/luabind',
	'./deps/Catch/single_include',
	'./deps/LuaState/include'
}

if local_lua then
	lua = get_local_lua()
else
	lua = assert(dofile 'premake/recipes/lua.lua')
	lua.generate_build = function() end
end
lua:set_includedirs()
lua:set_libdirs()
lua.generate_build()

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
configuration '*'
boost:set_links()
lua:set_links()




make_console_app('test_blufs',{ 'test.cpp' })
links {'luabind', 'blufs' }
defines 'LUA_COMPAT_APIINTCASTS'
boost:set_links()
lua:set_links()
platform_specifics()
run_target_after_build()

configuration 'linux'
	links { 'boost_filesystem', 'dl', 'pthread' }
configuration 'macosx'
	links 'boost_filesystem'
configuration '*'
