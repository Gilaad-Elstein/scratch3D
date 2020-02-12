cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

project(scratch3D)

find_package(raylib 2.5) # Let CMake search for a raylib-config.cmake


#copy resources folder from source directory to binary directory
file(COPY Resources DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})


add_executable(scratch3D main.cpp App.cpp App.h structs/Vec3.cpp structs/Vec3.h Mesh.cpp Mesh.h structs/Matrix4x4.cpp structs/Matrix4x4.h Graphics.cpp Graphics.h  structs/Vec2.cpp structs/Vec2.h  structs/Texture.cpp structs/Texture.h structs/Logger.cpp  structs/Logger.h  Scene.cpp Scene.h Scenes/TestCubeScene.cpp Scenes/TestCubeScene.h Scenes/AfricanHeadScene.cpp Scenes/AfricanHeadScene.h Scenes/RotatingObjectScene.cpp Scenes/RotatingObjectScene.h Scenes/JeepScene.cpp Scenes/JeepScene.h Scenes/MeiPosedScene.cpp Scenes/MeiPosedScene.h)

#set(raylib_VERBOSE 1)
target_link_libraries(scratch3D raylib  X11)

#if (NOT raylib_FOUND)
#    include(FetchContent)
#
#    FetchContent_Declare(
#            raylib
#            URL https://github.com/raysan5/raylib/archive/master.tar.gz
#    )
#
#    FetchContent_GetProperties(raylib)
#    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
#        set(FETCHCONTENT_QUIET NO)
#        FetchContent_Populate(raylib)
#
#        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
#        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games
#
#        # build raylib
#        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
#
#    endif()
#
#endif()