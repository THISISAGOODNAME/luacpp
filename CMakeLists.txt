cmake_minimum_required(VERSION 3.6)
project(luacpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(lua-5.1.5/src)

set(LUA_CORE_FILES
        lua-5.1.5/src/lapi.c
        lua-5.1.5/src/lcode.c
        lua-5.1.5/src/ldebug.c
        lua-5.1.5/src/ldo.c
        lua-5.1.5/src/ldump.c
        lua-5.1.5/src/lfunc.c
        lua-5.1.5/src/lgc.c
        lua-5.1.5/src/llex.c
        lua-5.1.5/src/lmem.c
        lua-5.1.5/src/lobject.c
        lua-5.1.5/src/lopcodes.c
        lua-5.1.5/src/lparser.c
        lua-5.1.5/src/lstate.c
        lua-5.1.5/src/lstring.c
        lua-5.1.5/src/ltable.c
        lua-5.1.5/src/ltm.c
        lua-5.1.5/src/lundump.c
        lua-5.1.5/src/lvm.c
        lua-5.1.5/src/lzio.c)

set(LUA_LIB_FILES
        lua-5.1.5/src/lauxlib.c
        lua-5.1.5/src/lbaselib.c
        lua-5.1.5/src/ldblib.c
        lua-5.1.5/src/liolib.c
        lua-5.1.5/src/lmathlib.c
        lua-5.1.5/src/loslib.c
        lua-5.1.5/src/ltablib.c
        lua-5.1.5/src/lstrlib.c
        lua-5.1.5/src/loadlib.c
        lua-5.1.5/src/linit.c)

set(LUA_SRC ${LUA_CORE_FILES} ${LUA_LIB_FILES})

# 构建lua动态库
#add_library(LuaLib SHARED ${LUA_SRC})
# 定义两个LuaLib构建相关的宏
#ADD_DEFINITIONS(-DLUA_LIB -DLUA_BUILD_AS_DLL)

#标准lua解释器
add_executable(lua lua-5.1.5/src/lua.c ${LUA_SRC})

# 1. 实现lua解释器
add_executable(myLuaInterpreter src/lua_interpreter/main.cpp ${LUA_SRC})

# 2. 从文件中读取代码并运行
add_executable(myLoadLuaCodeFromFile src/lua_loadCodeFromFile/main.cpp ${LUA_SRC})
file(COPY src/lua_loadCodeFromFile/test1.lua DESTINATION ${CMAKE_BINARY_DIR}/)

# 3. 从文件中读取变量
add_executable(myLoadValueFromFile src/lua_loadValueFromFile/main.cpp ${LUA_SRC})
file(COPY src/lua_loadValueFromFile/test2.lua DESTINATION ${CMAKE_BINARY_DIR}/)

# 4. C++将变量传至lua
add_executable(myLoadValueFromCpp src/lua_loadValueFromCpp/main.cpp ${LUA_SRC})
file(COPY src/lua_loadValueFromCpp/test3.lua DESTINATION ${CMAKE_BINARY_DIR}/)

# 5. 编写动态库供lua调用
add_library(myLuaLib SHARED src/lua_loadValueFromDll/main.cpp ${LUA_SRC})
#target_link_libraries(myLuaLib LuaLib)
file(COPY src/lua_loadValueFromDll/test4.lua DESTINATION ${CMAKE_BINARY_DIR}/)


#set(SOURCE_FILES main.cpp)
#add_executable(luacpp ${SOURCE_FILES})