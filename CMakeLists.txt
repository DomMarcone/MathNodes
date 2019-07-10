#add src directory
cmake_minimum_required(VERSION 3.14)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -I../inc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -I../inc")

#set(CMAKE_CURRENT_SOURCE_DIR "../src")
set(CURRENT_SOURCE_DIR src)
set(CURRENT_INCLUDE_DIR inc)

project(MathNodes)

include_directories(inc)


set(MATHNODELIB_SOURCES
	${CURRENT_SOURCE_DIR}/MathNodes.cpp
	${CURRENT_SOURCE_DIR}/parenthesize.c
	${CURRENT_SOURCE_DIR}/MathTreeBuilder.cpp
)

set(MATHNODELIB_HEADERS
	${CURRENT_INCLUDE_DIR}/MathNodes.hpp
	${CURRENT_INCLUDE_DIR}/parenthesize.h
	${CURRENT_INCLUDE_DIR}/MathTreeBuilder.hpp
)

#SET_SOURCE_FILES_PROPERTIES( MATHNODELIB_SOURCES PROPERTIES LANGUAGE CXX )

#create libraries
#add_library(libMathNodes SHARED ${MATHNODELIB_SOURCES})
add_library(libMathNodes STATIC ${MATHNODELIB_SOURCES} ${MATHNODELIB_HEADERS})
#target_include_directories(libMathNodes PUBLIC inc)
#target_include_directories(libMathNodes PRIVATE inc)

#install(TARGETS libMathNodes DESTINATION lib)
#install(FILES MathNodes.hpp parenthesize.h MathTreeBuilder.hpp DESTINATION include)

add_executable(iparse
	${CURRENT_SOURCE_DIR}/iparse.cpp ${MATHNODELIB_SOURCES} ${MATHNODELIB_HEADERS}
)
target_link_libraries(iparse libMathNodes)
target_include_directories(iparse PRIVATE inc)


add_executable(parse 
	${CURRENT_SOURCE_DIR}/parse.cpp ${MATHNODELIB_SOURCES} ${MATHNODELIB_HEADERS}

)
target_link_libraries(parse libMathNodes)


add_executable(MathNodesTest 
	../test/MathNodesTest.cpp ${MATHNODELIB_SOURCES} ${MATHNODELIB_HEADERS}
)
target_link_libraries(MathNodesTest libMathNodes)
