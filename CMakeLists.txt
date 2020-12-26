cmake_minimum_required(VERSION 3.10)

project(SourceBase)
set(CMAKE_CXX_STANDARD 17)
include_directories(ScriptHookV/inc)
link_directories(ScriptHookV/lib)
set(CMAKE_SUPPRESS_REGENERATION true)
set(DBUILD_SHARED_LIBS ON)

file(GLOB SOURCE_HPP "src/*.hpp")
file(GLOB SOURCE_CPP "src/*.cpp")

set(SRC 
	${SOURCE_HPP}
	${SOURCE_CPP}
)

list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS asi)
add_library(${PROJECT_NAME} SHARED ${SRC})