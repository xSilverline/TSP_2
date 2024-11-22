cmake_minimum_required(VERSION 3.28)
project(TSP_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")


add_executable(TSP_2 Source/Class/main.cpp
        Source/Class/DFS.cpp
        Source/Headers/DFS.h
        Source/Class/BFS.cpp
        Source/Headers/BFS.h
        Source/Class/BestFirst.cpp
        Source/Headers/BestFirst.h
        Source/Class/Run.cpp
        Source/Headers/Run.h
        Source/Class/NearestNeighbour.cpp
        Source/Headers/NearestNeighbour.h
        Source/Headers/Structures.h
        Source/Headers/TimeCounter.h
        Source/Headers/Libs.h
        Source/Libraries/iniParser/INIReader.cpp
        Source/Libraries/iniParser/INIReader.h
        Source/Libraries/iniParser/ini.cpp
        Source/Libraries/iniParser/ini.h)
