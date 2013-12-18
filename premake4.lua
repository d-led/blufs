_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

make_solution 'blufs'

make_shared_lib('blufs', {
	'blufs.cpp',
	'blufs_lib.cpp'
})

targetdir '.'

make_cpp11()

