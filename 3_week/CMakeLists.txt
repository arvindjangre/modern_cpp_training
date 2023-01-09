cmake_minimum_required(VERSION 3.10.0)
project(parser VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE SRC_FILES src/*.cpp )
add_executable(parser ${SRC_FILES})

add_subdirectory(csv-parser)

set(JSON_BuildTests OFF CACHE INTERNAL "")
target_link_libraries(parser csv)
include_directories(${Boost_INCLUDE_DIR})

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${CSV_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${LIBS})

set(CMAKE_BUILD_TYPE Debug)
include(CPack)