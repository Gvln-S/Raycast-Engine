cmake_minimum_required(VERSION 3.15)
project(Raycast-Engine VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MINGW)
    add_compile_definitions(
        __MINGW32__
        __MINGW64__
        __x86_64__
        _WIN32
        _WIN64
    )
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}
    "C:/ProgramData/mingw64/mingw64/lib/gcc/x86_64-w64-mingw32/13.2.0/include/c++"
    "C:/ProgramData/mingw64/mingw64/lib/gcc/x86_64-w64-mingw32/13.2.0/include/c++/x86_64-w64-mingw32"
    "C:/ProgramData/mingw64/mingw64/lib/gcc/x86_64-w64-mingw32/13.2.0/include/c++/backward"
    "C:/ProgramData/mingw64/mingw64/lib/gcc/x86_64-w64-mingw32/13.2.0/include"
    "C:/ProgramData/mingw64/mingw64/lib/gcc/x86_64-w64-mingw32/13.2.0/include-fixed"
    "C:/ProgramData/mingw64/mingw64/x86_64-w64-mingw32/include"
)

add_compile_options(-Wall)
add_executable(Raycast-Engine src/main.cpp)

target_link_libraries(Raycast-Engine freeglut opengl32 glu32)
