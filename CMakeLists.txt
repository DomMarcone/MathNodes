cmake_minimum_required(VERSION 3.14)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -I../inc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -I../inc")

set(CURRENT_SOURCE_DIR src)

project(MathNodes)

include_directories(inc)


set(MATHNODELIB_SOURCES
	${CURRENT_SOURCE_DIR}/MathNodes.cpp
	${CURRENT_SOURCE_DIR}/parenthesize.c
	${CURRENT_SOURCE_DIR}/MathTreeBuilder.cpp
)


add_library(libMathNodes STATIC ${MATHNODELIB_SOURCES})

add_executable(iparse
	${CURRENT_SOURCE_DIR}/iparse.cpp 
)
target_link_libraries(iparse libMathNodes)
target_include_directories(iparse PRIVATE inc)


add_executable(parse 
	${CURRENT_SOURCE_DIR}/parse.cpp 

)
target_link_libraries(parse libMathNodes)


add_executable(MathNodesTest 
	../test/MathNodesTest.cpp 
)
target_link_libraries(MathNodesTest libMathNodes)


#add_executable(parenthesize 
#	../test/test_parenthesize.cpp 
#)
#target_link_libraries(parenthesize libMathNodes)


add_executable(benchmark 
	../test/benchmark.cpp 
)
target_link_libraries(benchmark libMathNodes)


