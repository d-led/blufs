# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug32
endif

ifndef verbose
  SILENT = @
endif

CC = gcc
CXX = g++
AR = ar

ifndef RESCOMP
  ifdef WINDRES
    RESCOMP = $(WINDRES)
  else
    RESCOMP = windres
  endif
endif

ifeq ($(config),debug32)
  OBJDIR     = ../../../obj/linux/gmake/x32/Debug/blufs/x32
  TARGETDIR  = ../../../bin/linux/gmake/x32/Debug
  TARGET     = $(TARGETDIR)/blufs.so
  DEFINES   += -DBOOST_NO_VARIADIC_TEMPLATES -DDEBUG -D_DEBUG
  INCLUDES  += -I../../../deps/luabind -I../../../deps/Catch/single_include -I../../../deps/LuaState/include -I../../../deps/lua/lua-5.3.0/src
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -m32 -fPIC -std=c++0x -fPIC
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L../../../bin/linux/gmake/x32/Debug -L. -shared -m32 -L/usr/lib32
  LDDEPS    += ../../../bin/linux/gmake/x32/Debug/libluabind.a ../../../bin/linux/gmake/x32/Debug/lua5.3.a
  LIBS      += $(LDDEPS) -lboost_filesystem -ldl -lpthread -lboost_system
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release32)
  OBJDIR     = ../../../obj/linux/gmake/x32/Release/blufs/x32
  TARGETDIR  = ../../../bin/linux/gmake/x32/Release
  TARGET     = $(TARGETDIR)/blufs.so
  DEFINES   += -DBOOST_NO_VARIADIC_TEMPLATES -DRELEASE
  INCLUDES  += -I../../../deps/luabind -I../../../deps/Catch/single_include -I../../../deps/LuaState/include -I../../../deps/lua/lua-5.3.0/src
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O2 -m32 -fPIC -std=c++0x -fPIC
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L../../../bin/linux/gmake/x32/Release -L. -s -shared -m32 -L/usr/lib32
  LDDEPS    += ../../../bin/linux/gmake/x32/Release/libluabind.a ../../../bin/linux/gmake/x32/Release/lua5.3.a
  LIBS      += $(LDDEPS) -lboost_filesystem -ldl -lpthread -lboost_system
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug64)
  OBJDIR     = ../../../obj/linux/gmake/x64/Debug/blufs/x64
  TARGETDIR  = ../../../bin/linux/gmake/x64/Debug
  TARGET     = $(TARGETDIR)/blufs.so
  DEFINES   += -DBOOST_NO_VARIADIC_TEMPLATES -DDEBUG -D_DEBUG
  INCLUDES  += -I../../../deps/luabind -I../../../deps/Catch/single_include -I../../../deps/LuaState/include -I../../../deps/lua/lua-5.3.0/src
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -m64 -fPIC -std=c++0x -fPIC
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L../../../bin/linux/gmake/x64/Debug -L. -shared -m64 -L/usr/lib64
  LDDEPS    += ../../../bin/linux/gmake/x64/Debug/libluabind.a ../../../bin/linux/gmake/x64/Debug/lua5.3.a
  LIBS      += $(LDDEPS) -lboost_filesystem -ldl -lpthread -lboost_system
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release64)
  OBJDIR     = ../../../obj/linux/gmake/x64/Release/blufs/x64
  TARGETDIR  = ../../../bin/linux/gmake/x64/Release
  TARGET     = $(TARGETDIR)/blufs.so
  DEFINES   += -DBOOST_NO_VARIADIC_TEMPLATES -DRELEASE
  INCLUDES  += -I../../../deps/luabind -I../../../deps/Catch/single_include -I../../../deps/LuaState/include -I../../../deps/lua/lua-5.3.0/src
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O2 -m64 -fPIC -std=c++0x -fPIC
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L../../../bin/linux/gmake/x64/Release -L. -s -shared -m64 -L/usr/lib64
  LDDEPS    += ../../../bin/linux/gmake/x64/Release/libluabind.a ../../../bin/linux/gmake/x64/Release/lua5.3.a
  LIBS      += $(LDDEPS) -lboost_filesystem -ldl -lpthread -lboost_system
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = ../../../obj/linux/gmake/Native/Debug/blufs
  TARGETDIR  = ../../../bin/linux/gmake
  TARGET     = $(TARGETDIR)/blufs.so
  DEFINES   += -DBOOST_NO_VARIADIC_TEMPLATES -DDEBUG -D_DEBUG
  INCLUDES  += -I../../../deps/luabind -I../../../deps/Catch/single_include -I../../../deps/LuaState/include -I../../../deps/lua/lua-5.3.0/src
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -fPIC -std=c++0x -fPIC
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L../../../bin/linux/gmake -L. -shared
  LDDEPS    += ../../../bin/linux/gmake/libluabind.a ../../../bin/linux/gmake/lua5.3.a
  LIBS      += $(LDDEPS) -lboost_filesystem -ldl -lpthread -lboost_system
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = ../../../obj/linux/gmake/Native/Release/blufs
  TARGETDIR  = ../../../bin/linux/gmake
  TARGET     = $(TARGETDIR)/blufs.so
  DEFINES   += -DBOOST_NO_VARIADIC_TEMPLATES -DRELEASE
  INCLUDES  += -I../../../deps/luabind -I../../../deps/Catch/single_include -I../../../deps/LuaState/include -I../../../deps/lua/lua-5.3.0/src
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O2 -fPIC -std=c++0x -fPIC
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L../../../bin/linux/gmake -L. -s -shared
  LDDEPS    += ../../../bin/linux/gmake/libluabind.a ../../../bin/linux/gmake/lua5.3.a
  LIBS      += $(LDDEPS) -lboost_filesystem -ldl -lpthread -lboost_system
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/blufs.o \
	$(OBJDIR)/blufs_lib.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking blufs
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning blufs
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -MMD -MP $(DEFINES) $(INCLUDES) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
endif

$(OBJDIR)/blufs.o: ../../../src/blufs.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/blufs_lib.o: ../../../src/blufs_lib.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF $(@:%.o=%.d) -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif
