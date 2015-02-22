include 'premake'

local function platform_specifics()
	use_standard 'c++0x'
	configuration 'linux'
		buildoptions '-fPIC'
	configuration '*'
end

local function link_additional_boost_libs()
	configuration 'linux'
	links { 'boost_system', 'boost_filesystem', 'dl', 'pthread', 'readline' }
	-- buildoptions '-Wl,-E'
	configuration 'macosx'
		links 'boost_filesystem'
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
		generate_build = function(self)
			local lualib_build = make_shared_lib
			-- if os.get() == 'windows' then
			-- 	lualib_build = make_shared_lib
			-- end
			lualib_build('lua5.3',{
				path.join(lua_dir,'src','*.h'),
				path.join(lua_dir,'src','*.c')
			})
			language 'C'
			excludes { 
				path.join(lua_dir,'src','lua.c'),
				path.join(lua_dir,'src','luac.c')
			}
			configuration 'windows'
				defines 'LUA_BUILD_AS_DLL'
			configuration 'linux'
				defines 'LUA_USE_LINUX'
			configuration 'macosx'
				defines 'LUA_USE_MACOSX'
				targetextension '.so'
		 	configuration '*'
		 	targetprefix ''
		end
	}
end

boost = assert(dofile 'premake/recipes/boost.lua')

--== SOLUTION ==-----
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
lua:generate_build()

-----------------LUABIND-------------------------------
make_static_lib('luabind',{'./deps/luabind/src/*.cpp'})
platform_specifics()

-----------------BLUFS----
make_shared_lib('blufs', {
	'src/blufs.cpp',
	'src/blufs_lib.cpp'
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

make_static_lib('custom_lua',{'src/customizable_lua.c'})

------------------LUFS---
make_console_app('lufs',{
	'src/blufs_lib.cpp',
	'src/lufs_init.cpp',
	'src/resource.h',
	'src/resource.cpp',
	'src/resources.json'
})
boost:set_links()
links {
	'luabind',
	'custom_lua'
}
lua:set_links()
link_additional_boost_libs()
platform_specifics()

------------------TEST---------------------------
make_console_app('test_blufs',{ 'src/test.cpp' })
lua:set_links()
links {'luabind' } --, 'blufs'
defines 'LUA_COMPAT_APIINTCASTS'
boost:set_links()
platform_specifics()
run_target_after_build()
link_additional_boost_libs()


newaction {
   trigger     = "res",
   description = "compile the resources",
   execute     = function ()
	   	local function exec(command)
		    local handle = io.popen(command)
		    local result = handle:read("*a")
		    handle:close()
		    print(result)
		    return result
		end
        local ok = false
        local uname = os.get()
        if uname == 'windows' or uname:find'mingw' then
            exec[[ris\ris src\resources.json]]
        elseif uname == 'macosx' or uname == 'darwin' then
            exec[[ris/ris.osx src/resources.json]]
        elseif uname == 'linux' then
            exec[[ris/ris src/resources.json]]
        end
   end
}
