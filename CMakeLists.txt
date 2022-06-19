cmake_minimum_required(VERSION 3.16)
project(wilpac)

SET (CMAKE_CXX_FLAGS_RELEASE_INIT   "-o3 =DNDEBUG")

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(wilpac
        src/Buckets.h
        src/Colors.h
        src/Commands.cpp
        src/Commands.h
        src/main.cpp
        src/Package.h
        src/PackageMan.cpp
        src/PackageMan.h
        src/Parser.cpp
        src/Parser.h
        src/Runtime.cpp
        src/Runtime.h)
