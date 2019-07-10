#add src directory
cmake_minimum_required(VERSION 3.14)

#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -I../inc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -I../inc")

set(CMAKE_CURRENT_SOURCE_DIR "../src")

set(LIB_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/MathNodes.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/parenthesize.c
	${CMAKE_CURRENT_SOURCE_DIR}/MathTreeBuilder.cpp
)

#set(dir ../)


project(MathNodes)

include_directories(inc)

#create libraries
add_library(libMathNodes STATIC ${LIB_SOURCES})



add_executable(iparse 
	${CMAKE_CURRENT_SOURCE_DIR}/iparse.cpp
)
target_link_libraries(iparse libMathNodes)


add_executable(parse 
	${CMAKE_CURRENT_SOURCE_DIR}/parse.cpp

)
target_link_libraries(parse libMathNodes)

add_executable(MathNodesTest 
	../test/MathNodesTest.cpp
)
target_link_libraries(MathNodesTest libMathNodes)

