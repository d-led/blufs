_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

make_solution 'blufs'

local OS = os.get()
local settings = {
	links = {
		linux = { 'lua' },
		windows = { 'lua5.1' },
		macosx = { 'lua' }
	}
}

includedirs {
	'./luabind'
}

local function platform_specifics()
	-- platform specific --
	configuration 'macosx'
		targetprefix ''
		targetextension '.so'
	configuration 'windows'
		includedirs { [[C:\Users\Public\lua\LuaRocks\2.1\include]] , os.getenv 'BOOST' }
		libdirs { [[C:\Users\Public\lua\LuaRocks\2.1]] , path.join(os.getenv'BOOST',[[stage\lib]]) }
	configuration 'linux'
		targetprefix ''
		includedirs { [[/usr/include/lua5.1]] }
	configuration { '*' }
end

defines { 'BOOST_NO_VARIADIC_TEMPLATES' }

make_static_lib('luabind',{'./luabind/src/*.cpp'})

make_shared_lib('blufs', {
	'blufs.cpp',
	'blufs_lib.cpp'
})

links { 'luabind' , settings.links[OS] }

platform_specifics()